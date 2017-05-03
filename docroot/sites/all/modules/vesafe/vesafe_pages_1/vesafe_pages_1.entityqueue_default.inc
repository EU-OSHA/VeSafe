<?php
/**
 * @file
 * vesafe_pages_1.entityqueue_default.inc
 */

/**
 * Implements hook_entityqueue_default_queues().
 */
function vesafe_pages_1_entityqueue_default_queues() {
  $export = array();

  $queue = new EntityQueue();
  $queue->disabled = FALSE; /* Edit this to true to make a default queue disabled initially */
  $queue->api_version = 1;
  $queue->name = 'key_articles_introductory_page';
  $queue->label = 'Key Articles Introductory Page';
  $queue->language = 'en';
  $queue->handler = 'simple';
  $queue->target_type = 'node';
  $queue->settings = array(
    'target_bundles' => array(
      'key_article' => 'key_article',
    ),
    'min_size' => '3',
    'max_size' => '3',
    'act_as_queue' => 1,
  );
  $export['key_articles_introductory_page'] = $queue;

  return $export;
}
