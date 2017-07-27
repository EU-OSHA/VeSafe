<?php
/**
 * @file
 * vesafe_workflow.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function vesafe_workflow_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['vesafe_workflow-vesafe_workflow_info'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'vesafe_workflow_info',
    'i18n_block_language' => array(),
    'i18n_mode' => 0,
    'module' => 'vesafe_workflow',
    'node_types' => array(
      0 => 'good_practice',
      1 => 'key_article',
    ),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'osha_admin' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'osha_admin',
        'weight' => 0,
      ),
      'vesafe_frontend' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'vesafe_frontend',
        'weight' => -31,
      ),
    ),
    'title' => '<none>',
    'visibility' => 0,
  );

  return $export;
}
