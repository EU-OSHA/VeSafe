<?php
/**
 * @file
 * vesafe_workflow.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function vesafe_workflow_user_default_roles() {
  $roles = array();

  // Exported role: approver.
  $roles['approver'] = array(
    'name' => 'approver',
    'weight' => 3,
  );

  // Exported role: editor.
  $roles['editor'] = array(
    'name' => 'editor',
    'weight' => 6,
  );

  // Exported role: project manager.
  $roles['project manager'] = array(
    'name' => 'project manager',
    'weight' => 4,
  );

  // Exported role: reviewer.
  $roles['reviewer'] = array(
    'name' => 'reviewer',
    'weight' => 5,
  );

  return $roles;
}
