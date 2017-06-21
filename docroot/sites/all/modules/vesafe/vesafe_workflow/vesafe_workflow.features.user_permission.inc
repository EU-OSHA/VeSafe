<?php
/**
 * @file
 * vesafe_workflow.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function vesafe_workflow_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access administration pages'.
  $permissions['access administration pages'] = array(
    'name' => 'access administration pages',
    'roles' => array(
      'administrator' => 'administrator',
      'approver' => 'approver',
      'editor' => 'editor',
      'project manager' => 'project manager',
      'reviewer' => 'reviewer',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access content overview'.
  $permissions['access content overview'] = array(
    'name' => 'access content overview',
    'roles' => array(
      'administrator' => 'administrator',
      'approver' => 'approver',
      'editor' => 'editor',
      'project manager' => 'project manager',
      'reviewer' => 'reviewer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access site in maintenance mode'.
  $permissions['access site in maintenance mode'] = array(
    'name' => 'access site in maintenance mode',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'create good_practice content'.
  $permissions['create good_practice content'] = array(
    'name' => 'create good_practice content',
    'roles' => array(
      'editor' => 'editor',
      'project manager' => 'project manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create key_article content'.
  $permissions['create key_article content'] = array(
    'name' => 'create key_article content',
    'roles' => array(
      'editor' => 'editor',
      'project manager' => 'project manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any content in draft'.
  $permissions['delete any content in draft'] = array(
    'name' => 'delete any content in draft',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'vesafe_workflow',
  );

  // Exported permission: 'delete any content in final_draft'.
  $permissions['delete any content in final_draft'] = array(
    'name' => 'delete any content in final_draft',
    'roles' => array(),
    'module' => 'vesafe_workflow',
  );

  // Exported permission: 'delete any content in needs_review'.
  $permissions['delete any content in needs_review'] = array(
    'name' => 'delete any content in needs_review',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'vesafe_workflow',
  );

  // Exported permission: 'delete any content in published'.
  $permissions['delete any content in published'] = array(
    'name' => 'delete any content in published',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'vesafe_workflow',
  );

  // Exported permission: 'delete any content in ready_to_publish'.
  $permissions['delete any content in ready_to_publish'] = array(
    'name' => 'delete any content in ready_to_publish',
    'roles' => array(),
    'module' => 'vesafe_workflow',
  );

  // Exported permission: 'delete any content in to_be_approved'.
  $permissions['delete any content in to_be_approved'] = array(
    'name' => 'delete any content in to_be_approved',
    'roles' => array(),
    'module' => 'vesafe_workflow',
  );

  // Exported permission: 'delete any good_practice content'.
  $permissions['delete any good_practice content'] = array(
    'name' => 'delete any good_practice content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any key_article content'.
  $permissions['delete any key_article content'] = array(
    'name' => 'delete any key_article content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own good_practice content'.
  $permissions['delete own good_practice content'] = array(
    'name' => 'delete own good_practice content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own key_article content'.
  $permissions['delete own key_article content'] = array(
    'name' => 'delete own key_article content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any content in draft'.
  $permissions['edit any content in draft'] = array(
    'name' => 'edit any content in draft',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'vesafe_workflow',
  );

  // Exported permission: 'edit any content in final_draft'.
  $permissions['edit any content in final_draft'] = array(
    'name' => 'edit any content in final_draft',
    'roles' => array(
      'reviewer' => 'reviewer',
    ),
    'module' => 'vesafe_workflow',
  );

  // Exported permission: 'edit any content in needs_review'.
  $permissions['edit any content in needs_review'] = array(
    'name' => 'edit any content in needs_review',
    'roles' => array(
      'administrator' => 'administrator',
      'project manager' => 'project manager',
    ),
    'module' => 'vesafe_workflow',
  );

  // Exported permission: 'edit any content in published'.
  $permissions['edit any content in published'] = array(
    'name' => 'edit any content in published',
    'roles' => array(
      'administrator' => 'administrator',
      'project manager' => 'project manager',
    ),
    'module' => 'vesafe_workflow',
  );

  // Exported permission: 'edit any content in ready_to_publish'.
  $permissions['edit any content in ready_to_publish'] = array(
    'name' => 'edit any content in ready_to_publish',
    'roles' => array(),
    'module' => 'vesafe_workflow',
  );

  // Exported permission: 'edit any content in to_be_approved'.
  $permissions['edit any content in to_be_approved'] = array(
    'name' => 'edit any content in to_be_approved',
    'roles' => array(
      'approver' => 'approver',
    ),
    'module' => 'vesafe_workflow',
  );

  // Exported permission: 'edit any good_practice content'.
  $permissions['edit any good_practice content'] = array(
    'name' => 'edit any good_practice content',
    'roles' => array(
      'approver' => 'approver',
      'editor' => 'editor',
      'project manager' => 'project manager',
      'reviewer' => 'reviewer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any key_article content'.
  $permissions['edit any key_article content'] = array(
    'name' => 'edit any key_article content',
    'roles' => array(
      'approver' => 'approver',
      'editor' => 'editor',
      'project manager' => 'project manager',
      'reviewer' => 'reviewer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit node approvers'.
  $permissions['edit node approvers'] = array(
    'name' => 'edit node approvers',
    'roles' => array(
      'project manager' => 'project manager',
    ),
    'module' => 'vesafe_workflow',
  );

  // Exported permission: 'edit own good_practice content'.
  $permissions['edit own good_practice content'] = array(
    'name' => 'edit own good_practice content',
    'roles' => array(
      'approver' => 'approver',
      'editor' => 'editor',
      'project manager' => 'project manager',
      'reviewer' => 'reviewer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own key_article content'.
  $permissions['edit own key_article content'] = array(
    'name' => 'edit own key_article content',
    'roles' => array(
      'approver' => 'approver',
      'editor' => 'editor',
      'project manager' => 'project manager',
      'reviewer' => 'reviewer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'moderate content from draft to final_draft'.
  $permissions['moderate content from draft to final_draft'] = array(
    'name' => 'moderate content from draft to final_draft',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
      'project manager' => 'project manager',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate content from draft to needs_review'.
  $permissions['moderate content from draft to needs_review'] = array(
    'name' => 'moderate content from draft to needs_review',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate content from draft to published'.
  $permissions['moderate content from draft to published'] = array(
    'name' => 'moderate content from draft to published',
    'roles' => array(
      'administrator' => 'administrator',
      'project manager' => 'project manager',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate content from final_draft to draft'.
  $permissions['moderate content from final_draft to draft'] = array(
    'name' => 'moderate content from final_draft to draft',
    'roles' => array(
      'reviewer' => 'reviewer',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate content from final_draft to needs_review'.
  $permissions['moderate content from final_draft to needs_review'] = array(
    'name' => 'moderate content from final_draft to needs_review',
    'roles' => array(
      'administrator' => 'administrator',
      'reviewer' => 'reviewer',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate content from needs_review to draft'.
  $permissions['moderate content from needs_review to draft'] = array(
    'name' => 'moderate content from needs_review to draft',
    'roles' => array(
      'administrator' => 'administrator',
      'project manager' => 'project manager',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate content from needs_review to final_draft'.
  $permissions['moderate content from needs_review to final_draft'] = array(
    'name' => 'moderate content from needs_review to final_draft',
    'roles' => array(
      'project manager' => 'project manager',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate content from needs_review to published'.
  $permissions['moderate content from needs_review to published'] = array(
    'name' => 'moderate content from needs_review to published',
    'roles' => array(
      'administrator' => 'administrator',
      'project manager' => 'project manager',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate content from needs_review to to_be_approved'.
  $permissions['moderate content from needs_review to to_be_approved'] = array(
    'name' => 'moderate content from needs_review to to_be_approved',
    'roles' => array(
      'administrator' => 'administrator',
      'project manager' => 'project manager',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate content from ready_to_publish to final_draft'.
  $permissions['moderate content from ready_to_publish to final_draft'] = array(
    'name' => 'moderate content from ready_to_publish to final_draft',
    'roles' => array(
      'project manager' => 'project manager',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate content from ready_to_publish to published'.
  $permissions['moderate content from ready_to_publish to published'] = array(
    'name' => 'moderate content from ready_to_publish to published',
    'roles' => array(
      'project manager' => 'project manager',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate content from to_be_approved to final_draft'.
  $permissions['moderate content from to_be_approved to final_draft'] = array(
    'name' => 'moderate content from to_be_approved to final_draft',
    'roles' => array(
      'approver' => 'approver',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate content from to_be_approved to ready_to_publish'.
  $permissions['moderate content from to_be_approved to ready_to_publish'] = array(
    'name' => 'moderate content from to_be_approved to ready_to_publish',
    'roles' => array(
      'project manager' => 'project manager',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate good_practice state from draft to final_draft'.
  $permissions['moderate good_practice state from draft to final_draft'] = array(
    'name' => 'moderate good_practice state from draft to final_draft',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate good_practice state from draft to needs_review'.
  $permissions['moderate good_practice state from draft to needs_review'] = array(
    'name' => 'moderate good_practice state from draft to needs_review',
    'roles' => array(),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate good_practice state from draft to published'.
  $permissions['moderate good_practice state from draft to published'] = array(
    'name' => 'moderate good_practice state from draft to published',
    'roles' => array(),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate good_practice state from final_draft to draft'.
  $permissions['moderate good_practice state from final_draft to draft'] = array(
    'name' => 'moderate good_practice state from final_draft to draft',
    'roles' => array(),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate good_practice state from final_draft to needs_review'.
  $permissions['moderate good_practice state from final_draft to needs_review'] = array(
    'name' => 'moderate good_practice state from final_draft to needs_review',
    'roles' => array(),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate good_practice state from needs_review to draft'.
  $permissions['moderate good_practice state from needs_review to draft'] = array(
    'name' => 'moderate good_practice state from needs_review to draft',
    'roles' => array(),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate good_practice state from needs_review to final_draft'.
  $permissions['moderate good_practice state from needs_review to final_draft'] = array(
    'name' => 'moderate good_practice state from needs_review to final_draft',
    'roles' => array(),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate good_practice state from needs_review to published'.
  $permissions['moderate good_practice state from needs_review to published'] = array(
    'name' => 'moderate good_practice state from needs_review to published',
    'roles' => array(),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate good_practice state from needs_review to to_be_approved'.
  $permissions['moderate good_practice state from needs_review to to_be_approved'] = array(
    'name' => 'moderate good_practice state from needs_review to to_be_approved',
    'roles' => array(),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate good_practice state from ready_to_publish to final_draft'.
  $permissions['moderate good_practice state from ready_to_publish to final_draft'] = array(
    'name' => 'moderate good_practice state from ready_to_publish to final_draft',
    'roles' => array(),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate good_practice state from ready_to_publish to published'.
  $permissions['moderate good_practice state from ready_to_publish to published'] = array(
    'name' => 'moderate good_practice state from ready_to_publish to published',
    'roles' => array(),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate good_practice state from to_be_approved to final_draft'.
  $permissions['moderate good_practice state from to_be_approved to final_draft'] = array(
    'name' => 'moderate good_practice state from to_be_approved to final_draft',
    'roles' => array(),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate good_practice state from to_be_approved to ready_to_publish'.
  $permissions['moderate good_practice state from to_be_approved to ready_to_publish'] = array(
    'name' => 'moderate good_practice state from to_be_approved to ready_to_publish',
    'roles' => array(),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate key_article state from draft to final_draft'.
  $permissions['moderate key_article state from draft to final_draft'] = array(
    'name' => 'moderate key_article state from draft to final_draft',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate key_article state from draft to needs_review'.
  $permissions['moderate key_article state from draft to needs_review'] = array(
    'name' => 'moderate key_article state from draft to needs_review',
    'roles' => array(),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate key_article state from draft to published'.
  $permissions['moderate key_article state from draft to published'] = array(
    'name' => 'moderate key_article state from draft to published',
    'roles' => array(),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate key_article state from final_draft to draft'.
  $permissions['moderate key_article state from final_draft to draft'] = array(
    'name' => 'moderate key_article state from final_draft to draft',
    'roles' => array(),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate key_article state from final_draft to needs_review'.
  $permissions['moderate key_article state from final_draft to needs_review'] = array(
    'name' => 'moderate key_article state from final_draft to needs_review',
    'roles' => array(),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate key_article state from needs_review to draft'.
  $permissions['moderate key_article state from needs_review to draft'] = array(
    'name' => 'moderate key_article state from needs_review to draft',
    'roles' => array(),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate key_article state from needs_review to final_draft'.
  $permissions['moderate key_article state from needs_review to final_draft'] = array(
    'name' => 'moderate key_article state from needs_review to final_draft',
    'roles' => array(),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate key_article state from needs_review to published'.
  $permissions['moderate key_article state from needs_review to published'] = array(
    'name' => 'moderate key_article state from needs_review to published',
    'roles' => array(),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate key_article state from needs_review to to_be_approved'.
  $permissions['moderate key_article state from needs_review to to_be_approved'] = array(
    'name' => 'moderate key_article state from needs_review to to_be_approved',
    'roles' => array(),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate key_article state from ready_to_publish to final_draft'.
  $permissions['moderate key_article state from ready_to_publish to final_draft'] = array(
    'name' => 'moderate key_article state from ready_to_publish to final_draft',
    'roles' => array(),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate key_article state from ready_to_publish to published'.
  $permissions['moderate key_article state from ready_to_publish to published'] = array(
    'name' => 'moderate key_article state from ready_to_publish to published',
    'roles' => array(),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate key_article state from to_be_approved to final_draft'.
  $permissions['moderate key_article state from to_be_approved to final_draft'] = array(
    'name' => 'moderate key_article state from to_be_approved to final_draft',
    'roles' => array(),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'moderate key_article state from to_be_approved to ready_to_publish'.
  $permissions['moderate key_article state from to_be_approved to ready_to_publish'] = array(
    'name' => 'moderate key_article state from to_be_approved to ready_to_publish',
    'roles' => array(),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'use workbench_moderation needs review tab'.
  $permissions['use workbench_moderation needs review tab'] = array(
    'name' => 'use workbench_moderation needs review tab',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'view all unpublished content'.
  $permissions['view all unpublished content'] = array(
    'name' => 'view all unpublished content',
    'roles' => array(
      'administrator' => 'administrator',
      'approver' => 'approver',
      'editor' => 'editor',
      'project manager' => 'project manager',
      'reviewer' => 'reviewer',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'view moderation history'.
  $permissions['view moderation history'] = array(
    'name' => 'view moderation history',
    'roles' => array(
      'administrator' => 'administrator',
      'approver' => 'approver',
      'editor' => 'editor',
      'project manager' => 'project manager',
      'reviewer' => 'reviewer',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'view moderation messages'.
  $permissions['view moderation messages'] = array(
    'name' => 'view moderation messages',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'workbench_moderation',
  );

  // Exported permission: 'view own unpublished content'.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view revisions'.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view the administration theme'.
  $permissions['view the administration theme'] = array(
    'name' => 'view the administration theme',
    'roles' => array(
      'administrator' => 'administrator',
      'approver' => 'approver',
      'editor' => 'editor',
      'project manager' => 'project manager',
      'reviewer' => 'reviewer',
    ),
    'module' => 'system',
  );

  return $permissions;
}
