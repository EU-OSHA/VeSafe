<?php
/**
 * @file
 * vesafe_structure.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function vesafe_structure_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer search and replace settings'.
  $permissions['administer search and replace settings'] = array(
    'name' => 'administer search and replace settings',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'search_and_replace',
  );

  // Exported permission: 'undo search and replace'.
  $permissions['undo search and replace'] = array(
    'name' => 'undo search and replace',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'search_and_replace',
  );

  // Exported permission: 'use search and replace'.
  $permissions['use search and replace'] = array(
    'name' => 'use search and replace',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'search_and_replace',
  );

  return $permissions;
}
