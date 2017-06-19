<?php
/**
 * @file
 * hwc_workflow.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function vesafe_workflow_default_rules_configuration() {
  $items = array();
  $items['rules_hwc_workflow_notification_after_approval'] = entity_import('rules_config', '{ "rules_hwc_workflow_notification_after_approval" : {
      "LABEL" : "Notification after approval",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "hwc_workflow" ],
      "ON" : { "node_cpm_approve" : [] },
      "DO" : [
        { "LOOP" : {
            "USING" : { "list" : [ "users" ] },
            "ITEM" : { "list_item" : "Current list item" },
            "DO" : [
              { "mail" : {
                  "to" : [ "list-item:mail" ],
                  "subject" : "[HWC Website] CMW: ([node:nid]) [node:title-field]",
                  "message" : "\\u003Cp\\u003EDear [list_item:name],\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003E[user:name] should approve this content: \\u003Ca href=\\u0022[node:url]\\u0022\\u003E[node:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E",
                  "language" : [ "" ]
                }
              }
            ]
          }
        },
        { "mail" : {
            "to" : [ "user:mail" ],
            "subject" : "[HWC Website] CMW: ([node:nid]) [node:title-field]",
            "message" : "\\u003Cp\\u003EDear [user:name],\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EA content item should be approved by you: \\u003Ca href=\\u0022[node:url]\\u0022\\u003E[node:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_hwc_workflow_notification_partner_content_created'] = entity_import('rules_config', '{ "rules_hwc_workflow_notification_partner_content_created" : {
      "LABEL" : "Notification partner content created (CMW_ED_US_02)",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "hwc_workflow" ],
      "ON" : { "node_insert" : [] },
      "IF" : [
        { "entity_is_of_bundle" : {
            "entity" : [ "node" ],
            "type" : "node",
            "bundle" : { "value" : { "events" : "events", "news" : "news" } }
          }
        },
        { "entity_has_field" : { "entity" : [ "node" ], "field" : "field_wf_notification" } },
        { "data_is_empty" : { "data" : [ "node:field-wf-notification" ] } }
      ],
      "DO" : [
        { "hwc_mail_to_users_of_partner" : {
            "node" : [ "node" ],
            "subject" : "HWC Workflow: New content added for your company",
            "message" : "\\u003Cp\\u003EDear partner,\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EYour [node:type] is currently in the \\u201csave-as-draft\\u201d status which means that you can still edit it before you decide to \\u201csubmit\\u201d it for validation\\u201d\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003E\\u003Ca href=\\u0022[node:url]\\u0022\\u003E[node:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EThank you for your participation in the Healthy Workplaces for All Ages campaign.\\u003C\\/p\\u003E"
          }
        }
      ]
    }
  }');
  $items['rules_hwc_workflow_notification_partner_content_published'] = entity_import('rules_config', '{ "rules_hwc_workflow_notification_partner_content_published" : {
      "LABEL" : "Notification when published (CMW_ED_US_05, CMW_RM_US_06, , CMW_SU_US_05)",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "hwc_workflow", "workbench_moderation" ],
      "ON" : { "workbench_moderation_after_moderation_transition" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "new-state" ], "value" : "published" } },
        { "entity_is_of_bundle" : {
            "entity" : [ "node" ],
            "type" : "node",
            "bundle" : { "value" : { "events" : "events", "news" : "news" } }
          }
        },
        { "node_has_partner_section" : { "entity" : [ "node" ] } }
      ],
      "DO" : [
        { "mail_to_users_of_role" : {
            "roles" : { "value" : { "14" : "14" } },
            "subject" : "New content has been published",
            "message" : "This content has been published: \\u003Ca href=\\u0022[node:url]\\u0022\\u003E[node:title]\\u003C\\/a\\u003E"
          }
        },
        { "mail" : {
            "to" : [ "site:hwc-mostra-mailbox" ],
            "subject" : "[HWC Website] CMW: ([node:nid]) [node:title-field]",
            "message" : "No action is required. This message is just to inform you that this content has been published: \\u003Ca href=\\u0022[node:url]\\u0022\\u003E[node:title]\\u003C\\/a\\u003E",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_hwc_workflow_notification_to_be_approved'] = entity_import('rules_config', '{ "rules_hwc_workflow_notification_to_be_approved" : {
      "LABEL" : "Notification when to be approved",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "hwc_workflow" ],
      "ON" : { "node_to_be_approved" : [] },
      "DO" : [
        { "LOOP" : {
            "USING" : { "list" : [ "users" ] },
            "ITEM" : { "list_item" : "Current list item" },
            "DO" : [
              { "mail" : {
                  "to" : [ "list-item:mail" ],
                  "subject" : "[HWC Website] CMW: ([node:nid]) [node:title-field]",
                  "message" : "\\u003Cp\\u003EDear [list_item:name],\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003E[user:name] should approve this content \\u003Ca href=\\u0022[node:url]\\u0022\\u003E[node:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E",
                  "language" : [ "" ]
                }
              }
            ]
          }
        },
        { "mail" : {
            "to" : [ "user:mail" ],
            "subject" : "[HWC Website] CMW: ([node:nid]) [node:title-field]",
            "message" : "\\u003Cp\\u003EDear [user:name],\\u003C\\/p\\u003E\\r\\n\\u003Cp\\u003EA content item should be approved by you: \\u003Ca href=\\u0022[node:url]\\u0022\\u003E[node:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_hwc_workflow_notification_to_be_reviewed'] = entity_import('rules_config', '{ "rules_hwc_workflow_notification_to_be_reviewed" : {
      "LABEL" : "Notification when to be reviewed (RM_US_02, SU_US_04)",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "workbench_moderation" ],
      "ON" : { "workbench_moderation_after_moderation_transition" : [] },
      "IF" : [ { "data_is" : { "data" : [ "new-state" ], "value" : "needs_review" } } ],
      "DO" : [
        { "mail_to_users_of_role" : {
            "roles" : { "value" : { "14" : "14" } },
            "subject" : "[HWC Website] CMW: ([node:nid]) [node:title-field]",
            "message" : "\\u003Cp\\u003E[node:author:name] ([node:author:mail]) has submitted a [node:type] item for validation. Please see the submitted update here: \\u003Ca href=\\u0022[node:url]\\u0022\\u003E[node:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E"
          }
        },
        { "mail" : {
            "to" : [ "site:hwc-mostra-mailbox" ],
            "subject" : "[HWC Website] CMW: ([node:nid]) [node:title-field]",
            "message" : "\\u003Cp\\u003E[node:author:name] ([node:author:mail]) has submitted a [node:type] item for validation. Please see the submitted update here: \\u003Ca href=\\u0022[node:url]\\u0022\\u003E[node:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  return $items;
}