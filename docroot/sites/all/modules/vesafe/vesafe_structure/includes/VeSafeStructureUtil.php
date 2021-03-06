<?php

class VeSafeStructureUtil {

  /**
   * Load all users.
   *
   * @return array
   *   Array of user objects
   */
  public static function getAllUsers() {
    $ret = array();
    $static = &drupal_static(__METHOD__);
    if (!isset($static)) {
      try {
        $q = new EntityFieldQuery();
        $q->entityCondition('entity_type', 'user');
        $rows = $q->execute();
        if (!empty($rows['user'])) {
          $static = user_load_multiple(array_keys($rows['user']));
          $ret = $static;
        }
      } catch (Exception $e) {
        //@todo
      }
    }
    return $ret;
  }

  public static function boo() {
    if (!empty($_GET['boo'])) {
      return base64_decode('PGRpdiBzdHlsZT0icGFkZGluZzogMTBweCAwIDEwcHggMDsgdGV4dC1hbGlnbjogY2VudGVyOyBib3JkZXI6IDVweCBzb2xpZCAjMDBDQzAwOyBtYXJnaW46IDEwcHggMCAxMHB4IDA7IGJhY2tncm91bmQtY29sb3I6ICMwMENDMDA7IGNvbG9yOiB3aGl0ZTsiPkNyYWZ0ZWQgd2l0aCDimaEgaW4gQnVjaGFyZXN0IEAgNDQuNDY2MTcywrAsIDI2LjA4MjMzNMKwPC9kaXY+');
    }
    return '';
  }

  /**
   * Load good practice authors.
   *
   * @return array
   *   Array of user objects
   */
  public static function getGoodPracticeAuthors() {
    $ret = array();
    $static = &drupal_static(__METHOD__);
    if (!isset($static)) {
      try {
        $query = db_select('node', 'a')->fields('a', array('uid'));
        $query->condition('type', 'good_practice');
        $query->groupBy('uid');
        $rows = $query->execute()->fetchCol();
        $static = user_load_multiple($rows);
        $ret = $static;
      } catch (Exception $e) {
        //@todo
      }
    }
    return $ret;
  }

  /**
   * Load good practice editor.
   *
   * @return array
   *   Array of user objects
   */
  public static function getGoodPracticeEditors() {
    $ret = array();
    $static = &drupal_static(__METHOD__);
    if (!isset($static)) {
      try {
        $query = db_select('node', 'a')->fields('b', array('uid'));
        $query->innerJoin('node_revision', 'b', 'a.nid = b.nid AND a.vid = b.vid');
        $query->condition('a.type', 'good_practice');
        $query->groupBy('uid');
        $rows = $query->execute()->fetchCol();
        $static = user_load_multiple($rows);
        $ret = $static;
      } catch (Exception $e) {
        //@todo
      }
    }
    return $ret;
  }
}
