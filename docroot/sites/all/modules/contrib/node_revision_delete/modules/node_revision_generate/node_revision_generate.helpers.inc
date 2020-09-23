<?php

/**
 * @file
 * Helper functions.
 */

/**
 * Get the available nodes to generate revisions.
 *
 * Returns the ids of the available nodes to generate the revisions and the
 * next date (Unix timestamp) of the revision to be generated for that node.
 *
 * @param array $bundles
 *   An array with the selected content types to generate node revisions.
 * @param int $revisions_age
 *   Interval in Unix timestamp format to add to the last revision date of the
 *   node.
 *
 * @return array
 *   Returns the available nodes ids to generate the revisions and its next
 *   revision date.
 */
function _node_revision_generate_get_available_nodes_for_revisions(array $bundles, $revisions_age) {
  // Variable with the placeholders arguments needed for the expression.
  $interval_time = array(
    ':interval' => $revisions_age,
    ':current_time' => REQUEST_TIME,
  );

  $query = db_select('node', 'n');
  // Get/check the last revision (vid).
  $query->leftJoin('node_revision', 'r', 'n.vid = r.vid');
  // Get the node id to generate revisions.
  $query->fields('n', array('nid'));
  // Get timestamp to calculate the number of revisions.
  $query->fields('r', array('timestamp'));
  // Get nodes with title to avoid some error on save it.
  $query->isNotNull('n.title');
  // Get nodes of selected content types (bundles).
  $query->condition('n.type', $bundles);
  // Get only the published nodes.
  $query->condition('n.status', 1);
  // Check the next date to generate the revision be <= current date.
  $query->where('r.timestamp + :interval <= :current_time', $interval_time);
  // Return the available nodes ids and its next revision date, as array.
  return $query->execute()->fetchAll();
}
