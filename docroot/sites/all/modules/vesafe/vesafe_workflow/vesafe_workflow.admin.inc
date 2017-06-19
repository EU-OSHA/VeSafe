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
      if (isset($moderator->vesafe_workflow_node_approval)) {
        $val = $moderator->vesafe_workflow_node_approval->approved;
        if ($val === NULL) {
          // NULL - not reviewed yet.
          // $status = t('Waiting to approve');
        }
        else {
          $status = ($last == $uid) ? ucfirst($val) : t('User created a new revision');
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
