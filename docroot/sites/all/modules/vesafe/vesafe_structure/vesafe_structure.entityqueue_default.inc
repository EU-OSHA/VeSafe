<?php
/**
 * @file
 * vesafe_structure.entityqueue_default.inc
 */

/**
 * Implements hook_entityqueue_default_queues().
 */
function vesafe_structure_entityqueue_default_queues() {
  $export = array();

  $queue = new EntityQueue();
  $queue->disabled = FALSE; /* Edit this to true to make a default queue disabled initially */
  $queue->api_version = 1;
  $queue->name = 'did_you_know';
  $queue->label = 'Did you know';
  $queue->language = 'en';
  $queue->handler = 'simple';
  $queue->target_type = 'node';
  $queue->settings = array(
    'target_bundles' => array(
      'did_you_know_slide' => 'did_you_know_slide',
    ),
    'min_size' => '0',
    'max_size' => '0',
    'act_as_queue' => 1,
  );
  $export['did_you_know'] = $queue;

  $queue = new EntityQueue();
  $queue->disabled = FALSE; /* Edit this to true to make a default queue disabled initially */
  $queue->api_version = 1;
  $queue->name = 'frontpage_key_articles';
  $queue->label = 'Frontpage key articles';
  $queue->language = 'en';
  $queue->handler = 'simple';
  $queue->target_type = 'node';
  $queue->settings = array(
    'target_bundles' => array(
      'key_article' => 'key_article',
    ),
    'min_size' => '0',
    'max_size' => '0',
    'act_as_queue' => 0,
  );
  $export['frontpage_key_articles'] = $queue;

  return $export;
}
