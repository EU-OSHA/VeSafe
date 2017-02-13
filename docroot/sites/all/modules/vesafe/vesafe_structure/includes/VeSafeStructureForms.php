<?php

class VeSafeStructureForms {


  /**
   * {@inheritdoc}
   */
  public static function good_practice_node_form_alter(&$form, &$form_state) {
    self::attachCSS($form, drupal_get_path('module', 'vesafe_structure') . '/styles/good-practice.css');
    $form['body']['#access'] = false;
    global $user;
    if (empty($user) || $user->uid != 1) {
      $form['field_like_count']['#access'] = FALSE;
    }
    $form['field_like_count'][LANGUAGE_NONE][0]['value']['#description'] = 'Visible to user/1 only';
  }


  /**
   * {@inheritdoc}
   */
  public static function key_article_node_form_alter(&$form, &$form_state) {
    self::attachCSS($form, drupal_get_path('module', 'vesafe_structure') . '/styles/key-article.css');
  }


  /**
   * Alter exposed filter for /admin/content/good-practices
   *
   * {@inheritdoc}
   */
  public static function good_practice_admin_content_view_form_alter(&$form, &$form_state) {
    self::attachCSS($form, drupal_get_path('module', 'vesafe_structure') . '/styles/good-practice-overview.css');
    unset($form['field_vehicles_tid']['#description']);
    unset($form['field_risks_tid']['#description']);
    unset($form['field_publication_date_value']['min']['#title']);
    $form['field_publication_date_value']['max']['#title'] = t('and');
    $form['author']['#type'] = 'select';
    $form['author']['#size'] = 1;
    $form['author']['#options'] = array('' => t(' - Any - '));
    $rows = VeSafeStructureUtil::getGoodPracticeAuthors();
    foreach($rows as $uid => $row) {
      $form['author']['#options'][$row->name] = $row->name;
    }

    $form['editor']['#type'] = 'select';
    $form['editor']['#size'] = 1;
    $form['editor']['#options'] = array('' => t(' - Any - '));
    $rows = VeSafeStructureUtil::getGoodPracticeEditors();
    foreach($rows as $uid => $row) {
      $form['editor']['#options'][$row->name] = $row->name;
    }
    $form['#suffix'] = VeSafeStructureUtil::boo();
  }


  /**
   * Safely attach CSS to a form.
   *
   * @param array $form
   *   Reference to form array
   * @param string $file
   *   Path to CSS file
   */
  private static function attachCSS(&$form, $file) {
    if (empty($form['#attached'])) {
      $form['#attached'] = array();
    }
    if (empty($form['#attached']['css'])) {
      $form['#attached']['css'] = array();
    }
    $form['#attached']['css'][] = $file;
  }
}
