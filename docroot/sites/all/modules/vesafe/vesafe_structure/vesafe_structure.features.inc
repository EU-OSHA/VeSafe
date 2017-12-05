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
  if ($module == "file_entity" && $api == "file_default_displays") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "path_breadcrumbs" && $api == "path_breadcrumbs") {
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
 * Implements hook_image_default_styles().
 */
function vesafe_structure_image_default_styles() {
  $styles = array();

  // Exported image style: generic_background.
  $styles['generic_background'] = array(
    'label' => 'Generic background',
    'effects' => array(
      10 => array(
        'name' => 'manualcrop_crop_and_scale',
        'data' => array(
          'width' => 1000,
          'height' => 393,
          'upscale' => 1,
          'respectminimum' => 0,
          'onlyscaleifcrop' => 0,
          'style_name' => 'generic_background',
        ),
        'weight' => 0,
      ),
    ),
  );

  // Exported image style: good_practice_thumbnail.
  $styles['good_practice_thumbnail'] = array(
    'label' => 'Good practice thumbnail',
    'effects' => array(
      8 => array(
        'name' => 'manualcrop_crop_and_scale',
        'data' => array(
          'width' => 1000,
          'height' => 393,
          'upscale' => 1,
          'respectminimum' => 0,
          'onlyscaleifcrop' => 0,
          'style_name' => 'good_practice_thumbnail',
        ),
        'weight' => 0,
      ),
    ),
  );

  // Exported image style: key_article_thumbnail.
  $styles['key_article_thumbnail'] = array(
    'label' => 'Key article thumbnail',
    'effects' => array(
      9 => array(
        'name' => 'manualcrop_crop_and_scale',
        'data' => array(
          'width' => 420,
          'height' => 315,
          'upscale' => 1,
          'respectminimum' => 0,
          'onlyscaleifcrop' => 0,
          'style_name' => 'key_article_thumbnail',
        ),
        'weight' => 0,
      ),
    ),
  );

  return $styles;
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
      'description' => 'Content appearing in the Good practices section of the vehicle safety portal. You can download the template of the Factsheet <a target="_blank" href="/system/files/EU-OSHA_VS_Factsheet%20template.docx">here</a>',
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
    'webform' => array(
      'name' => 'Webform',
      'base' => 'node_content',
      'description' => 'Create a new form or questionnaire accessible to users. Submission results and statistics are recorded and accessible to privileged users.',
      'has_title' => '1',
      'title_label' => 'Title',
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
