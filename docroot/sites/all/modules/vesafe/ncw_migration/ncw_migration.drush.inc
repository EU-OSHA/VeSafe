<?php

/**
 * @file
 * Drush for NCW migration.
 */

/**
 * Implements COMMANDFILE_drush_command().
 */
function ncw_migration_drush_command() {
  return array(
    'hwc-migrate-all' => array(
      'description' => t('Import all content from the corporate website'),
    ),
    'hwc-migrate-node' => array(
      'description' => t('Import single node'),
      'arguments' => array(
        'nid' => t('Node ID in NCW'),
      ),
      'required-arguments' => TRUE,
      'options' => array(
        'update' => t('Update existing migrated node'),
      ),
    ),
  );
}
/**
 * Migrate all.
 */
function drush_ncw_migration_hwc_migrate_all() {
  /* BE AWARE OF THE MIGRATIONS ORDERING! */
  $migrations = array(
    'tax_thesaurus',
  );
  foreach ($migrations as $migration) {
    ncw_migration_run_single($migration, FALSE);
  }
}

/**
 * Migrate node.
 */
function drush_ncw_migration_hwc_migrate_node($nid) {
  module_load_include('inc', 'ncw_migration', 'ncw_migration.migrate');
  $url = ncw_migration_datasource_url() . '/export/node/' . $nid;
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_URL, $url);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 0);
  curl_setopt($ch, CURLOPT_FILETIME, TRUE);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
  curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 5);
  $content = curl_exec($ch);
  $info = curl_getinfo($ch);
  curl_close($ch);
  if ($info['http_code'] == 200) {
    $node = json_decode($content);
    define('SINGLE_NODE_MIGRATION_NID', $nid);
    if ($m = Migration::getInstance($node->type)) {
      if (function_exists('drush_get_option')) {
        if (drush_get_option('update', FALSE)) {
          $m->prepareUpdate();
        }
      }
      $m->processImport();
    }
  }
  else {
    if (function_exists('drush_set_error')) {
      drush_set_error(t('Cannot stat remote node !url (HTTP status: !http_code)', array(
        '!url' => $url,
        'http_code' => $info['http_code'],
      )));
    }
  }
}
