<?php
/**
 * @file
 * vesafe_pages_1.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function vesafe_pages_1_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'page_not_found';
  $page->task = 'page';
  $page->admin_title = 'Page not found';
  $page->admin_description = '';
  $page->path = 'page-not-found';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_page_not_found__panel_context_110ff01e-4abc-4bd9-af90-90bc3d26e94b';
  $handler->task = 'page';
  $handler->subtask = 'page_not_found';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => 'page-not-found',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
    'panels_breadcrumbs_state' => 1,
    'panels_breadcrumbs_titles' => 'Page not found',
    'panels_breadcrumbs_paths' => '<none>',
    'panels_breadcrumbs_home' => 1,
  );
  $display = new panels_display();
  $display->layout = 'twocol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'left' => NULL,
      'right' => NULL,
    ),
    'style' => 'default',
  );
  $display->cache = array();
  $display->title = 'Page not found';
  $display->uuid = 'd8a6c268-a64a-457a-9edd-4e1798fe9a91';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-24da57b8-c89a-4bbe-aed1-6591543767c0';
    $pane->panel = 'left';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => 'Page not found text',
      'title' => '',
      'title_heading' => 'h2',
      'body' => '<p>Sorry but we couldn\'t find the page you are looking for. Please check to make sure you\'ve typed the URL correctly. You may also want to search for what you are looking for.</p>',
      'format' => 'full_html',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '24da57b8-c89a-4bbe-aed1-6591543767c0';
    $display->content['new-24da57b8-c89a-4bbe-aed1-6591543767c0'] = $pane;
    $display->panels['left'][0] = 'new-24da57b8-c89a-4bbe-aed1-6591543767c0';
    $pane = new stdClass();
    $pane->pid = 'new-4d86044e-1c2e-4c15-a001-74029512864d';
    $pane->panel = 'right';
    $pane->type = 'block';
    $pane->subtype = 'vesafe_search-search_vesafe_sidebar';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '4d86044e-1c2e-4c15-a001-74029512864d';
    $display->content['new-4d86044e-1c2e-4c15-a001-74029512864d'] = $pane;
    $display->panels['right'][0] = 'new-4d86044e-1c2e-4c15-a001-74029512864d';
    $pane = new stdClass();
    $pane->pid = 'new-d7a5ece3-5ae1-49b6-a12a-d48c3b821bd4';
    $pane->panel = 'right';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => 'Go back to homepage',
      'title' => '',
      'title_heading' => 'h2',
      'body' => '<p><a href="/">Return to homepage</a></p>',
      'format' => 'full_html',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'd7a5ece3-5ae1-49b6-a12a-d48c3b821bd4';
    $display->content['new-d7a5ece3-5ae1-49b6-a12a-d48c3b821bd4'] = $pane;
    $display->panels['right'][1] = 'new-d7a5ece3-5ae1-49b6-a12a-d48c3b821bd4';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-24da57b8-c89a-4bbe-aed1-6591543767c0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['page_not_found'] = $page;

  return $pages;

}
