<?php

// This alias is used in install and update scripts.
// Rewrite it in your aliases.local.php as you need.

$aliases['staging'] = array(
  'uri' => 'test-vesafe.osha.europa.eu',
  'db-allows-remote' => TRUE,
  'remote-host' => 'osha-webs-stg-app01.mainstrat.com',
  'remote-user' => 'osha',
  'root' => '/expert/vesafe/docroot',
  'path-aliases' => array(
    '%files' => 'sites/default/files',
  ),
  'command-specific' => array(
    'sql-sync' => array(
      'simulate' => '1',
      'target-dump' => '/tmp/vesafe-source-dump-edw.sql.gz',
    ),
  ),
);

// Add your local aliases.
if (file_exists(dirname(__FILE__) . '/aliases.local.php')) {
  include dirname(__FILE__) . '/aliases.local.php';
}
