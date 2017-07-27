<?php
/**
 * @file
 * vesafe_workflow.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function vesafe_workflow_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'user-user-field_cmw_mail_notifications'.
  $field_instances['user-user-field_cmw_mail_notifications'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => 1,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_cmw_mail_notifications',
    'label' => 'Receive Workflow notifications via e-mail?',
    'required' => 0,
    'settings' => array(
      'entity_translation_sync' => FALSE,
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 41,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Receive Workflow notifications via e-mail?');

  return $field_instances;
}
