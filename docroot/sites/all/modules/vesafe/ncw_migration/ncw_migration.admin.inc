<?php

/**
 * @file
 * Administration NCW migration functions.
 */

/**
 * NCW migration configuration form.
 */
function ncw_migration_config_form() {
  $form['title'] = array(
    '#markup' => '<h1>' . t('NCW migration configuration') . '</h1>',
  );
  if (!isset($form['#theme'])) {
    $form['#theme'] = 'system_settings_form';
  }
  $note = 'To disable one of the migrations set the URL empty then Save. Endpoints should expose JSON data';
  if (module_exists('migrate_ui')) {
    $note .= ' ' . l(t('Visit migration status overview'), 'admin/content/migrate/groups/ncw');
  }
  $form['note'] = array(
    '#type' => 'item',
    '#markup' => $note,
    '#weight' => -1,
  );

  foreach (migrate_migrations() as $machine_name => $meta) {
    $migration = MigrationBase::getInstance($machine_name);
    if ($group = $migration->getGroup()) {
      // Filter all migrations from NCW group.
      if ('ncw' == $group->getName()) {
        $form['migration']["ncw_migration_${machine_name}_url"] = array(
          '#type' => 'textfield',
          '#title' => ucfirst(str_replace('_', ' ', $machine_name)) . ' endpoint URI',
          '#default_value' => variable_get("ncw_migration_${machine_name}_url"),
          '#description' => t('Uri that will be appended to the Root endpoint URL defined'),
          '#size' => 90,
        );
      }
    }
    uksort($form['migration'], 'strcmp');
  }

  $form['migration']["ncw_migration_root_url"] = array(
    '#type' => 'textfield',
    '#title' => t('Root endpoint URL'),
    '#default_value' => variable_get("ncw_migration_root_url", 'http://test.osha.europa.eu'),
    '#size' => 90,
  );

  $form = system_settings_form($form);

  return $form;
}
