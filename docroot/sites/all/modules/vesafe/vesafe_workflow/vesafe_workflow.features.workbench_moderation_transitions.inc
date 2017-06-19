<?php
/**
 * @file
 * vesafe_workflow.features.workbench_moderation_transitions.inc
 */

/**
 * Implements hook_workbench_moderation_export_transitions().
 */
function vesafe_workflow_workbench_moderation_export_transitions() {
  $items = array(
    'draft:final_draft' => array(
      'from_name' => 'draft',
      'to_name' => 'final_draft',
      'name' => 'Send to Reviewer',
    ),
    'final_draft:draft' => array(
      'from_name' => 'draft',
      'to_name' => 'final_draft',
      'name' => 'Send back to editor',
    ),
    'draft:published' => array(
      'from_name' => 'draft',
      'to_name' => 'published',
      'name' => 'Publish',
    ),
    'final_draft:needs_review' => array(
      'from_name' => 'final_draft',
      'to_name' => 'needs_review',
      'name' => 'Send for review',
    ),
    'needs_review:final_draft' => array(
      'from_name' => 'needs_review',
      'to_name' => 'final_draft',
      'name' => 'Send back to reviewer',
    ),
    'needs_review:published' => array(
      'from_name' => 'needs_review',
      'to_name' => 'published',
      'name' => 'Publish',
    ),
    'needs_review:to_be_approved' => array(
      'from_name' => 'needs_review',
      'to_name' => 'to_be_approved',
      'name' => 'Send for approval',
    ),
    'ready_to_publish:final_draft' => array(
      'from_name' => 'ready_to_publish',
      'to_name' => 'final_draft',
      'name' => 'Send back to reviewer',
    ),
    'ready_to_publish:published' => array(
      'from_name' => 'ready_to_publish',
      'to_name' => 'published',
      'name' => 'Publish',
    ),
    'to_be_approved:final_draft' => array(
      'from_name' => 'to_be_approved',
      'to_name' => 'final_draft',
      'name' => 'Send back to reviewer',
    ),
    'to_be_approved:ready_to_publish' => array(
      'from_name' => 'to_be_approved',
      'to_name' => 'ready_to_publish',
      'name' => 'Send for publishing',
    ),
  );
  return $items;
}
