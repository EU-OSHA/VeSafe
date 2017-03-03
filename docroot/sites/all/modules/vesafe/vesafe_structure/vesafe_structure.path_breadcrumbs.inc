<?php
/**
 * @file
 * vesafe_structure.path_breadcrumbs.inc
 */

/**
 * Implements hook_path_breadcrumbs_settings_info().
 */
function vesafe_structure_path_breadcrumbs_settings_info() {
  $export = array();

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'good_practice_node';
  $path_breadcrumb->name = 'Good practice node';
  $path_breadcrumb->path = 'node/%node';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Good Practices',
      1 => '!page_title',
    ),
    'paths' => array(
      0 => 'node/241',
      1 => '<none>',
    ),
    'home' => 1,
    'translatable' => 0,
    'arguments' => array(
      'node' => array(
        'position' => 1,
        'argument' => 'entity_id:node',
        'settings' => array(
          'identifier' => 'Content: ID',
        ),
      ),
    ),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'entity_bundle:node',
          'settings' => array(
            'type' => array(
              'good_practice' => 'good_practice',
            ),
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = 0;
  $export['good_practice_node'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'node_page';
  $path_breadcrumb->name = 'Node page';
  $path_breadcrumb->path = 'node/%node';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => '!page_title',
    ),
    'paths' => array(
      0 => '<none>',
    ),
    'home' => 1,
    'translatable' => 0,
    'arguments' => array(
      'node' => array(
        'position' => 1,
      ),
    ),
    'access' => array(),
  );
  $path_breadcrumb->weight = 0;
  $export['node_page'] = $path_breadcrumb;

  return $export;
}
