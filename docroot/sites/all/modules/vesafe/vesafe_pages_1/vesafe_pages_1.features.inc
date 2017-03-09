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

/**
 * Implements hook_image_default_styles().
 */
function vesafe_pages_1_image_default_styles() {
  $styles = array();

  // Exported image style: good_practice_thumbnail.
  $styles['good_practice_thumbnail'] = array(
    'label' => 'Good Practice Thumbnail',
    'effects' => array(
      2 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => '',
          'height' => 186,
          'upscale' => 1,
        ),
        'weight' => -10,
      ),
      1 => array(
        'name' => 'image_crop',
        'data' => array(
          'width' => 270,
          'height' => 186,
          'anchor' => 'center-center',
        ),
        'weight' => -9,
      ),
    ),
  );

  return $styles;
}
