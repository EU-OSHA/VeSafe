<?php
/**
 * @file
 * vesafe_structure.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function vesafe_structure_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'home_page';
  $page->task = 'page';
  $page->admin_title = 'Home page';
  $page->admin_description = 'Vehicle safety home page';
  $page->path = 'index.html';
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
  $handler->name = 'page_home_page__panel';
  $handler->task = 'page';
  $handler->subtask = 'home_page';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Home page',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => 'homepage',
    'css_id' => 'homepage',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => 'panel',
  );
  $display = new panels_display();
  $display->layout = 'flexible';
  $display->layout_settings = array(
    'items' => array(
      'canvas' => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 'main',
        ),
        'parent' => NULL,
      ),
      'main' => array(
        'type' => 'column',
        'width' => 100,
        'width_type' => '%',
        'children' => array(
          0 => 'main-row',
          1 => 2,
          2 => 3,
          3 => 4,
        ),
        'parent' => 'canvas',
      ),
      'main-row' => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'center',
        ),
        'parent' => 'main',
      ),
      'center' => array(
        'type' => 'region',
        'title' => 'Head',
        'width' => 100,
        'width_type' => '%',
        'parent' => 'main-row',
        'class' => '',
        'hide_empty' => 0,
      ),
      2 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'taxonomy_navigation',
        ),
        'parent' => 'main',
        'class' => '',
        'hide_empty' => 0,
      ),
      'taxonomy_navigation' => array(
        'type' => 'region',
        'title' => 'Navigation intro',
        'width' => 100,
        'width_type' => '%',
        'parent' => '2',
        'class' => 'col-md-12',
        'hide_empty' => 0,
      ),
      3 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'vehicle_navigation',
          1 => 'risk_navigation',
        ),
        'parent' => 'main',
        'class' => '',
        'hide_empty' => 0,
      ),
      'vehicle_navigation' => array(
        'type' => 'region',
        'title' => 'Vehicle navigation',
        'width' => 50,
        'width_type' => '%',
        'parent' => '3',
        'class' => 'col-md-6',
        'hide_empty' => 0,
      ),
      'risk_navigation' => array(
        'type' => 'region',
        'title' => 'Risk navigation',
        'width' => 50,
        'width_type' => '%',
        'parent' => '3',
        'class' => 'col-md-6',
        'hide_empty' => 0,
      ),
      4 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'key_articles_introduction',
        ),
        'parent' => 'main',
        'class' => '',
        'hide_empty' => 0,
      ),
      'key_articles_introduction' => array(
        'type' => 'region',
        'title' => 'Key articles',
        'width' => 100,
        'width_type' => '%',
        'parent' => '4',
        'class' => 'col-md-12',
        'hide_empty' => 0,
      ),
    ),
  );
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
      'jumbotron' => NULL,
      'taxonomy_navigation' => NULL,
      'vehicle_navigation' => NULL,
      'risk_navigation' => NULL,
      'key_articles_introduction' => NULL,
      'did_you_know' => NULL,
      'roles' => NULL,
    ),
    'vehicle_navigation' => array(
      'style' => '-1',
    ),
  );
  $display->cache = array();
  $display->title = 'Welcome to the one stop shop for vehicle safety';
  $display->uuid = 'da281de1-7b2b-4e65-afa5-f1c6cae69151';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-ec1583a0-7db0-4071-a40a-be716535164f';
    $pane->panel = 'key_articles_introduction';
    $pane->type = 'block';
    $pane->subtype = 'views-key_articles-block';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Or select the area you work in',
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
    $pane->uuid = 'ec1583a0-7db0-4071-a40a-be716535164f';
    $display->content['new-ec1583a0-7db0-4071-a40a-be716535164f'] = $pane;
    $display->panels['key_articles_introduction'][0] = 'new-ec1583a0-7db0-4071-a40a-be716535164f';
    $pane = new stdClass();
    $pane->pid = 'new-430035bc-7474-4836-966d-45bae4ee307f';
    $pane->panel = 'risk_navigation';
    $pane->type = 'block';
    $pane->subtype = 'views-risks-block';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Filter by risk',
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
    $pane->uuid = '430035bc-7474-4836-966d-45bae4ee307f';
    $display->content['new-430035bc-7474-4836-966d-45bae4ee307f'] = $pane;
    $display->panels['risk_navigation'][0] = 'new-430035bc-7474-4836-966d-45bae4ee307f';
    $pane = new stdClass();
    $pane->pid = 'new-4577aab5-5111-40f0-8696-fa2e82d9f45c';
    $pane->panel = 'taxonomy_navigation';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => 'Select a vehicle type or risk',
      'title' => 'Select a vehicle type or risk',
      'title_heading' => 'h2',
      'body' => '<p>The main part of this guide are good practice examples for you to learn from. To find the good practices that are applicable to you we have&nbsp;tagged them by vehicle and by risk.</p>',
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
    $pane->uuid = '4577aab5-5111-40f0-8696-fa2e82d9f45c';
    $display->content['new-4577aab5-5111-40f0-8696-fa2e82d9f45c'] = $pane;
    $display->panels['taxonomy_navigation'][0] = 'new-4577aab5-5111-40f0-8696-fa2e82d9f45c';
    $pane = new stdClass();
    $pane->pid = 'new-3fd7c380-f032-47f5-b9c6-db1e32d89873';
    $pane->panel = 'vehicle_navigation';
    $pane->type = 'block';
    $pane->subtype = 'views-vehicles-block';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => 'Filter by vehicle',
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
    $pane->uuid = '3fd7c380-f032-47f5-b9c6-db1e32d89873';
    $display->content['new-3fd7c380-f032-47f5-b9c6-db1e32d89873'] = $pane;
    $display->panels['vehicle_navigation'][0] = 'new-3fd7c380-f032-47f5-b9c6-db1e32d89873';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['home_page'] = $page;

  return $pages;

}
