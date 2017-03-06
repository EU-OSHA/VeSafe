<?php
/**
 * @file
 * vesafe_pages_1.features.inc
 */

/**
 * Implements hook_entityqueue_api().
 */
function vesafe_pages_1_entityqueue_api($module = NULL, $api = NULL) {
  if ($module == "entityqueue" && $api == "entityqueue_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_ctools_plugin_api().
 */
function vesafe_pages_1_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "facetapi" && $api == "facetapi_defaults") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function vesafe_pages_1_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
