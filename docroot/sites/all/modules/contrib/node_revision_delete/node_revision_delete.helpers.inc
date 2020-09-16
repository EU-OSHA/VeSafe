<?php

/**
 * @file
 * Helper functions.
 */

/**
 * Save the content type config variable.
 *
 * @param string $content_type
 *   Content type machine name.
 * @param int $minimum_revisions_to_keep
 *   Minimum number of revisions to keep.
 * @param int $minimum_age_to_delete
 *   Minimum age in months of revision to delete.
 * @param int $when_to_delete
 *   Number of inactivity months to wait for delete a revision.
 */
function _node_revision_delete_save_content_type_config($content_type, $minimum_revisions_to_keep, $minimum_age_to_delete, $when_to_delete) {
  // Getting the variables with the content types configuration.
  $node_revision_delete_track = variable_get('node_revision_delete_track');
  // Creating the content type info.
  $content_type_info = array(
    'minimum_revisions_to_keep' => $minimum_revisions_to_keep,
    'minimum_age_to_delete' => $minimum_age_to_delete,
    'when_to_delete' => $when_to_delete,
  );
  // Adding the info into te array.
  $node_revision_delete_track[$content_type] = $content_type_info;
  // Saving the values in the config.
  variable_set('node_revision_delete_track', $node_revision_delete_track);
}

/**
 * Delete the content type config variable.
 *
 * @param string $content_type
 *   Content type machine name.
 *
 * @return bool
 *   Return TRUE if the content type config was deleted or FALSE if not exists.
 */
function _node_revision_delete_delete_content_type_config($content_type) {
  // Getting the variables with the content types configuration.
  $node_revision_delete_track = variable_get('node_revision_delete_track');
  // Checking if the config exists.
  if (isset($node_revision_delete_track[$content_type])) {
    // Deleting the value from the array.
    unset($node_revision_delete_track[$content_type]);
    // Saving the values in the config.
    variable_set('node_revision_delete_track', $node_revision_delete_track);
    return TRUE;
  }
  return FALSE;
}

/**
 * Return the list of candidate nodes for node revision delete.
 *
 * @param string $content_type
 *   Content type machine name.
 * @param int $minimum_revisions_to_keep
 *   Minimum number of revisions to keep.
 * @param int $minimum_age_to_delete
 *   Minimum age of revisions to be deleted.
 * @param int $when_to_delete
 *   Minimum inactivity age to wait for delete a revision.
 *
 * @return array
 *   Array of nids.
 */
function _node_revision_delete_candidates($content_type, $minimum_revisions_to_keep, $minimum_age_to_delete, $when_to_delete) {

  // Get the time value for minimum age to delete.
  $minimum_age_time = _node_revision_delete_determine_time('minimum_age_to_delete', $content_type);

  // Get the time value for when to delete.
  $when_delete_time = _node_revision_delete_determine_time('when_to_delete', $content_type);

  // Get candidates based on node type, node age, and number of revisions to
  // keep. This determines which nodes have more than one revision based on the
  // variables. Also limit candidates by the minimum age variable.
  $result = db_query('SELECT nr.nid, nr.vid
    FROM {node_revision} nr
    INNER JOIN {node} n ON n.nid = nr.nid and n.vid <> nr.vid
    WHERE nr.timestamp < :minimum_age_time
        AND n.changed < :when_delete_time
        AND n.type = :content_type
    ORDER BY nid ASC', array(
      ':minimum_age_time' => $minimum_age_time,
      ':content_type' => $content_type,
      ':when_delete_time' => $when_delete_time,
    ));

  $candidates = array();
  foreach ($result as $row) {
    $candidates[] = (array) $row;
  }

  return $candidates;
}

/**
 * Return the time string for the config_name parameter.
 *
 * @param string $config_name
 *   The config name.
 * @param int $number
 *   The number for the $config_name parameter configuration.
 *
 * @return string
 *   The time string for the $config_name parameter.
 */
function _node_revision_delete_time_string($config_name, $number) {
  $config_name_time = variable_get('node_revision_delete_' . $config_name . '_time');
  // Is singular or plural?
  $time = _node_revision_delete_time_number_string($number, $config_name_time['time']);
  // Return the time string for the $config_name parameter.
  switch ($config_name) {
    case 'minimum_age_to_delete':
      return t('@number @time', array('@number' => $number, '@time' => $time));

    case 'when_to_delete':
      return t('After @number @time of inactivity', array('@number' => $number, '@time' => $time));
  }
}

/**
 * Update the max_number for a config name.
 *
 * We need to update the max_number in the existing content type configuration
 * if the new value (max_number) is lower than the actual, in this case the new
 * value will be the value for the content type.
 *
 * @param string $config_name
 *   Config name to update.
 * @param int $max_number
 *   The maximum number for $config_name parameter.
 */
function _node_revision_delete_update_time_max_number_config($config_name, $max_number) {
  $node_revision_delete_track = variable_get('node_revision_delete_track', array());
  $changed = FALSE;
  // Checking the when_to_delete value for all the configured content types.
  foreach ($node_revision_delete_track as $content_type => $content_type_info) {
    // If the new defined max_number is smaller than the defined when_to_delete
    // value in the config, we need to change the stored config value.
    if ($max_number < $content_type_info[$config_name]) {
      $node_revision_delete_track[$content_type][$config_name] = $max_number;
      $changed = TRUE;
    }
  }
  // Saving only if we have changes.
  if ($changed) {
    // Saving the values in the config.
    variable_set('node_revision_delete_track', $node_revision_delete_track);
  }
}

/**
 * Return the available values for time frequency.
 *
 * @param string $index
 *   The index to retrieve.
 *
 * @return array|string
 *   The index value (human readable value), or map when no index is provided.
 */
function _node_revision_delete_time_value($index = NULL) {
  $options_node_revision_delete_time = array(
    '-1'       => t('Never'),
    '0'        => t('Every time cron runs'),
    '3600'     => t('Every hour'),
    '86400'    => t('Everyday'),
    '604800'   => t('Every week'),
    '864000'   => t('Every 10 days'),
    '1296000'  => t('Every 15 days'),
    '2592000'  => t('Every month'),
    '7776000'  => t('Every 3 months'),
    '15552000' => t('Every 6 months'),
    '31536000' => t('Every year'),
    '63072000' => t('Every 2 years'),
  );

  if (isset($index) && isset($options_node_revision_delete_time[$index])) {
    return $options_node_revision_delete_time[$index];
  }
  else {
    return $options_node_revision_delete_time;
  }
}

/**
 * Return a mapping of the old word values to numeric equivalents.
 *
 * @param string $word
 *   The old word to map.
 *
 * @return array|string
 *   The numeric value when a word is provided or the whole map.
 */
function _node_revision_delete_word_to_time($word = '') {
  $word_map = array(
    'never'          => '-1',
    'every_time'     => '0',
    'every_hour'     => '3600',
    'everyday'       => '86400',
    'every_week'     => '604800',
    'every_10_days'  => '864000',
    'every_15_days'  => '1296000',
    'every_month'    => '2592000',
    'every_3_months' => '7776000',
    'every_6_months' => '15552000',
    'every_year'     => '31536000',
    'every_2_years'  => '63072000',
  );

  if (empty($word)) {
    return $word_map;
  }
  else {
    return $word_map[$word];
  }
}

/**
 * Return the time option in singular or plural.
 *
 * @param string $number
 *   The number.
 * @param string $time
 *   The time option (days, weeks or months).
 *
 * @return string
 *   The singular or plural value for the time.
 */
function _node_revision_delete_time_number_string($number, $time) {
  // Time options.
  $time_options = array(
    'days' => array(
      'singular' => t('day'),
      'plural' => t('days'),
    ),
    'weeks' => array(
      'singular' => t('week'),
      'plural' => t('weeks'),
    ),
    'months' => array(
      'singular' => t('month'),
      'plural' => t('months'),
    ),
  );

  return $number == 1 ? $time_options[$time]['singular'] : $time_options[$time]['plural'];
}

/**
 * Returns if a number is a positive integer.
 *
 * @param int $number
 *   The time option (days, weeks or months).
 *
 * @return bool
 *   TRUE if the number is integer positive, FALSE otherwise.
 *
 * @see element_validate_integer_positive()
 */
function _node_revision_delete_is_integer_positive($number) {
  if ($number !== '' && (!is_numeric($number) || intval($number) != $number || $number <= 0)) {
    return FALSE;
  }
  return TRUE;
}

/**
 * Private function to perform revision deletion.
 *
 * @param int $nid
 *   The node whose oldest revisions will be deleted.
 * @param int $minimum_revisions_to_keep
 *   Max amount of revisions to keep for this node.
 * @param bool $dry_run
 *   TRUE to test run without deleting revisions but seeing the output results,
 *   FALSE for a real node revision delete.
 *
 * @return object
 *   stdClass with list containing an array of deleted revisions
 *   and pending containing a boolean where TRUE means that there
 *   are more revisions to delete for this node.
 */
function _node_revision_delete_do_delete($nid, $minimum_revisions_to_keep, $dry_run = FALSE) {
  // Getting the number of revisions to remove in each cron run.
  $max = variable_get('node_revision_delete_cron', 50);

  // Get the minimum age for the nid.
  $minimum_age_time = _node_revision_delete_determine_time('minimum_age_to_delete', NULL, $nid);

  $node = new stdClass();
  $node->nid = $nid;
  $revisions = node_revision_list($node);

  // Remove current revision.
  $node = node_load($nid);
  foreach ($revisions as $key => $revision_node) {
    if ($node->vid == $key) {
      unset ($revisions[$key]);
      break;
    }
  }

  // POPO to keep track of deleted revisions and whether there are more
  // to be deleted on a next run.
  $deleted_revisions = new stdClass();
  $deleted_revisions->count = 0;
  $deleted_revisions->pending = FALSE;

  // Keep recent revisions.
  if (count($revisions) > $minimum_revisions_to_keep) {
    $revisions = array_slice($revisions, $minimum_revisions_to_keep);
  }
  else {
    return $deleted_revisions;
  }

  // Reverse the list so we start deleting oldest revisions first.
  $revisions = array_reverse($revisions);

  foreach ($revisions as $revision) {
    $revision_id = $revision->vid;

    // Skip revisions that are too new.
    if ($revision->timestamp > $minimum_age_time) {
      continue;
    }

    if ($dry_run ? $dry_run : node_revision_delete($revision_id)) {
      $deleted_revisions->count++;
      // Stop deleting if we hit the limit per cron run.
      if ($deleted_revisions->count == $max) {
        $deleted_revisions->pending = TRUE;
        break;
      }
    }
  }

  return $deleted_revisions;
}

/**
 * Get all revision that are older than current deleted revision.
 *
 * @param int $nid
 *   The node id.
 * @param int $currently_deleted_revision_id
 *   The current revision.
 *
 * @return array
 *   An array with the previous revisions.
 */
function _node_revision_delete_get_previous_revisions($nid, $currently_deleted_revision_id) {
  // Getting the node.
  $node = node_load($nid);
  // Getting all revisions of the current node, in all languages.
  $revision_ids = node_revision_list($node);
  // Adding a placeholder for the deleted revision, as our custom submit
  // function is executed after the core delete the current revision.
  $revision_ids[$currently_deleted_revision_id] = [];

  $revisions_before = [];

  if (count($revision_ids) > 1) {
    // Ordering the array.
    krsort($revision_ids);

    // Getting the prior revisions.
    $revisions_before = array_slice($revision_ids, array_search($currently_deleted_revision_id, array_keys($revision_ids)) + 1, NULL, TRUE);
  }

  return $revisions_before;
}

/**
 * Determine the time value for the node type or nid and variable type.
 *
 * @param string $variable_type
 *   The variable type.
 * @param string $node_type
 *   The node type, can be null.
 * @param int $nid
 *   The nid, can be null.
 *
 * @return int
 *   The timestamp representing the when delete for the node type or nid.
 */
function _node_revision_delete_determine_time($variable_type, $node_type = NULL, $nid = NULL) {

  // Get the node type for the nid.
  if (empty($node_type) && !empty($nid)) {
    $node_type = db_select('node', 'n')
      ->fields('n', array('type'))
      ->condition('n.nid', $nid)
      ->execute()
      ->fetchField();
  }

  // Get the variable value for the node type (or default).
  $track = variable_get('node_revision_delete_track', array());
  $time = REQUEST_TIME;
  $time_interval = variable_get('node_revision_delete_' . $variable_type . '_time')['time'];
  if (count($track) && !empty($node_type) && isset($track[$node_type])) {
    $time = $track[$node_type][$variable_type];
  }
  $time = strtotime('-' . $time . ' ' . $time_interval);

  return $time;
}

/**
 * Returns a donation message to print in module pages.
 *
 * @return string
 *   The donation message.
 */
function _node_revision_delete_get_donation_text() {
  return '<div class="description">' . t('If you would like to say thanks and support the development of this module, a <a target="_blank" href="@url">donation</a> will be much appreciated.', array('@url' => 'http://paypal.me/adriancid')) . '</div>';
}
