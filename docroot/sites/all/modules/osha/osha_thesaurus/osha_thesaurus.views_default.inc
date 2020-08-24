<?php
/**
 * @file
 * osha_thesaurus.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function osha_thesaurus_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'thesaurus_back';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Thesaurus backend';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Thesaurus';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page'] = TRUE;
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options'] = '10, 50, 100';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = TRUE;
  $handler->display->display_options['style_plugin'] = 'table';
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['header']['result']['content'] = 'Total: @total';
  /* Footer: Global: Result summary */
  $handler->display->display_options['footer']['result']['id'] = 'result';
  $handler->display->display_options['footer']['result']['table'] = 'views';
  $handler->display->display_options['footer']['result']['field'] = 'result';
  $handler->display->display_options['footer']['result']['content'] = '<span class="result_summary">Displaying @start - @end of @total</span>';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Father */
  $handler->display->display_options['fields']['field_father']['id'] = 'field_father';
  $handler->display->display_options['fields']['field_father']['table'] = 'field_data_field_father';
  $handler->display->display_options['fields']['field_father']['field'] = 'field_father';
  $handler->display->display_options['fields']['field_father']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_father']['settings'] = array(
    'bypass_access' => 0,
    'link' => 0,
  );
  /* Field: Content: Full URL */
  $handler->display->display_options['fields']['field_full_url']['id'] = 'field_full_url';
  $handler->display->display_options['fields']['field_full_url']['table'] = 'field_data_field_full_url';
  $handler->display->display_options['fields']['field_full_url']['field'] = 'field_full_url';
  $handler->display->display_options['fields']['field_full_url']['element_label_colon'] = FALSE;
  /* Field: Content: ID */
  $handler->display->display_options['fields']['field_term_id']['id'] = 'field_term_id';
  $handler->display->display_options['fields']['field_term_id']['table'] = 'field_data_field_term_id';
  $handler->display->display_options['fields']['field_term_id']['field'] = 'field_term_id';
  $handler->display->display_options['fields']['field_term_id']['label'] = 'Term ID';
  $handler->display->display_options['fields']['field_term_id']['element_label_colon'] = FALSE;
  /* Field: Content: Definition */
  $handler->display->display_options['fields']['field_definition']['id'] = 'field_definition';
  $handler->display->display_options['fields']['field_definition']['table'] = 'field_data_field_definition';
  $handler->display->display_options['fields']['field_definition']['field'] = 'field_definition';
  $handler->display->display_options['fields']['field_definition']['element_label_colon'] = FALSE;
  /* Field: Content: Context */
  $handler->display->display_options['fields']['field_context']['id'] = 'field_context';
  $handler->display->display_options['fields']['field_context']['table'] = 'field_data_field_context';
  $handler->display->display_options['fields']['field_context']['field'] = 'field_context';
  $handler->display->display_options['fields']['field_context']['element_label_colon'] = FALSE;
  /* Field: Content: Synonyms */
  $handler->display->display_options['fields']['field_synonyms']['id'] = 'field_synonyms';
  $handler->display->display_options['fields']['field_synonyms']['table'] = 'field_data_field_synonyms';
  $handler->display->display_options['fields']['field_synonyms']['field'] = 'field_synonyms';
  $handler->display->display_options['fields']['field_synonyms']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_synonyms']['delta_offset'] = '0';
  /* Field: Content: Term reference */
  $handler->display->display_options['fields']['field_term_reference']['id'] = 'field_term_reference';
  $handler->display->display_options['fields']['field_term_reference']['table'] = 'field_data_field_term_reference';
  $handler->display->display_options['fields']['field_term_reference']['field'] = 'field_term_reference';
  $handler->display->display_options['fields']['field_term_reference']['element_label_colon'] = FALSE;
  /* Field: Content: Notes */
  $handler->display->display_options['fields']['field_notes']['id'] = 'field_notes';
  $handler->display->display_options['fields']['field_notes']['table'] = 'field_data_field_notes';
  $handler->display->display_options['fields']['field_notes']['field'] = 'field_notes';
  $handler->display->display_options['fields']['field_notes']['element_label_colon'] = FALSE;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['exclude'] = TRUE;
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  /* Field: Content: Delete link */
  $handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['label'] = '';
  $handler->display->display_options['fields']['delete_node']['exclude'] = TRUE;
  $handler->display->display_options['fields']['delete_node']['element_label_colon'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Action';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<ul class="links inline">
<li>[edit_node]</li>
<li>[delete_node]</li>
</ul>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'thesaurus' => 'thesaurus',
  );
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
  );

  /* Display: Thesaurus */
  $handler = $view->new_display('page', 'Thesaurus', 'page');
  $handler->display->display_options['path'] = 'admin/content/thesaurus';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Thesaurus';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Data export */
  $handler = $view->new_display('views_data_export', 'Data export', 'views_data_export_1');
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
    4 => '4',
    2 => '2',
    7 => '7',
    5 => '5',
    6 => '6',
  );
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_xls';
  $handler->display->display_options['style_options']['provide_file'] = 1;
  $handler->display->display_options['style_options']['filename'] = 'thesaurus.xls';
  $handler->display->display_options['style_options']['parent_sort'] = 1;
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['footer'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Father */
  $handler->display->display_options['fields']['field_father']['id'] = 'field_father';
  $handler->display->display_options['fields']['field_father']['table'] = 'field_data_field_father';
  $handler->display->display_options['fields']['field_father']['field'] = 'field_father';
  $handler->display->display_options['fields']['field_father']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_father']['settings'] = array(
    'bypass_access' => 0,
    'link' => 0,
  );
  /* Field: Content: Full URL */
  $handler->display->display_options['fields']['field_full_url']['id'] = 'field_full_url';
  $handler->display->display_options['fields']['field_full_url']['table'] = 'field_data_field_full_url';
  $handler->display->display_options['fields']['field_full_url']['field'] = 'field_full_url';
  $handler->display->display_options['fields']['field_full_url']['element_label_colon'] = FALSE;
  /* Field: Content: ID */
  $handler->display->display_options['fields']['field_term_id']['id'] = 'field_term_id';
  $handler->display->display_options['fields']['field_term_id']['table'] = 'field_data_field_term_id';
  $handler->display->display_options['fields']['field_term_id']['field'] = 'field_term_id';
  $handler->display->display_options['fields']['field_term_id']['label'] = 'Term ID';
  $handler->display->display_options['fields']['field_term_id']['element_label_colon'] = FALSE;
  /* Field: Content: Definition */
  $handler->display->display_options['fields']['field_definition']['id'] = 'field_definition';
  $handler->display->display_options['fields']['field_definition']['table'] = 'field_data_field_definition';
  $handler->display->display_options['fields']['field_definition']['field'] = 'field_definition';
  $handler->display->display_options['fields']['field_definition']['element_label_colon'] = FALSE;
  /* Field: Content: Context */
  $handler->display->display_options['fields']['field_context']['id'] = 'field_context';
  $handler->display->display_options['fields']['field_context']['table'] = 'field_data_field_context';
  $handler->display->display_options['fields']['field_context']['field'] = 'field_context';
  $handler->display->display_options['fields']['field_context']['element_label_colon'] = FALSE;
  /* Field: Content: Synonyms */
  $handler->display->display_options['fields']['field_synonyms']['id'] = 'field_synonyms';
  $handler->display->display_options['fields']['field_synonyms']['table'] = 'field_data_field_synonyms';
  $handler->display->display_options['fields']['field_synonyms']['field'] = 'field_synonyms';
  $handler->display->display_options['fields']['field_synonyms']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_synonyms']['delta_offset'] = '0';
  /* Field: Content: Term reference */
  $handler->display->display_options['fields']['field_term_reference']['id'] = 'field_term_reference';
  $handler->display->display_options['fields']['field_term_reference']['table'] = 'field_data_field_term_reference';
  $handler->display->display_options['fields']['field_term_reference']['field'] = 'field_term_reference';
  $handler->display->display_options['fields']['field_term_reference']['element_label_colon'] = FALSE;
  /* Field: Content: Notes */
  $handler->display->display_options['fields']['field_notes']['id'] = 'field_notes';
  $handler->display->display_options['fields']['field_notes']['table'] = 'field_data_field_notes';
  $handler->display->display_options['fields']['field_notes']['field'] = 'field_notes';
  $handler->display->display_options['fields']['field_notes']['element_label_colon'] = FALSE;
  $handler->display->display_options['path'] = 'admin/content/thesaurus-export';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Thesaurus List with Tree */
  $handler = $view->new_display('page', 'Thesaurus List with Tree', 'page_1');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'tree';
  $handler->display->display_options['style_options']['main_field'] = 'nid';
  $handler->display->display_options['style_options']['parent_field'] = 'field_father';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Father */
  $handler->display->display_options['fields']['field_father']['id'] = 'field_father';
  $handler->display->display_options['fields']['field_father']['table'] = 'field_data_field_father';
  $handler->display->display_options['fields']['field_father']['field'] = 'field_father';
  $handler->display->display_options['fields']['field_father']['label'] = '';
  $handler->display->display_options['fields']['field_father']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_father']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_father']['settings'] = array(
    'bypass_access' => 0,
    'link' => 0,
  );
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['path'] = 'admin/content/thesaurus-tree';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Thesaurus - Tree';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Entity Reference View Widget */
  $handler = $view->new_display('entityreference_view_widget', 'Entity Reference View Widget', 'entityreference_view_widget_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
    4 => '4',
    2 => '2',
    7 => '7',
    5 => '5',
    6 => '6',
  );
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'tree';
  $handler->display->display_options['style_options']['main_field'] = 'nid';
  $handler->display->display_options['style_options']['parent_field'] = 'field_father';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['footer'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Father */
  $handler->display->display_options['fields']['field_father']['id'] = 'field_father';
  $handler->display->display_options['fields']['field_father']['table'] = 'field_data_field_father';
  $handler->display->display_options['fields']['field_father']['field'] = 'field_father';
  $handler->display->display_options['fields']['field_father']['label'] = '';
  $handler->display->display_options['fields']['field_father']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_father']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_father']['settings'] = array(
    'bypass_access' => 0,
    'link' => 0,
  );
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Entity Reference View Widget Checkbox: Content */
  $handler->display->display_options['fields']['entityreference_view_widget']['id'] = 'entityreference_view_widget';
  $handler->display->display_options['fields']['entityreference_view_widget']['table'] = 'node';
  $handler->display->display_options['fields']['entityreference_view_widget']['field'] = 'entityreference_view_widget';
  $handler->display->display_options['fields']['entityreference_view_widget']['label'] = '';
  $handler->display->display_options['fields']['entityreference_view_widget']['exclude'] = TRUE;
  $handler->display->display_options['fields']['entityreference_view_widget']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['entityreference_view_widget']['ervw']['force_single'] = 1;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="thesaurus_element_select">[entityreference_view_widget]</div><div class="thesaurus_element_select title">[title]</div>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $translatables['thesaurus_back'] = array(
    t('Master'),
    t('Thesaurus'),
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
    t('Total: @total'),
    t('<span class="result_summary">Displaying @start - @end of @total</span>'),
    t('Title'),
    t('Father'),
    t('Full URL'),
    t('Term ID'),
    t('Definition'),
    t('Context'),
    t('Synonyms'),
    t('Term reference'),
    t('Notes'),
    t('Action'),
    t('<ul class="links inline">
<li>[edit_node]</li>
<li>[delete_node]</li>
</ul>'),
    t('Data export'),
    t('Thesaurus List with Tree'),
    t('Entity Reference View Widget'),
    t('<div class="thesaurus_element_select">[entityreference_view_widget]</div><div class="thesaurus_element_select title">[title]</div>'),
  );
  $export['thesaurus_back'] = $view;

  return $export;
}
