<?php

/**
 * Retrieve the list of default moderators stored in entity_collection.
 *
 * @return mixed
 *   Array of user accounts, ordered by weight in the collection.
 */
function vesafe_workflow_get_default_approvers() {
  $entity_collection = entity_collection_load('approvers');
  $contexts = _entity_collection_get_contexts($entity_collection);
  $tree = EntityCollectionStorage::getBundleStorage($entity_collection->bundle)->retrieve($entity_collection, $contexts);
  $rows = $tree->getFlat();
  $uids = array();
  foreach ($rows as $row) {
    $uids[] = $row->entity_id;
  }
  $users = user_load_multiple($uids);
  foreach ($users as &$user) {
    $user->osha_workflow_node_approval_saved = FALSE;
  }
  return $users;
}

/**
 * Retrieve the list of moderators for a node.
 *
 * @param int $nid
 *   Node ID
 * @param bool $default
 *   If not set yet, return the default values stored in the entity collection.
 *
 * @return array|mixed
 *   Array of users.
 */
function vesafe_workflow_get_node_approvers($nid, $default = TRUE) {
  $ret = [];
  $query = new EntityFieldQuery();
  $moderators = $query->entityCondition('entity_type', 'node_approval')
    ->propertyCondition('nid', $nid)
    ->propertyOrderBy('weight')
    ->execute();
  if (!empty($moderators['node_approval'])) {
    $ids = array_keys($moderators['node_approval']);
    $rows = vesafe_workflow_node_approval_load_multiple($ids);
    $uids = [];
    $rows_by_uid = [];
    foreach ($rows as $row) {
      $rows_by_uid[$row->uid] = $row;
      $uids[] = $row->uid;
    }
    $users = user_load_multiple($uids);
    foreach ($users as &$user) {
      $user->osha_workflow_node_approval = $rows_by_uid[$user->uid];
      $user->osha_workflow_node_approval_saved = TRUE;
    }
    reset($users);
    return $users;
  }
  elseif ($default) {
    $ret = vesafe_workflow_get_default_approvers();
  }
  return $ret;
}

/**
 * Assign the list of moderators to a node.
 *
 * @param object $nid
 *   Node ID
 * @param array $moderators
 *   Associative array of user accounts. Keys are weights, values are uids.
 */
function vesafe_workflow_set_node_approvers($nid, $moderators) {
  $transaction = db_transaction();
  try {
    // Delete old records for this node.
    db_delete('osha_workflow_node_approval')
      ->condition('nid', $nid)
      ->execute();
    $query = db_insert('osha_workflow_node_approval')
      ->fields(array('nid', 'uid', 'next', 'weight'));
    $i = 0;
    foreach ($moderators as $weight => $uid) {
      $record = array(
        'nid' => $nid,
        'uid' => $uid,
        'next' => $i == 0 ? 1 : 0,
        'weight' => $weight,
      );
      $query->values($record);
      $i++;
    }
    $query->execute();
  }
  catch(Exception $e) {
    $transaction->rollback();
    drupal_set_message($e->getMessage(), 'error');
  }
}

/**
 * Reset voting status and next in line approval queue.
 *
 * @param int $nid
 *   Affected node ID
 */
function vesafe_workflow_reset_node_approvers($nid) {
  $transaction = db_transaction();
  try {
    $rows = vesafe_workflow_get_node_approvers($nid, FALSE);
    $first = NULL;
    if (!empty($rows)) {
      $first = current($rows);
    }
    // Reset all of them to defaults.
    db_update('osha_workflow_node_approval')
      ->fields(array(
        'approved' => NULL,
        'next' => 0,
      ))
      ->condition('nid', $nid)
      ->execute();

    if ($first) {
      // Assign 'next' to first one in line.
      db_update('osha_workflow_node_approval')
        ->fields(array(
          'next' => 1,
        ))
        ->condition('nid', $nid)
        ->condition('uid', $first->uid)
        ->execute();
    }
  }
  catch(Exception $e) {
    $transaction->rollback();
    drupal_set_message($e->getMessage(), 'error');
  }
}

/**
 * Find the next moderator in the line for a node/revision.
 *
 * @param object $node
 *   Node to retrieve info.
 *
 * @return mixed|null
 *   User account
 */
function vesafe_workflow_get_next_approver($nid) {
  $ret = NULL;
  $query = new EntityFieldQuery();
  $moderators = $query->entityCondition('entity_type', 'node_approval')
    ->propertyCondition('nid', $nid)
    ->propertyCondition('next', 1)
    ->range(0, 1)
    ->execute();
  if (!empty($moderators['node_approval'])) {
    $rows = vesafe_workflow_node_approval_load_multiple(array_keys($moderators['node_approval']));
    $task = current($rows);
    $ret = user_load($task->uid);
  }
  return $ret;
}

function vesafe_workflow_is_next_approver($nid, $user=NULL) {
  if (empty($user)) {
    global $user;
  }
  $query = new EntityFieldQuery();
  $rows = $query->entityCondition('entity_type', 'node_approval')
    ->propertyCondition('nid', $nid)
    ->propertyCondition('uid', $user->uid)
    ->propertyCondition('next', 1)
    ->execute();
  return !empty($rows['node_approval']);
}

/**
 * Check if the user is the last approver.
 *
 * @param object $node
 *   Node to check
 * @param object $user
 *   User to check. If NULL, assuming current user.
 *
 * @return bool
 *   TRUE if it's the last in the queue.
 */
function vesafe_workflow_is_last_approver($node, $user = NULL) {
  $ret = FALSE;
  if (empty($user)) {
    global $user;
  }
  $all_users = vesafe_workflow_get_node_approvers($node->nid, FALSE);
  if (!empty($all_users)) {
    $last = array_pop($all_users);
    $ret = $user->uid == $last->uid;
  }
  return $ret;
}

function vesafe_workflow_needs_last_approver($node, $user = NULL) {
  $ret = FALSE;
  $query = new EntityFieldQuery();
  $miids = $query->entityCondition('entity_type', 'node_approval')
    ->propertyCondition('nid', $node->nid)
    ->propertyOrderBy('weight')
    ->execute();
  if (isset($miids['node_approval'])) {
    $rows = vesafe_workflow_node_approval_load_multiple(array_keys($miids['node_approval']));
    reset($rows);
    $last = array_pop($rows);
    $ret = $last->next == 1;
  }
  return $ret;
}

/**
 * Verifies if user has approved the workflow.
 * @param $nid
 * @param $uid
 * @return bool
 */
function vesafe_workflow_has_approved($nid, $uid) {
  $query = new EntityFieldQuery();
  $rows = $query->entityCondition('entity_type', 'node_approval')
    ->propertyCondition('nid', $nid)
    ->propertyCondition('uid', $uid)
    ->propertyCondition('approved', array(OSHA_WORKFLOW_STATE_APPROVED, OSHA_WORKFLOW_STATE_REJECTED))
    ->execute();
  return !empty($rows['node_approval']);
}


/**
 * Record the user's vote and move the record to the next in queue.
 *
 * @param object $node
 *   Node object
 * @param int $vote
 *   User's vote (accepted, rejected)
 * @param string $message
 *   User's message
 * @param object $voter
 *   User who vote, if NULL assuming current user.
 */
function vesafe_workflow_approve($node, $vote, $message = '', $voter = NULL) {
  if (empty($voter)) {
    global $user;
    $voter = $user;
  }
  $transaction = db_transaction();
  try {
    $query = new EntityFieldQuery();
    $miids = $query->entityCondition('entity_type', 'node_approval')
      ->propertyCondition('nid', $node->nid)
      ->propertyOrderBy('weight')
      ->execute();
    if (isset($miids['node_approval'])) {
      $rows = vesafe_workflow_node_approval_load_multiple(array_keys($miids['node_approval']));
      reset($rows);
      $mark_next = FALSE;
      foreach ($rows as $row) {
        if ($row->next == 1) {
          $mark_next = TRUE;
          $row->next = 0;
          $row->approved = $vote;
          if ($row->uid != $voter->uid) {
            $message .= $voter->name . ' approved the content.';
          }
          $row->message = $message;
          entity_save('node_approval', $row);
          continue;
        }
        if ($mark_next) {
          $row->next = 1;
          entity_save('node_approval', $row);
          break;
        }
      }
    }

    $query = new EntityFieldQuery();
    $miids = $query->entityCondition('entity_type', 'node_reviewing')
      ->propertyCondition('nid', $node->nid)
      ->propertyOrderBy('weight')
      ->execute();
    if (isset($miids['node_reviewing'])) {
      $rows = vesafe_workflow_node_reviewing_load_multiple(array_keys($miids['node_reviewing']));
      reset($rows);
      $mark_next = FALSE;
      foreach ($rows as $row) {
        if ($row->next == 1) {
          $mark_next = TRUE;
          $row->next = 0;
          $row->reviewed = $vote;
          if ($row->uid != $voter->uid) {
            $message .= $voter->name . ' reviewed the content.';
          }
          $row->message = $message;
          entity_save('node_reviewing', $row);
          continue;
        }
        if ($mark_next) {
          $row->next = 1;
          entity_save('node_reviewing', $row);
          break;
        }
      }
    }

  }
  catch(Exception $e) {
    $transaction->rollback();
    drupal_set_message($e->getMessage(), 'error');
  }
}

/**
 * Make an HTML select options from the list of users assigned to a role.
 *
 * @param string $role_name
 *   Name of the Role
 *
 * @see osha_workflow_users_get_review_managers
 * @return array
 *   HTML select options
 */
function vesafe_workflow_users_get_users_from_role_as_options($role_name) {
  $users = vesafe_workflow_users_get_users_from_role($role_name);
  $ret = array();
  foreach ($users as $uid => $u) {
    $ret[$uid] = $u->name;
  }
  return $ret;
}

/**
 * Retrieve the list of users from a role, ordered by name.
 *
 * @param string $role_name
 *   Name of the Role
 *
 * @return array
 *   Array of user objects
 */
function vesafe_workflow_users_get_users_from_role($role_name) {
  $ret = array();
  if ($role = user_role_load_by_name($role_name)) {
    $query = db_select('users', 'u')->fields('u', array('uid'));
    $query->join('users_roles', 'ur', 'ur.uid = u.uid');
    $uids = $query->condition('ur.rid', $role->rid)
      ->orderBy('u.name')
      ->groupBy('u.uid')
      ->execute()->fetchCol();
    $ret = user_load_multiple($uids);
  }
  return $ret;
}

/**
 *  Set default approvers list for a node.
 */
function vesafe_workflow_assign_default_cpm($node) {
  $default_cpms = _hwc_workflow_get_default_cpm();
  $weight = 0;
  foreach ($default_cpms as $cpm) {
    $row = array(
      'uid' => $cpm->uid,
      'weight' => $weight,
      'nid' => $node->nid,
    );
    _hwc_workflow_admin_approvers_save_row($row);
    $weight++;
  }
  drupal_set_message('Default Campaign Project Managers were set for this node');
  return $default_cpms;
}

/**
 * Retrieve the list of default moderators stored in entity_collection.
 *
 * @return mixed
 *   Array of user accounts, ordered by weight in the collection.
 */
function vesafe_workflow_get_default_reviewers() {
  $entity_collection = entity_collection_load('reviewers');
  $contexts = _entity_collection_get_contexts($entity_collection);
  $tree = EntityCollectionStorage::getBundleStorage($entity_collection->bundle)->retrieve($entity_collection, $contexts);
  $rows = $tree->getFlat();
  $uids = array();
  foreach ($rows as $row) {
    $uids[] = $row->entity_id;
  }
  $users = user_load_multiple($uids);
  foreach ($users as &$user) {
    $user->osha_workflow_node_reviewing_saved = FALSE;
  }
  return $users;
}

/**
 * Retrieve the list of moderators for a node.
 *
 * @param int $nid
 *   Node ID
 * @param bool $default
 *   If not set yet, return the default values stored in the entity collection.
 *
 * @return array|mixed
 *   Array of users.
 */
function vesafe_workflow_get_node_reviewers($nid, $default = TRUE) {
  $ret = [];
  $query = new EntityFieldQuery();
  $moderators = $query->entityCondition('entity_type', 'node_reviewing')
    ->propertyCondition('nid', $nid)
    ->propertyOrderBy('weight')
    ->execute();
  if (!empty($moderators['node_reviewing'])) {
    $ids = array_keys($moderators['node_reviewing']);
    $rows = vesafe_workflow_node_reviewing_load_multiple($ids);
    $uids = [];
    $rows_by_uid = [];
    foreach ($rows as $row) {
      $rows_by_uid[$row->uid] = $row;
      $uids[] = $row->uid;
    }
    $users = user_load_multiple($uids);
    foreach ($users as &$user) {
      $user->osha_workflow_node_reviewing = $rows_by_uid[$user->uid];
      $user->osha_workflow_node_reviewing_saved = TRUE;
    }
    reset($users);
    return $users;
  }
  elseif ($default) {
    $ret = vesafe_workflow_get_default_reviewers();
  }
  return $ret;
}

/**
 * Assign the list of moderators to a node.
 *
 * @param object $nid
 *   Node ID
 * @param array $moderators
 *   Associative array of user accounts. Keys are weights, values are uids.
 */
function vesafe_workflow_set_node_reviewers($nid, $moderators) {
  $transaction = db_transaction();
  try {
    // Delete old records for this node.
    db_delete('osha_workflow_node_review')
      ->condition('nid', $nid)
      ->execute();
    $query = db_insert('osha_workflow_node_review')
      ->fields(array('nid', 'uid', 'next', 'weight'));
    $i = 0;
    foreach ($moderators as $weight => $uid) {
      $record = array(
        'nid' => $nid,
        'uid' => $uid,
        'next' => $i == 0 ? 1 : 0,
        'weight' => $weight,
      );
      $query->values($record);
      $i++;
    }
    $query->execute();
  }
  catch(Exception $e) {
    $transaction->rollback();
    drupal_set_message($e->getMessage(), 'error');
  }
}

/**
 * Reset voting status and next in line reviewing queue.
 *
 * @param int $nid
 *   Affected node ID
 */
function vesafe_workflow_reset_node_reviewers($nid) {
  $transaction = db_transaction();
  try {
    $rows = vesafe_workflow_get_node_reviewers($nid, FALSE);
    $first = NULL;
    if (!empty($rows)) {
      $first = current($rows);
    }
    // Reset all of them to defaults.
    db_update('osha_workflow_node_review')
      ->fields(array(
        'reviewed' => NULL,
        'next' => 0,
      ))
      ->condition('nid', $nid)
      ->execute();

    if ($first) {
      // Assign 'next' to first one in line.
      db_update('osha_workflow_node_review')
        ->fields(array(
          'next' => 1,
        ))
        ->condition('nid', $nid)
        ->condition('uid', $first->uid)
        ->execute();
    }
  }
  catch(Exception $e) {
    $transaction->rollback();
    drupal_set_message($e->getMessage(), 'error');
  }
}

/**
 * Find the next moderator in the line for a node/revision.
 *
 * @param object $node
 *   Node to retrieve info.
 *
 * @return mixed|null
 *   User account
 */
function vesafe_workflow_get_next_reviewer($nid) {
  $ret = NULL;
  $query = new EntityFieldQuery();
  $moderators = $query->entityCondition('entity_type', 'node_reviewing')
    ->propertyCondition('nid', $nid)
    ->propertyCondition('next', 1)
    ->range(0, 1)
    ->execute();
  if (!empty($moderators['node_reviewing'])) {
    $rows = vesafe_workflow_node_reviewing_load_multiple(array_keys($moderators['node_reviewing']));
    $task = current($rows);
    $ret = user_load($task->uid);
  }
  return $ret;
}

function vesafe_workflow_is_next_reviewer($nid, $user=NULL) {
  if (empty($user)) {
    global $user;
  }
  $query = new EntityFieldQuery();
  $rows = $query->entityCondition('entity_type', 'node_reviewing')
    ->propertyCondition('nid', $nid)
    ->propertyCondition('uid', $user->uid)
    ->propertyCondition('next', 1)
    ->execute();
  return !empty($rows['node_reviewing']);
}

/**
 * Check if the user is the last reviewer.
 *
 * @param object $node
 *   Node to check
 * @param object $user
 *   User to check. If NULL, assuming current user.
 *
 * @return bool
 *   TRUE if it's the last in the queue.
 */
function vesafe_workflow_is_last_reviewer($node, $user = NULL) {
  $ret = FALSE;
  if (empty($user)) {
    global $user;
  }
  $all_users = vesafe_workflow_get_node_reviewers($node->nid, FALSE);
  if (!empty($all_users)) {
    $last = array_pop($all_users);
    $ret = $user->uid == $last->uid;
  }
  return $ret;
}

function vesafe_workflow_needs_last_reviewer($node, $user = NULL) {
  $ret = FALSE;
  $query = new EntityFieldQuery();
  $miids = $query->entityCondition('entity_type', 'node_reviewing')
    ->propertyCondition('nid', $node->nid)
    ->propertyOrderBy('weight')
    ->execute();
  if (isset($miids['node_reviewing'])) {
    $rows = vesafe_workflow_node_reviewing_load_multiple(array_keys($miids['node_reviewing']));
    reset($rows);
    $last = array_pop($rows);
    $ret = $last->next == 1;
  }
  return $ret;
}

/**
 * Verifies if user has reviewed the workflow.
 * @param $nid
 * @param $uid
 * @return bool
 */
function vesafe_workflow_has_reviewed($nid, $uid) {
  $query = new EntityFieldQuery();
  $rows = $query->entityCondition('entity_type', 'node_reviewing')
    ->propertyCondition('nid', $nid)
    ->propertyCondition('uid', $uid)
    ->propertyCondition('reviewed', array(OSHA_WORKFLOW_STATE_REVIEWED, OSHA_WORKFLOW_STATE_REJECTED))
    ->execute();
  return !empty($rows['node_reviewing']);
}


/**
 * Record the user's vote and move the record to the next in queue.
 *
 * @param object $node
 *   Node object
 * @param int $vote
 *   User's vote (accepted, rejected)
 * @param string $message
 *   User's message
 * @param object $voter
 *   User who vote, if NULL assuming current user.
 */
function vesafe_workflow_review($node, $vote, $message = '', $voter = NULL) {
  if (empty($voter)) {
    global $user;
    $voter = $user;
  }
  $transaction = db_transaction();
  try {
    $query = new EntityFieldQuery();
    $miids = $query->entityCondition('entity_type', 'node_reviewing')
      ->propertyCondition('nid', $node->nid)
      ->propertyOrderBy('weight')
      ->execute();
    if (isset($miids['node_reviewing'])) {
      $rows = vesafe_workflow_node_reviewing_load_multiple(array_keys($miids['node_reviewing']));
      reset($rows);
      $mark_next = FALSE;
      foreach ($rows as $row) {
        if ($row->next == 1) {
          $mark_next = TRUE;
          $row->next = 0;
          $row->reviewed = $vote;
          if ($row->uid != $voter->uid) {
            $message .= $voter->name . ' reviewed the content.';
          }
          $row->message = $message;
          entity_save('node_reviewing', $row);
          continue;
        }
        if ($mark_next) {
          $row->next = 1;
          entity_save('node_reviewing', $row);
          break;
        }
      }
    }
  }
  catch(Exception $e) {
    $transaction->rollback();
    drupal_set_message($e->getMessage(), 'error');
  }
}
