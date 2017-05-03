<?php

/**
 * Module's configuration form.
 */
function vesafe_search_admin_form($form, &$form_state) {
  $form['vesafe_search_autocomplete'] = array(
    '#title' => 'Search autocomplete',
    '#type' => 'fieldset',
  );
  $form['vesafe_search_autocomplete']['vesafe_search_bundles'] = array(
    '#title' => 'Node types to search trough',
    '#type' => 'checkboxes',
    '#options' => node_type_get_names(),
    '#default_value' => variable_get('vesafe_search_bundles', array()),
  );
  $form['vesafe_search_autocomplete']['vesafe_search_ac_categ_limit'] = array(
    '#title' => 'Search AC categories',
    '#description' => 'Number of categories to show in Search Autocomplete',
    '#type' => 'textfield',
    '#default_value' => variable_get('vesafe_search_ac_categ_limit', 3),
  );
  $form['vesafe_search_autocomplete']['vesafe_search_ac_items_limit'] = array(
    '#title' => 'Search AC items',
    '#description' => 'Number of items per category to show in Search Autocomplete',
    '#type' => 'textfield',
    '#default_value' => variable_get('vesafe_search_ac_items_limit', 3),
  );
  $index_id = variable_get('vesafe_search_ac_index', 'default_solr_index');
  $form['vesafe_search_autocomplete']['vesafe_search_ac_index'] = array(
    '#title' => 'Search AC index',
    '#description' => 'Number of items per category to show in Search Autocomplete',
    '#type' => 'select',
    '#options' => search_api_index_options_list(),
    '#default_value' => $index_id,
  );
  $index = search_api_index_load($index_id);
  $search_fields = $index->getFulltextFields();
  $form['vesafe_search_autocomplete']['vesafe_search_ac_fields'] = array(
    '#title' => 'Search AC index',
    '#description' => 'Number of items per category to show in Search Autocomplete',
    '#type' => 'select',
    '#options' => drupal_map_assoc($search_fields),
    '#default_value' => variable_get('vesafe_search_ac_fields', array()),
    '#multiple' => TRUE,
  );
  return system_settings_form($form);
}
