<?php

// This alias is used in install and update scripts.
// Rewrite it in your aliases.local.php as you need.

$aliases['staging'] = array(
  'uri' => 'http://vesafe.edw.ro',
  'db-allows-remote' => TRUE,
  'remote-host' => '5.9.54.24',
  'remote-user' => 'php',
  'root' => '/var/www/html/osha-vesafe/docroot',
  'path-aliases' => array(
    '%files' => 'sites/default/files',
  ),
  'command-specific' => array(
    'sql-sync' => array(
      'simulate' => '1',
      'source-dump' => '/tmp/osha-vesafe-dump-cristiroma.sql',
    ),
  ),
);

// Add your local aliases.
if (file_exists(dirname(__FILE__) . '/aliases.local.php')) {
  include dirname(__FILE__) . '/aliases.local.php';
}
