<?php
/**
 * @file
 * vesafe_structure.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function vesafe_structure_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "captcha" && $api == "captcha") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_entityqueue_api().
 */
function vesafe_structure_entityqueue_api($module = NULL, $api = NULL) {
  if ($module == "entityqueue" && $api == "entityqueue_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function vesafe_structure_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function vesafe_structure_node_info() {
  $items = array(
    'article' => array(
      'name' => 'Article',
      'base' => 'node_content',
      'description' => 'Articles are static content part of the vehicle safety portal',
      'has_title' => '1',
      'title_label' => 'Title',
      'help' => '',
    ),
    'did_you_know_slide' => array(
      'name' => 'Did you know slide',
      'base' => 'node_content',
      'description' => 'This content appears in the "Did you know?" section of the home page',
      'has_title' => '1',
      'title_label' => 'Title',
      'help' => '',
    ),
    'good_practice' => array(
      'name' => 'Good practice',
      'base' => 'node_content',
      'description' => 'Content appearing in the Good practices section of the vehicle safety portal',
      'has_title' => '1',
      'title_label' => 'Title',
      'help' => '',
    ),
    'key_article' => array(
      'name' => 'Key article',
      'base' => 'node_content',
      'description' => 'This content appears in the Themes section of the vehicle safety portal',
      'has_title' => '1',
      'title_label' => 'Title',
      'help' => '',
    ),
    'key_article_theme' => array(
      'name' => 'Key article theme',
      'base' => 'node_content',
      'description' => 'Key article themes are linked to key articles',
      'has_title' => '1',
      'title_label' => 'Title',
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
