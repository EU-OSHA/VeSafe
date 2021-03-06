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
    
    $form['#validate'][] = "good_practice_node_form_validate";
    $form['field_creation_date'] = $form['field_publication_date'];
    $form['field_creation_date']['und'][0]['#title'] = 'Creation date';
    if ($form['author']['date']['#default_value']) {
      $form['field_creation_date']['und'][0]['#default_value']['value'] = $form['author']['date']['#default_value'];  
    }    
    $form['field_creation_date']['#disabled'] = TRUE;
  }

  /**
   * {@inheritdoc}
   */
  public static function key_article_node_form_alter(&$form, &$form_state) {
    self::attachCSS($form, drupal_get_path('module', 'vesafe_structure') . '/styles/key-article.css');

    $form['#validate'][] = "key_article_node_form_validate";
    $form['field_creation_date'] = $form['field_publication_date'];
    $form['field_creation_date']['und'][0]['#title'] = 'Creation date';
    if ($form['author']['date']['#default_value']) {
      $form['field_creation_date']['und'][0]['#default_value']['value'] = $form['author']['date']['#default_value'];  
    }    
    $form['field_creation_date']['#disabled'] = TRUE;
  }

  /**
   * {@inheritdoc}
   */
  public static function key_article_theme_node_form_alter(&$form, &$form_state) {
    self::attachCSS($form, drupal_get_path('module', 'vesafe_structure') . '/styles/key-article-theme.css');
  }

  public static function did_you_know_slide_node_form_alter(&$form, &$form_state) {
    $form['title']['#required'] = false;
    hide($form['title']);
    array_unshift($form['actions']['submit']['#submit'], [self::class, 'did_you_know_slide_node_form_submit']);
    array_unshift($form['#submit'], [self::class, 'did_you_know_slide_node_form_submit']);
  }

  public static function did_you_know_slide_node_form_submit($form, &$form_state) {
    // Copy the first 150 characters of body into node title
    $body = $form_state['values']['body'][LANGUAGE_NONE][0]['value'];
    $title = substr($body, 0, 150);
    $title = substr($title, 0, strrpos($title, ' ') - 1);
    if (strlen($body) > 150) {
      $title .= '...';
    }
    $form_state['values']['title'] = $title;
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
   * Alter form for Contact Us Webform
   *
   * {@inheritdoc}
   */
  public static function contact_us_form_alter(&$form, &$form_state) {
    $form['submitted']['disclaimer']['#weight'] = '7';
    $form['disclaimer'] = $form['submitted']['disclaimer'];
    $form['captcha']['#weight'] = '6';
    $form['submitted']['disclaimer']['#access'] = FALSE;
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
