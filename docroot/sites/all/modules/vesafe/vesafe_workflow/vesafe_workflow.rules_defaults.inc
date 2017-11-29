<?php
/**
 * @file
 * vesafe_workflow.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function vesafe_workflow_default_rules_configuration() {
  $items = array();
  $items['rules_notification_reminder_pm'] = entity_import('rules_config', '{ "rules_notification_reminder_pm" : {
      "LABEL" : "Notification Reminder PM",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "vesafe_workflow" ],
      "ON" : { "notify_pm_review" : [] },
      "DO" : [
        { "mail_to_users_of_role" : {
            "roles" : { "value" : { "5" : "5" } },
            "subject" : "[Vesafe Website] Reminders: Content Update Status",
            "message" : "\\u003Cp\\u003EDear Project Manager,\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EAs you know the contents on the website have to be reviewed every 3 months. This is a reminder for you to check the content status of the section [content-type:value] \\u003Ca href=\\u0022[site:url]\\/admin\\/config\\/workbench\\/access\\/managers\\/review\\/[content-type-key:value]\\u0022\\u003Ein this screen\\u003C\\/a\\u003E.\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EYou can check the broken links in \\u003Ca href=\\u0022[site:url]\\/admin\\/content\\/linkchecker-broken-links?type=[content-type-key:value]\\u0022\\u003Ethis page\\u003C\\/a\\u003E.\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EThank you,\\u003C\\/p\\u003E\\r\\n"
          }
        }
      ]
    }
  }');
  $items['vesafe_workflow_draft'] = entity_import('rules_config', '{ "vesafe_workflow_draft" : {
      "LABEL" : "Item rejected back to Draft",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "workflow" ],
      "REQUIRES" : [ "workbench_moderation", "rules", "vesafe_workflow" ],
      "ON" : { "workbench_moderation_after_moderation_transition" : [] },
      "IF" : [
        { "contents_current_state" : { "node" : [ "node" ], "moderation_state" : "draft" } },
        { "NOT contents_previous_state" : { "node" : [ "node" ], "moderation_state" : "draft" } }
      ],
      "DO" : [
        { "vesafe_workflow_mail" : {
            "to" : [ "node:author:mail" ],
            "subject" : "[Vesafe website] New content needs your review",
            "message" : "\\u003Cp\\u003EDear Editor,\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EThere is a new content to be reviewed by you: \\u003Ca href=\\u0022[node:edit-url]\\u0022\\u003E[node:title]\\u003C\\/a\\u003E. You can access also \\u003Ca href=\\u0022[site:url]\\/admin\\/content?state=draft\\u0022\\u003Ethe \\u003Cstrong\\u003E{{count}}\\u003C\\/strong\\u003E items\\u003C\\/a\\u003E that need to review.\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EThank you,\\u003C\\/p\\u003E",
            "count_type" : { "value" : { "draft" : "draft" } }
          }
        }
      ]
    }
  }');
  $items['vesafe_workflow_final_draft'] = entity_import('rules_config', '{ "vesafe_workflow_final_draft" : {
      "LABEL" : "Editor finished, notify reviewer about final draft",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "workflow" ],
      "REQUIRES" : [ "workbench_moderation", "rules", "vesafe_workflow" ],
      "ON" : { "workbench_moderation_after_moderation_transition" : [] },
      "IF" : [
        { "contents_current_state" : { "node" : [ "node" ], "moderation_state" : "final_draft" } },
        { "NOT contents_previous_state" : { "node" : [ "node" ], "moderation_state" : "final_draft" } }
      ],
      "DO" : [
        { "vesafe_workflow_mail_to_users_of_role" : {
            "roles" : { "value" : { "6" : "6", "7" : "7" } },
            "subject" : "[Vesafe website] New content needs your review ",
            "message" : "\\u003Cp\\u003EDear Reviewer,\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EThere is a new content to be reviewed by you: \\u003Ca href=\\u0022[node:edit-url]\\u0022\\u003E[node:title]\\u003C\\/a\\u003E. You can access also to the \\u003Ca href=\\u0022[site:url]\\/admin\\/content?state=final_draft\\u0022\\u003Elist of {{count}} items\\u003C\\/a\\u003E that need to review.\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EThank you,\\u003C\\/p\\u003E",
            "count_type" : { "value" : { "final_draft" : "final_draft" } }
          }
        }
      ]
    }
  }');
  $items['vesafe_workflow_ready_to_publish'] = entity_import('rules_config', '{ "vesafe_workflow_ready_to_publish" : {
      "LABEL" : "Content was approved and now is Ready to publish",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "workflow" ],
      "REQUIRES" : [ "workbench_moderation", "rules", "vesafe_workflow" ],
      "ON" : { "workbench_moderation_after_moderation_transition" : [] },
      "IF" : [
        { "contents_current_state" : { "node" : [ "node" ], "moderation_state" : "ready_to_publish" } },
        { "NOT contents_previous_state" : { "node" : [ "node" ], "moderation_state" : "ready_to_publish" } }
      ],
      "DO" : [
        { "vesafe_workflow_mail_to_users_of_role" : {
            "roles" : { "value" : { "5" : "5" } },
            "subject" : "[Vesafe website] New content needs your review ",
            "message" : "\\u003Cp\\u003EDear Project Manager,\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EThere is a new content ready to be published by you: \\u003Ca href=\\u0022[node:edit-url]\\u0022\\u003E[node:title]\\u003C\\/a\\u003E. You can also access the \\u003Ca href=\\u0022[site:url]\\/admin\\/content?state=ready_to_publish\\u0022\\u003Elist of {{count}} items\\u003C\\/a\\u003E that is ready to be published.\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EThank you,\\u003C\\/p\\u003E",
            "count_type" : { "value" : { "to_be_approved" : "to_be_approved" } }
          }
        }
      ]
    }
  }');
  $items['vesafe_workflow_to_be_approved'] = entity_import('rules_config', '{ "vesafe_workflow_to_be_approved" : {
      "LABEL" : "Notify approver content is in state To be approved",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "workflow" ],
      "REQUIRES" : [ "rules", "vesafe_workflow" ],
      "ON" : { "node_to_be_approved" : [] },
      "DO" : [
        { "vesafe_workflow_mail" : {
            "to" : [ "user:mail" ],
            "subject" : "[Vesafe website] New content needs your approval",
            "message" : "\\u003Cp\\u003EDear Approver,\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EThere is a new content to be reviewed by you: \\u003Ca href=\\u0022[node:edit-url]\\u0022\\u003E[node:title]\\u003C\\/a\\u003E. You can access also to the \\u003Ca href=\\u0022[site:url]\\/admin\\/content\\/approve\\u0022\\u003Elist of {{count}} items\\u003C\\/a\\u003E that need to approve.\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EThank you,\\u003C\\/p\\u003E",
            "count_type" : { "value" : { "to_be_approved" : "to_be_approved" } }
          }
        }
      ]
    }
  }');
  $items['vesafe_workflow_vesafe_workflow_review'] = entity_import('rules_config', '{ "vesafe_workflow_vesafe_workflow_review" : {
      "LABEL" : "Reviewer accepted, state changed to be reviewed by EU-OSHA",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "workflow" ],
      "REQUIRES" : [ "workbench_moderation", "rules", "vesafe_workflow" ],
      "ON" : { "workbench_moderation_after_moderation_transition" : [] },
      "IF" : [
        { "contents_current_state" : { "node" : [ "node" ], "moderation_state" : "needs_review" } },
        { "NOT contents_previous_state" : { "node" : [ "node" ], "moderation_state" : "needs_review" } }
      ],
      "DO" : [
        { "vesafe_workflow_mail_to_users_of_role" : {
            "roles" : { "value" : { "5" : "5" } },
            "subject" : "[Vesafe website] New content needs your review ",
            "message" : "\\u003Cp\\u003EDear Project Manager,\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EThere is a new content to be reviewed by you: \\u003Ca href=\\u0022[node:edit-url]\\u0022\\u003E[node:title]\\u003C\\/a\\u003E. You can access also to the \\u003Ca href=\\u0022[site:url]\\/admin\\/content?state=needs_review\\u0022\\u003Elist of {{count}} items\\u003C\\/a\\u003E that need to review.\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EThank you,\\u003C\\/p\\u003E",
            "count_type" : { "value" : { "needs_review" : "needs_review" } }
          }
        }
      ]
    }
  }');
  return $items;
}
