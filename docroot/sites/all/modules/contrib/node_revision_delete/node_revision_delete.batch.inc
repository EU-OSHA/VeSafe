<?php

/**
 * @file
 * Batch API callbacks for node_revision_delete module.
 */

/**
 * Process for one batch step, deleting a revision.
 *
 * @param string $content_type
 *   Content type machine name.
 * @param int $minimum_revisions_to_keep
 *   Minimum number of revisions to keep.
 * @param int $minimum_age_to_delete
 *   Minimum age in months of revision to delete.
 * @param int $when_to_delete
 *   Number of inactivity months to wait for delete a revision.
 * @param bool $dry_run
 *   Boolean to know if we must delete the revision or only show how the
 *   will works.
 * @param array|\ArrayObject $context
 *   The context.
 */
function node_revision_delete_batch_process($content_type, $minimum_revisions_to_keep, $minimum_age_to_delete, $when_to_delete, $dry_run, &$context) {
  if (!isset($context['sandbox']['nids'])) {
    // Set initial values.
    $candidates = _node_revision_delete_candidates($content_type, $minimum_revisions_to_keep, $minimum_age_to_delete, $when_to_delete);
    $context['sandbox']['nids'] = array_values(array_unique(array_column($candidates, 'nid')));
    $context['sandbox']['current'] = 0;
    $context['sandbox']['total'] = count($candidates);
  }

  // Perform the actual revision deletion.
  $nid = $context['sandbox']['nids'][$context['sandbox']['current']];
  if (isset($nid)) {
    $deleted_revisions = _node_revision_delete_do_delete($nid, $minimum_revisions_to_keep, $dry_run);
  }
  // Save results for final report.
  if (isset($context['results'][$nid])) {
    $context['results'][$nid] += $deleted_revisions->count;
  }
  else {
    $context['results'][$nid] = $deleted_revisions->count;
  }

  // Evaluate if we are done with the current node.
  if (empty($deleted_revisions->pending)) {
    $context['sandbox']['current']++;
  }

  // Inform the batch engine that we are not finished,
  // and provide an estimation of the completion level we reached.
  $context['finished'] = empty($context['sandbox']['nids']) ? 1 : $context['sandbox']['current'] / $context['sandbox']['total'];
}

/**
 * Finishing bulk operations for revision deletion.
 *
 * @param bool $success
 *   A boolean indicating the operations success.
 * @param array $results
 *   The results variables.
 * @param array $operations
 *   The operations.
 */
function node_revision_delete_batch_finish($success, array $results, array $operations) {
  if ($success) {
    foreach ($results as $nid => $count) {
      drupal_set_message(t('Deleted @count revisions for node with nid @nid.', array(
        '@count' => $count,
        '@nid' => $nid,
      )));
    }
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    $message_variables = array(
      '%error_operation' => $error_operation[0],
      '@arguments' => print_r($error_operation[1], TRUE),
    );
    $message = t('An error occurred while processing %error_operation with arguments: @arguments', $message_variables);
    drupal_set_message($message, 'error');
  }
}

/**
 * Process for one batch step, deleting a prior revision.
 *
 * @param int $nid
 *   The node id.
 * @param int $revision
 *   The current revision.
 * @param array $context
 *   The context.
 */
function node_revision_delete_batch_delete_prior_revisions($nid, $revision, array &$context) {
  if (empty($context['results'])) {
    $context['results']['revisions'] = 0;
  }

  // Count the number of revisions deleted.
  $context['results']['revisions']++;
  $context['results']['node'] = $nid;
  $context['message'] = t('Processing revision: @id', array('@id' => $revision));

  node_revision_delete($revision);
}

/**
 * Finishing bulk operations for prior revision deletion.
 *
 * @param bool $success
 *   A boolean indicating the operations success.
 * @param array $results
 *   The results variables.
 * @param array $operations
 *   The operations.
 */
function node_revision_delete_batch_delete_prior_revisions_finished($success, array $results, array $operations) {
  if ($success) {
    $message = format_plural($results['revisions'], 'One prior revision deleted.', '@count prior revisions deleted.');
    drupal_set_message($message);

    // Getting the node.
    $node = node_load($results['node']);
    // Get all revisions of the current node.
    $revision_ids = node_revision_list($node);
    // In case there are no more revisions, we should be redirected to the node
    // view as the node revision page does not exist.
    if (count($revision_ids) == 1) {
      drupal_goto('node/' . $results['node']);
    }

  }
  else {
    $error_operation = reset($operations);
    drupal_set_message(t('An error occurred while processing @operation with arguments: @args', [
      '@operation' => $error_operation[0],
      '@args' => print_r($error_operation[0], TRUE),
    ]));
  }
}
