<?php

/**
 * Controller class for the approval workflow.
 *
 * {@inheritdoc}
 */
class VesafeWorkflowApprovalItemController extends EntityAPIController {

  /**
   * {@inheritdoc}
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    parent::save($entity, $transaction);
  }

  /**
   * {@inheritdoc}
   */
  public function delete($ids, $transaction = NULL) {
    parent::delete($ids, $transaction);
  }
}

/**
 * Controller class for the ProjectManager entity.
 *
 * {@inheritdoc}
 */
class VesafeWorkflowProjectManagerEntityController extends EntityAPIController {

  /**
   * {@inheritdoc}
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    parent::save($entity, $transaction);
  }

  /**
   * {@inheritdoc}
   */
  public function delete($ids, $transaction = NULL) {
    parent::delete($ids, $transaction);
  }
}
