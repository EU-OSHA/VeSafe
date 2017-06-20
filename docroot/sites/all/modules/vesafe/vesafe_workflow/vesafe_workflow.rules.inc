<?php

/**
 * Implements hook_rules_event_info() on behalf of the node module.
 */
function vesafe_workflow_rules_event_info() {
  $items = array(
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
  );
  return $items;
}
