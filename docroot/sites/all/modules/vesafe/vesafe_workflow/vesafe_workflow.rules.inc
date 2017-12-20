<?php

/**
 * Implements hook_rules_event_info() on behalf of the node module.
 */
function vesafe_workflow_rules_event_info() {
  $items = array(
    'node_to_be_reviewed' => array(
      'label' => t('When setting a node to be reviewed'),
      'group' => t('Vesafe workflow'),
      'variables' => array(
        'node' => array(
          'type' => 'node',
          'label' => t('Node'),
        ),
        'user' => array(
          'type' => 'user',
          'label' => t('Next reviewer'),
        ),
      ),
      'access callback' => 'rules_node_integration_access',
    ),
    'node_to_be_approved' => array(
      'label' => t('When setting a node to be approved'),
      'group' => t('Vesafe workflow'),
      'variables' => array(
        'node' => array(
          'type' => 'node',
          'label' => t('Node'),
        ),
        'user' => array(
          'type' => 'user',
          'label' => t('Next approver'),
        ),
      ),
      'access callback' => 'rules_node_integration_access',
    ),
    'notify_pm_review' => array(
      'label' => t('When system wants to notify PM that content was not reviewed in a while'),
      'group' => t('Vesafe workflow'),
      'variables' => array(
        'content_type' => array(
          'type' => 'text',
          'label' => t('Content type label'),
        ),
        'content_type_key' => array(
          'type' => 'text',
          'label' => t('Content type key'),
        ),
      ),
      'access callback' => 'rules_node_integration_access',
    ),
  );
  return $items;
}


/**
 * Implements hook_rules_action_info().
 */
function vesafe_workflow_rules_action_info() {
  return array(
    'vesafe_workflow_mail' => array(
      'label' => t('VeSafe workflow mail with item count'),
      'group' => t('VeSafe'),
      'parameter' => array(
        'to' => array(
          'type' => 'text',
          'label' => t('To'),
          'description' => t('The e-mail address or addresses where the message will be sent to. The formatting of this string must comply with RFC 2822.'),
        ),
        'subject' => array(
          'type' => 'text',
          'label' => t('Subject'),
          'description' => t("The mail's subject."),
          'translatable' => TRUE,
        ),
        'message' => array(
          'type' => 'text',
          'label' => t('Message'),
          'description' => t("The mail's message body."),
          'translatable' => TRUE,
        ),
        'count_type' => array(
          'type' => 'list<integer>',
          'label' => t('Count type'),
          'options list' => 'vesafe_workflow_rules_count_type_list',
          'description' => t("The type of count to perform, depending on notification"),
          'translatable' => TRUE,
        ),
      ),
      'base' => 'vesafe_workflow_action_mail',
      'access callback' => 'rules_system_integration_access',
    ),
    'vesafe_workflow_mail_to_users_of_role' => array(
      'label' => t('VeSafe workflow mail to all users of a role with item count'),
      'group' => t('VeSafe'),
      'parameter' => array(
        'roles' => array(
          'type' => 'list<text>',
          'label' => t('Roles'),
          'options list' => 'entity_metadata_user_roles',
          'description' => t('Select the roles whose users should receive the mail.'),
        ),
        'subject' => array(
          'type' => 'text',
          'label' => t('Subject'),
          'description' => t("The mail's subject."),
        ),
        'message' => array(
          'type' => 'text',
          'label' => t('Message'),
          'description' => t("The mail's message body."),
        ),
        'count_type' => array(
          'type' => 'list<integer>',
          'label' => t('Count type'),
          'options list' => 'vesafe_workflow_rules_count_type_list',
          'description' => t("The type of count to perform, depending on notification"),
          'translatable' => TRUE,
        ),
      ),
      'base' => 'vesafe_workflow_action_mail_to_users_of_role',
      'access callback' => 'rules_system_integration_access',
    ),
  );
}


function vesafe_workflow_rules_count_type_list() {
  return array(
    OSHA_WORKFLOW_STATE_DRAFT => 'Draft',
    OSHA_WORKFLOW_STATE_FINAL_DRAFT => 'Final draft',
    OSHA_WORKFLOW_STATE_READY_TO_PUBLISH => 'Ready to publish',
    OSHA_WORKFLOW_STATE_TO_BE_APPROVED => 'To be approved',
    OSHA_WORKFLOW_STATE_TO_BE_REVIEWED => 'To be reviewed by EU-OSHA',
  );
}

function vesafe_workflow_action_mail($to, $subject, $message, $count_type, $settings, RulesState $state, RulesPlugin $element) {
  $approver = null;
  if (!empty($state->variables['user'])) {
    $approver = $state->variables['user']->value();
  }
  $type = array_pop($count_type);
  $item_count = VeSafeWorkflowEmailCount::count_items($type, $approver);
  $to = str_replace(array("\r", "\n"), '', $to);
  $message = str_replace('{{count}}', $item_count, $message);
  $params = array(
    'subject' => $subject,
    'message' => $message,
    'langcode' => 'en',
  );
  // Set a unique key for this mail.
  $name = isset($element->root()->name) ? $element->root()->name : 'unnamed';
  $key = 'vesafe_rules_action_mail_' . $name . '_' . $element->elementId();
  $language = language_default();

  $message = drupal_mail('rules', $key, $to, $language, $params);
  if ($message['result']) {
    watchdog('rules', 'Successfully sent email to %recipient', array('%recipient' => $to));
  }
}


function vesafe_workflow_action_mail_to_users_of_role($roles, $subject, $message, $count_type, $settings, RulesState $state, RulesPlugin $element) {
  $type = array_pop($count_type);
  $author = $state->variables['node']->author->value();
  $item_count = VeSafeWorkflowEmailCount::count_items($type, $author);
  $message = str_replace('{{count}}', $item_count, $message);

  // All authenticated users, which is everybody.
  if (in_array(DRUPAL_AUTHENTICATED_RID, $roles)) {
    $result = db_query('SELECT mail FROM {users} WHERE uid > 0');
  }
  else {
    $rids = implode(',', $roles);
    // Avoid sending emails to members of two or more target role groups.
    $result = db_query('SELECT DISTINCT u.mail FROM {users} u INNER JOIN {users_roles} r ON u.uid = r.uid WHERE r.rid IN ('. $rids .')');
  }

  // Now, actually send the mails.
  $params = array(
    'subject' => $subject,
    'message' => $message,
  );
  // Set a unique key for this mail.
  $name = isset($element->root()->name) ? $element->root()->name : 'unnamed';
  $key = 'vesafe_rules_action_mail_to_users_of_role_' . $name . '_' . $element->elementId();

  $message = array('result' => TRUE);
  foreach ($result as $row) {
    $message = drupal_mail('rules', $key, $row->mail, language_default(), $params);
    // If $message['result'] is FALSE, then it's likely that email sending is
    // failing at the moment, and we should just abort sending any more. If
    // however, $mesage['result'] is NULL, then it's likely that a module has
    // aborted sending this particular email to this particular user, and we
    // should just keep on sending emails to the other users.
    // For more information on the result value, see drupal_mail().
    if ($message['result'] === FALSE) {
      break;
    }
  }
  if ($message['result'] !== FALSE) {
    $role_names = array_intersect_key(user_roles(TRUE), array_flip($roles));
    watchdog('rules', 'Successfully sent email to the role(s) %roles.', array('%roles' => implode(', ', $role_names)));
  }
}