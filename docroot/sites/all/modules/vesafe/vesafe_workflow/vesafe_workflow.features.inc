<?php
/**
 * @file
 * vesafe_workflow.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function vesafe_workflow_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "entity_collection" && $api == "entity_collection_bundles_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function vesafe_workflow_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_default_entity_collection().
 */
function vesafe_workflow_default_entity_collection() {
  $items = array();
  $items['approvers'] = entity_import('entity_collection', '{
    "type" : null,
    "name" : "approvers",
    "bid" : null,
    "title" : "Approvers",
    "cache" : null,
    "requiredcontexts" : [],
    "contexts" : [],
    "bundle" : "moderators_group",
    "style" : "entity_collection_style_flat",
    "row" : "entity_collection_row_view_mode",
    "settings" : {
      "row_settings" : { "style_per_row" : 1 },
      "style_settings" : [],
      "allowed_bundles" : {
        "node" : [],
        "taxonomy_term" : [],
        "comment" : [],
        "entity_collection" : [],
        "i18n_translation" : [],
        "redirect" : [],
        "search_api_server" : [],
        "search_api_index" : [],
        "file" : [],
        "taxonomy_vocabulary" : [],
        "tmgmt_job" : [],
        "tmgmt_job_item" : [],
        "tmgmt_message" : [],
        "tmgmt_translator" : [],
        "tmgmt_remote" : [],
        "tmgmt_local_task" : [],
        "tmgmt_local_task_item" : [],
        "user" : [ "user" ],
        "wysiwyg_profile" : [],
        "workbench_moderation_transition" : [],
        "rules_config" : []
      }
    },
    "rdf_mapping" : []
  }');
  $items['reviewers'] = entity_import('entity_collection', '{
    "type" : null,
    "name" : "reviewers",
    "bid" : null,
    "title" : "Reviewers",
    "cache" : null,
    "requiredcontexts" : [],
    "contexts" : [],
    "bundle" : "moderators_group",
    "style" : "entity_collection_style_flat",
    "row" : "entity_collection_row_view_mode",
    "settings" : {
      "row_settings" : { "style_per_row" : 1 },
      "style_settings" : [],
      "allowed_bundles" : {
        "node" : [],
        "taxonomy_term" : [],
        "entityqueue_subqueue" : [],
        "entity_collection" : [],
        "i18n_translation" : [],
        "match_redirect" : [],
        "linkchecker_link" : [],
        "linkchecker_node" : [],
        "redirect" : [],
        "search_api_server" : [],
        "search_api_index" : [],
        "search_api_sort" : [],
        "file" : [],
        "taxonomy_vocabulary" : [],
        "user" : [ "user" ],
        "node_approval" : [],
        "node_reviewing" : [],
        "wysiwyg_profile" : [],
        "workbench_moderation_transition" : [],
        "rules_config" : [],
        "menu_link" : []
      }
    },
    "rdf_mapping" : []
  }');
  return $items;
}
