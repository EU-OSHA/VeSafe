<?php
/**
 * @file
 * vesafe_workflow.features.workbench_moderation_states.inc
 */

/**
 * Implements hook_workbench_moderation_export_states().
 */
function vesafe_workflow_workbench_moderation_export_states() {
  $items = array(
    'draft' => array(
      'name' => 'draft',
      'label' => 'Draft',
      'description' => 'Editors can add and edit content in state draft',
      'weight' => -10,
    ),
    'final_draft' => array(
      'name' => 'final_draft',
      'label' => 'Final Draft',
      'description' => 'Editors, when done set the status to Final Draft',
      'weight' => -7,
    ),
    'needs_review' => array(
      'name' => 'needs_review',
      'label' => 'To Be Reviewed',
      'description' => 'Review Manager can set the Final Draft to To Be Reviewed or To Be Approved ',
      'weight' => -6,
    ),
    'published' => array(
      'name' => 'published',
      'label' => 'Published',
      'description' => 'Web team set the content from Ready To Publish to Published',
      'weight' => -3,
    ),
    'ready_to_publish' => array(
      'name' => 'ready_to_publish',
      'label' => 'Ready to Publish',
      'description' => 'After approval the content it is set to Ready to publish',
      'weight' => -3,
    ),
    'to_be_approved' => array(
      'name' => 'to_be_approved',
      'label' => 'To Be Approved',
      'description' => 'Review Manager can set the Final Draft to To Be Reviewed or To Be Approved ',
      'weight' => -5,
    ),
  );
  return $items;
}
