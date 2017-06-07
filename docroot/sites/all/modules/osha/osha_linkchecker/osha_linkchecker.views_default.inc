<?php
/**
 * @file
 * osha_linkchecker.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function osha_linkchecker_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'broken_links';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'linkchecker_link';
  $view->human_name = 'Linkchecker Broken Links';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = ' Linkchecker Broken Links';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Relationship: Linkchecker Links: Link ID */
  $handler->display->display_options['relationships']['lid']['id'] = 'lid';
  $handler->display->display_options['relationships']['lid']['table'] = 'linkchecker_link';
  $handler->display->display_options['relationships']['lid']['field'] = 'lid';
  $handler->display->display_options['relationships']['lid']['required'] = TRUE;
  /* Relationship: Linkchecker Node Links: Node */
  $handler->display->display_options['relationships']['nid']['id'] = 'nid';
  $handler->display->display_options['relationships']['nid']['table'] = 'linkchecker_node';
  $handler->display->display_options['relationships']['nid']['field'] = 'nid';
  $handler->display->display_options['relationships']['nid']['relationship'] = 'lid';
  $handler->display->display_options['relationships']['nid']['required'] = TRUE;
  /* Field: Linkchecker Links: Code */
  $handler->display->display_options['fields']['code']['id'] = 'code';
  $handler->display->display_options['fields']['code']['table'] = 'linkchecker_link';
  $handler->display->display_options['fields']['code']['field'] = 'code';
  /* Field: Linkchecker Links: URL */
  $handler->display->display_options['fields']['url']['id'] = 'url';
  $handler->display->display_options['fields']['url']['table'] = 'linkchecker_link';
  $handler->display->display_options['fields']['url']['field'] = 'url';
  $handler->display->display_options['fields']['url']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['url']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['url']['alter']['path'] = '[url]';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'nid';
  /* Filter criterion: Linkchecker Links: Code */
  $handler->display->display_options['filters']['code']['id'] = 'code';
  $handler->display->display_options['filters']['code']['table'] = 'linkchecker_link';
  $handler->display->display_options['filters']['code']['field'] = 'code';
  $handler->display->display_options['filters']['code']['value'] = array(
    0 => '0',
    -101 => '-101',
    -111 => '-111',
    400 => '400',
    401 => '401',
    403 => '403',
    404 => '404',
  );
  /* Filter criterion: Linkchecker Links: Error */
  $handler->display->display_options['filters']['error']['id'] = 'error';
  $handler->display->display_options['filters']['error']['table'] = 'linkchecker_link';
  $handler->display->display_options['filters']['error']['field'] = 'error';
  $handler->display->display_options['filters']['error']['operator'] = '!=';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/content/linkchecker-broken-links';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Broken Links';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['broken_links'] = array(
    t('Master'),
    t(' Linkchecker Broken Links'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Linkchecker Node Links'),
    t('Content'),
    t('Code'),
    t('URL'),
    t('Title'),
    t('Page'),
  );
  $export['broken_links'] = $view;

  return $export;
}
