<?php

/**
 * Form builder for workflow_moderation_form (approval).
 *
 * @param array $form
 *   Form to modify
 * @param array $form_state
 *   Form state
 * @param object $node
 *   Current node
 *
 * @return array
 *   Form array
 */
function vesafe_workflow_node_approval_form($form, &$form_state, $node) {
  module_load_include('inc', 'vesafe_workflow', 'vesafe_workflow.api');
  $can_edit = user_access('edit node approvers');
  $form_state['node'] = $node;
  $form['#can_edit']  = $can_edit;
  $form['#tree'] = TRUE;
  $form['#theme'] = 'vesafe_workflow_approval_form';
  if (isset($form_state['rows'])) {
    $rows = $form_state['rows'];
  }
  else {
    $rows = vesafe_workflow_get_node_approvers($node->nid, FALSE);
  }
  $form_state['rows'] = $rows;
  $weight = 0;
  foreach ($rows as $uid => $row) {
    $form['rows'][$uid]['#row'] = $row;
    $form['rows'][$uid]['weight'] = array(
      '#type' => 'weight',
      '#title' => t('Weight'),
      '#title_display' => 'invisible',
      '#default_value' => (-10 + $weight),
      '#access' => $can_edit,
      '#attributes' => array('class' => array('user-weight')),
    );
    $form['rows'][$uid]['uid'] = array(
      '#type' => 'hidden',
      '#value' => $uid,
    );
    $form['rows'][$uid]['remove'] = array(
      '#type' => 'submit',
      '#name' => $uid,
      '#value' => t('Remove'),
      '#access' => $can_edit,
      '#submit' => array('vesafe_workflow_admin_approvers_remove_row'),
    );
    $weight++;
  }
  $form['add']['uid'] = array(
    '#type' => 'select',
    '#multiple' => FALSE,
    '#options' => vesafe_workflow_users_get_users_from_role_as_options('approver'),
    '#title' => t('Add another approver'),
    '#title_display' => 'invisible',
    '#access' => $can_edit,
  );
  $form['add']['submit'] = array(
    '#type' => 'submit',
    '#name' => 'adduser',
    '#value' => t('Add to queue'),
    '#access' => $can_edit,
    '#attributes' => array('class' => array('container-inline')),
    '#submit' => array('vesafe_workflow_admin_approvers_add_row'),
  );
  $form['help'] = array(
    '#type' => 'markup',
    '#markup' =>
      t('<div><strong>Tip:</strong> Use the drag handlers to sort the users in the order you want them to have the content reviewed. <br />** - Temporary, not yet saved</div>'),
  );
  $form['content'] = array(
    'actions' => array(
      '#type' => 'actions',
      '#weight' => 20,
      'submit' => array(
        '#type' => 'submit',
        '#value' => t('Save'),
        '#access' => $can_edit,
      ),
    ),
  );
  return $form;
}

function vesafe_workflow_admin_approvers_remove_row($form, &$form_state) {
  if (isset($form_state['triggering_element'])) {
    $triggering_element = $form_state['triggering_element'];
    if (isset($triggering_element['#name'])) {
      $uid = $triggering_element['#name'];
      unset($form_state['rows'][$uid]);
      unset($form_state['values']['rows'][$uid]);
      drupal_set_message(t('Changes made in this table will not be saved until you press Save'), 'warning');
      $form_state['rebuild'] = TRUE;
    }
  }
}

function vesafe_workflow_admin_approvers_add_row($form, &$form_state) {
  if (!empty($form_state['input']['add']['uid'])) {
    $moderator = user_load($form_state['input']['add']['uid']);
    $moderator->vesafe_workflow_node_approval_saved = FALSE;
    $form_state['rows'][$moderator->uid] = $moderator;
    drupal_set_message(t('Changes made in this table will not be saved until you press Save'), 'warning');
    $form_state['rebuild'] = TRUE;
  }
}

/**
 * Themes the workflow_moderation_form form.
 *
 * @param array $variables
 *   Form variables
 *
 * @return string
 *   Form HTML
 */
function theme_vesafe_workflow_approval_form($variables) {
  $output = '';
  $form = $variables['form'];
  $rows = array();
  if (!empty($form['rows'])) {
    $items = element_children($form['rows']);
    $last = end($items);
    reset($items);
    foreach ($items as $uid) {
      $moderator = $form['rows'][$uid]['#row'];
      $status = '';
      if (isset($moderator->osha_workflow_node_approval)) {
        $val = $moderator->osha_workflow_node_approval->approved;
        if ($val === NULL) {
          // NULL - not reviewed yet.
          $status = t('Waiting to approve');
        }
        else {
          $status = $val . (!empty($moderator->osha_workflow_node_approval->message) ? ' - ' . $moderator->osha_workflow_node_approval->message : '');
        }
      }
      $row = array();
      $name = check_plain($moderator->name);
      if (empty($moderator->vesafe_workflow_node_approval_saved)) {
        $name .= '<sup>**</sup>';
      }
      $row[] = $name;
      $row[] = check_plain($moderator->mail);
      $row[] = $status;
      $row[] = drupal_render($form['rows'][$uid]['remove']);
      $row[] = drupal_render($form['rows'][$uid]['weight']);
      $rows[] = array('data' => $row, 'class' => array('draggable'));
    }
  }
  $row = array(
    drupal_render($form['add']['uid']),
    drupal_render($form['add']['submit']),
    '',
    '',
    '',
  );
  $rows[] = $row;
  $caption = t('List of approvers');

  $header = array(
    t('User'),
    t('Mail'),
    t('Status'),
    '',
  );
  if ($form['#can_edit']) {
    array_push($header, t('Order of notification'));
  }
  $table = array(
    '#theme' => 'table',
    '#caption' => $caption,
    '#header' => $header,
    '#attributes' => array(
      'id' => 'approvers_table',
    ),
    '#rows' => $rows,
  );
  if (isset($form['moderation'])) {
    $output .= drupal_render($form['moderation']);
  }
  $output .= drupal_render($table);
  $output .= drupal_render_children($form);
  if ($form['#can_edit']) {
    drupal_add_tabledrag('approvers_table', 'order', 'sibling', 'user-weight');
  }
  return $output;
}

/**
 * Implements hook_form_validate().
 */
function vesafe_workflow_node_approval_form_validate($form, $form_state) {
  if (empty($form_state['rows']) && $form_state['triggering_element']['#name'] != 'adduser') {
    form_set_error('enabled', t('Cannot have an empty moderation queue. Add at least one user or switch to another state!'));
  }
}

/**
 * Implements hook_form_submit().
 */
function vesafe_workflow_node_approval_form_submit($form, $form_state) {
  $users = array();
  $node = $form_state['node'];
  if (!empty($form_state['values']['rows'])) {
    $data = $form_state['values']['rows'];
    foreach ($data as $uid => $cfg) {
      $weight = $cfg['weight'];
      $users[$weight] = $uid;
    }
    ksort($users);
  }
  vesafe_workflow_set_node_approvers($node->nid, $users);
}


function vesafe_workflow_workbench_project_managers($type = NULL) {
  $types = ['good_practice', 'key_article'];
  if (empty($type)) {
    $rows = [];
    $output = '';
    $pms = vesafe_workflow_users_get_users_from_role(OSHA_WORKFLOW_ROLE_PM);
    if (empty($pms)) {
      $output .= '<p>No Project Managers are defined yet for the site</p>';
      return ['#markup' => $output];
    }
    $header = array(t('Section'), t('Review'), t('Broken Links'));

    $names = [];
    foreach ($pms as $pm) {
      $names[] = $pm->name;
    }
    $output .= '<p>Project Managers for this sections are: ' . implode(', ', $names) . '</p>';

    foreach ($types as $type) {
      $row = [];
      $bundle = node_type_load($type);
      $reviews = vesafe_workflow_workbench_pm_get_review($type);
      $review = current($reviews);

      $row[] = $bundle->name;

      if (empty($review)) {
        $text = 'Not reviewed yet';
      }
      else {
        $user_name = $review->uid;
        $user = user_load($review->uid);
        if (!empty($user)) {
          $user_name = $user->name;
        }
        $last_review = new DateTime(date("c", $review->created));
        $now = new DateTime();
        $since_last_review = $now->diff($last_review);
        $text = t('Last reviewed by @user on @date (@months months ago)', [
          '@user' => $user_name,
          '@date' => date('d-m-Y', $review->created),
          '@months' => $since_last_review->m,
        ]);
      }
      $text = l($text, 'admin/content/review/' . $type);

      $row[] = $text;

      $row[] = l(t('See the broken links'),
        'admin/content/linkchecker-broken-links',
        array('query' => array('type' => $type))
      );

      $rows[] = $row;
    }
    $output .= theme('table', array('header' => $header, 'rows' => $rows));
    $build['content']['#markup'] = $output;
    return $build;
  }

  return drupal_get_form('vesafe_workflow_section_review_form', $type);
}

/**
 * PM Review Section form.
 */
function vesafe_workflow_section_review_form($form, &$form_state, $type) {
  $bundle = node_type_load($type);
  $output = '<h2>' . t('%name PM section review', array('%name' => $bundle->name)) . '</h2>';

  $form_state['#section'] = $type;

  $form['title'] = array(
    '#markup' => $output,
  );

  $form['actions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Reviews'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['actions']['review_message'] = array(
    '#type' => 'textarea',
    '#title' => 'Message',
    '#description' => t('You can enter a message for your review.'),
  );

  $form['actions']['mark_as_reviewed'] = array(
    '#type' => 'submit',
    '#submit' => array('vesafe_workflow_access_section_review_form_submit'),
    '#validate' => array(),
    '#value' => 'Mark this section as Reviewed',
    '#access' => array('mark access section as reviewed'),
  );
  $form['go_back'] = array(
    '#theme' => 'link',
    '#text' => t('Go back'),
    '#path' => 'admin/config/workbench/access/managers/review',
    '#options' => array(
      'attributes' => array(),
      'html' => FALSE,
    ),
  );

  $form['actions']['#access'] = FALSE;
  if (_vesafe_workflow_user_has_role(OSHA_WORKFLOW_ROLE_PM)
    || _vesafe_workflow_user_has_role('administrator')) {
    $form['actions']['#access'] = TRUE;
  }

  // Add review history.
  $form['reviews'] = array(
    '#type' => 'fieldset',
    '#title' => t('Reviews'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $reviews = vesafe_workflow_workbench_pm_get_review($type);
  $rows = array();
  foreach ($reviews as $review) {
    $reviewer = user_load($review->uid);
    $rows[] = array(
      $reviewer->name,
      date('d-m-Y', $review->created),
      $review->message,
    );
  }
  $header = array('Reviewer', 'Data', 'Mesaj');
  $form['reviews']['table'] = array(
    '#markup' => theme('table', array('header' => $header, 'rows' => $rows)),
  );

  return $form;
}

/**
 * Submit callback for PM Review Section.
 */
function vesafe_workflow_access_section_review_form_submit($form, &$form_state) {
  global $user;
  $message = $form_state['values']['review_message'];
  $review = array(
    'uid' => $user->uid,
    'section' => $form_state['#section'],
    'message' => $message,
    'created' => REQUEST_TIME,
  );
  // Add the review.
  drupal_write_record('vesafe_workflow_sections_review', $review);

  drupal_set_message(t('Section reviewed successfully!'));
  $form_state['redirect'] = 'admin/content/review';
}

function vesafe_workflow_workbench_pm_get_review($section) {
  return db_select('vesafe_workflow_sections_review', 'sr')
    ->fields('sr')
    ->condition('sr.section', $section)
    ->orderBy('sr.srid', 'DESC')
    ->range(0, 1)
    ->execute()->fetchAllAssoc('srid');
}

function vesafe_workflow_get_sections_to_notify() {
  $sections = [];
  $types = ['good_practice', 'key_article'];
  $notify_interval = variable_get('vesafe_workflow_pm_reminders_interval', 3);
  foreach ($types as $type) {
    $review = vesafe_workflow_workbench_pm_get_review($type);
    $review = current($review);
    if (!empty($review)) {
      $last_review = new DateTime(date("c", $review->created));
      $now = new DateTime();
      $since_last_review = $now->diff($last_review);
      if ($since_last_review->m >= $notify_interval) {
        $sections[] = $type;
      }
    }
    else {
      $sections[] = $type;
    }
  }
  return $sections;
}

/**
 * Form builder for workflow_moderation_form (reviewing).
 *
 * @param array $form
 *   Form to modify
 * @param array $form_state
 *   Form state
 * @param object $node
 *   Current node
 *
 * @return array
 *   Form array
 */
function vesafe_workflow_node_reviewing_form($form, &$form_state, $node) {
  module_load_include('inc', 'vesafe_workflow', 'vesafe_workflow.api');
  $can_edit = user_access('edit node reviewers');
  $form_state['node'] = $node;
  $form['#can_edit']  = $can_edit;
  $form['#tree'] = TRUE;
  $form['#theme'] = 'vesafe_workflow_reviewing_form';
  if (isset($form_state['rows'])) {
    $rows = $form_state['rows'];
  }
  else {
    $rows = vesafe_workflow_get_node_reviewers($node->nid, FALSE);
  }
  $form_state['rows'] = $rows;
  $weight = 0;
  foreach ($rows as $uid => $row) {
    $form['rows'][$uid]['#row'] = $row;
    $form['rows'][$uid]['weight'] = array(
      '#type' => 'weight',
      '#title' => t('Weight'),
      '#title_display' => 'invisible',
      '#default_value' => (-10 + $weight),
      '#access' => $can_edit,
      '#attributes' => array('class' => array('user-weight')),
    );
    $form['rows'][$uid]['uid'] = array(
      '#type' => 'hidden',
      '#value' => $uid,
    );
    $form['rows'][$uid]['remove'] = array(
      '#type' => 'submit',
      '#name' => $uid,
      '#value' => t('Remove'),
      '#access' => $can_edit,
      '#submit' => array('vesafe_workflow_admin_reviewers_remove_row'),
    );
    $weight++;
  }
  $options = vesafe_workflow_users_get_users_from_role_as_options('reviewer');
  $editors = vesafe_workflow_users_get_users_from_role_as_options('editor');
  foreach($editors as $uid => $name) {
    $options[$uid] = $name;
  }

  $form['add']['uid'] = array(
    '#type' => 'select',
    '#multiple' => FALSE,
    '#options' => $options,
    '#title' => t('Add another reviewer'),
    '#title_display' => 'invisible',
    '#access' => $can_edit,
  );
  $form['add']['submit'] = array(
    '#type' => 'submit',
    '#name' => 'adduser',
    '#value' => t('Add to queue'),
    '#access' => $can_edit,
    '#attributes' => array('class' => array('container-inline')),
    '#submit' => array('vesafe_workflow_admin_reviewers_add_row'),
  );
  $form['help'] = array(
    '#type' => 'markup',
    '#markup' =>
      t('<div><strong>Tip:</strong> Use the drag handlers to sort the users in the order you want them to have the content reviewed. <br />** - Temporary, not yet saved</div>'),
  );
  $form['content'] = array(
    'actions' => array(
      '#type' => 'actions',
      '#weight' => 20,
      'submit' => array(
        '#type' => 'submit',
        '#value' => t('Save'),
        '#access' => $can_edit,
      ),
    ),
  );
  return $form;
}

function vesafe_workflow_admin_reviewers_remove_row($form, &$form_state) {
  if (isset($form_state['triggering_element'])) {
    $triggering_element = $form_state['triggering_element'];
    if (isset($triggering_element['#name'])) {
      $uid = $triggering_element['#name'];
      unset($form_state['rows'][$uid]);
      unset($form_state['values']['rows'][$uid]);
      drupal_set_message(t('Changes made in this table will not be saved until you press Save'), 'warning');
      $form_state['rebuild'] = TRUE;
    }
  }
}

function vesafe_workflow_admin_reviewers_add_row($form, &$form_state) {
  if (!empty($form_state['input']['add']['uid'])) {
    $moderator = user_load($form_state['input']['add']['uid']);
    $moderator->vesafe_workflow_node_reviewing_saved = FALSE;
    $form_state['rows'][$moderator->uid] = $moderator;
    drupal_set_message(t('Changes made in this table will not be saved until you press Save'), 'warning');
    $form_state['rebuild'] = TRUE;
  }
}

/**
 * Themes the workflow_moderation_form form.
 *
 * @param array $variables
 *   Form variables
 *
 * @return string
 *   Form HTML
 */
function theme_vesafe_workflow_reviewing_form($variables) {
  $output = '';
  $form = $variables['form'];
  $rows = array();
  if (!empty($form['rows'])) {
    $items = element_children($form['rows']);
    $last = end($items);
    reset($items);
    foreach ($items as $uid) {
      $moderator = $form['rows'][$uid]['#row'];
      $status = '';
      if (isset($moderator->osha_workflow_node_reviewing)) {
        $val = $moderator->osha_workflow_node_reviewing->reviewed;
        if ($val === NULL) {
          // NULL - not reviewed yet.
          $status = t('Waiting to review');
        }
        else {
          $status = $val . (!empty($moderator->osha_workflow_node_reviewing->message) ? ' - ' . $moderator->osha_workflow_node_reviewing->message : '');
        }
      }
      $row = array();
      $name = check_plain($moderator->name);
      if (empty($moderator->vesafe_workflow_node_reviewing_saved)) {
        $name .= '<sup>**</sup>';
      }
      $row[] = $name;
      $row[] = check_plain($moderator->mail);
      $row[] = $status;
      $row[] = drupal_render($form['rows'][$uid]['remove']);
      $row[] = drupal_render($form['rows'][$uid]['weight']);
      $rows[] = array('data' => $row, 'class' => array('draggable'));
    }
  }
  $row = array(
    drupal_render($form['add']['uid']),
    drupal_render($form['add']['submit']),
    '',
    '',
    '',
  );
  $rows[] = $row;
  $caption = t('List of reviewers');

  $header = array(
    t('User'),
    t('Mail'),
    t('Status'),
    '',
  );
  if ($form['#can_edit']) {
    array_push($header, t('Order of notification'));
  }
  $table = array(
    '#theme' => 'table',
    '#caption' => $caption,
    '#header' => $header,
    '#attributes' => array(
      'id' => 'reviewers_table',
    ),
    '#rows' => $rows,
  );
  if (isset($form['moderation'])) {
    $output .= drupal_render($form['moderation']);
  }
  $output .= drupal_render($table);
  $output .= drupal_render_children($form);
  if ($form['#can_edit']) {
    drupal_add_tabledrag('reviewers_table', 'order', 'sibling', 'user-weight');
  }
  return $output;
}

/**
 * Implements hook_form_validate().
 */
function vesafe_workflow_node_reviewing_form_validate($form, $form_state) {
  if (empty($form_state['rows']) && $form_state['triggering_element']['#name'] != 'adduser') {
    form_set_error('enabled', t('Cannot have an empty moderation queue. Add at least one user or switch to another state!'));
  }
}


/**
 * Implements hook_form_submit().
 */
function vesafe_workflow_node_reviewing_form_submit($form, $form_state) {
  $users = array();
  $node = $form_state['node'];
  if (!empty($form_state['values']['rows'])) {
    $data = $form_state['values']['rows'];
    foreach ($data as $uid => $cfg) {
      $weight = $cfg['weight'];
      $users[$weight] = $uid;
    }
    ksort($users);
  }
  vesafe_workflow_set_node_reviewers($node->nid, $users);
}
