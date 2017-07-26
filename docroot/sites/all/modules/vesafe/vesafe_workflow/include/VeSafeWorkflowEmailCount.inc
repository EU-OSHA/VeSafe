<?php


class VeSafeWorkflowEmailCount {

  public static function count_items($type, $approver = null) {
    $ret = 0;
    switch ($type) {
      case OSHA_WORKFLOW_STATE_FINAL_DRAFT:
      case OSHA_WORKFLOW_STATE_DRAFT:
      case OSHA_WORKFLOW_STATE_TO_BE_REVIEWED:
      case OSHA_WORKFLOW_STATE_TO_BE_APPROVED:
        $ret = self::countNodesInWorkflowState($type);
        break;
      // We compute the nodes for the approver - $approver
      case OSHA_WORKFLOW_STATE_TO_BE_APPROVED:
        $view = views_get_view('osh_workflow_admin');
        $view->set_display('page_1');
        $view->set_arguments(array($approver->uid));
        $view->pre_execute();
        $view->execute();
        $ret = $view->total_rows;
    }
    return $ret;
  }


  private static function countNodesForApprover($author) {
    $query = db_select('workbench_moderation_node_history', 'a');
    $query->fields('a', array('nid'));
    $query->condition('current', 1);
    $query->condition('state', OSHA_WORKFLOW_STATE_TO_BE_APPROVED);
    $query->countQuery();
    $nids = $query->execute()->fetchCol();
  }


  private static function countNodesInWorkflowState($state) {
    $query = db_select('workbench_moderation_node_history', 'a');
    $query->addExpression('COUNT(*)');
    $query->condition('current', 1);
    $query->condition('state', $state);
    $query->countQuery();
    return $query->execute()->fetchField();
  }

}