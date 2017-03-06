<?php
/**
 * Render footer menu as nav-pills.
 */
function bootstrap_menu_tree__menu_footer_menu(&$variables) {
  return '<ul class="menu nav nav-pills">' . $variables['tree'] . '</ul>';
}


/**
 * Implements hook_path_breadcrumbs_view_alter().
 *
 * {@inheritdoc}
 */
function vesafe_frontend_path_breadcrumbs_view_alter(&$breadcrumbs, $path_breadcrumbs, $contexts) {
  if (drupal_is_front_page()) {
    $breadcrumbs = null;
  }
}


/**
 * Implements hook_process_html_tag().
 */
function vesafe_frontend_process_html_tag(&$variables) {
  $tag = &$variables['element'];

  if ($tag['#tag'] == 'script') {
    $tag['#attributes']['type'] = 'text/javascript';
  }
}

function vesafe_frontend_preprocess_page(&$vars) {
  global $language;
  if (drupal_is_front_page()) {
    unset($vars['page']['content']['system_main']['default_message']);
  }
  $vars['logo'] = '/sites/all/themes/vesafe_frontend/images/eu-osha-logo/EU-OSHA-'.($language->language).'.png';
  $vars['eu_logo'] = '/sites/all/themes/vesafe_frontend/images/europeLogo.png';
  $vars['vesafe_logo'] = '/sites/all/themes/vesafe_frontend/images/vesafeLogo.gif';
}
