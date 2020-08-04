<?php


class NCWSingleThesaurusMigration extends AbstractNCWNodeMigration {

  protected $nid = NULL;

  public function __construct($arguments, $nid = NULL) {
    $content_type = 'thesaurus';
    $source = 'NCWSingleThesaurusSource';
    parent::__construct($arguments, $source, $content_type);
file_put_contents("/var/tmp/output.txt", $arguments);
file_put_contents("/var/tmp/output.txt", PHP_EOL, FILE_APPEND);
    /*if (defined('SINGLE_NODE_MIGRATION_NID')) {
      $url = ncw_migration_datasource_url() . '/export/node/' . SINGLE_NODE_MIGRATION_NID;
      $node = ncw_migration_file_get_contents($url);
      $row = NULL;
      if ($row_ob = json_decode($node, TRUE)) {
        $row = new stdClass();
        foreach ($row_ob as $k => $v) {
          $row->$k = $v;
        }
      }
      $this->source = new NCWSingleArticleSource(array(
        'endpoint_url' => NULL,
        'track_changes' => TRUE,
        'node' => $row,
      ));
    }*/
    $this->description = 'Import arbitrary nodes from NCW (not all content types supported)';
    /*$this->ignoreMetatagMigration();

    $this->addFieldMapping('field_tags:source_type')->defaultValue('tid');
    $this->addFieldMapping('field_tags:create_term')->defaultValue(FALSE);
    $this->addFieldMapping('field_tags', 'field_tags');

    $this->removeFieldMapping('field_summary:format');
    $this->addUnmigratedDestinations(array(
      'field_article_type:source_type', 'field_article_type:ignore_case',
      'field_expiration_date:rrule',
      'field_nace_codes', 'field_nace_codes:source_type', 'field_nace_codes:create_term', 'field_nace_codes:ignore_case',

      'field_image:file_class', 'field_image:preserve_files', 'field_image:destination_dir',
      'field_image:destination_file', 'field_image:source_dir', 'field_image:urlencode', 'field_image:alt', 'field_image:title',

      'field_publication_date:rrule',
      'field_tags:ignore_case',

    ));*/
file_put_contents("/var/tmp/output.txt", "Construct OUT", FILE_APPEND);
  }

  /**
   * {@inheritdoc}
   */
  protected function getManuallyMigratedFields() {
    return array();
  }

  /**
   * {@inheritdoc}
   */
  function prepareRow($row) {
    parent::prepareRow($row);
    //$row->field_tags = osha_migration_normalize_migrated_term_reference($row->field_tags, 'tax_tags');
  }
}


class NCWSingleThesaurusSource extends AbstractNCWNodeSource {

  protected $nid = NULL;
  protected $type = NULL;
  protected $node = NULL;

  public function __construct($options) {
    parent::__construct($options);
    if (!empty($options['node'])) {
      $node = $options['node'];
      $this->node = $node;
      $this->type = $node->type;
      $this->nid = $node->nid;
      $this->readData();
    }
  }

  /**
   * Return a string representing the source, for display in the UI.
   */
  public function __toString() { return 'Extract single article from NCW endpoint'; }

  /**
   * Remote call to load the data from the endpoint URL
   */
  public function readData() {
    $this->rows = array($this->nid => $this->node);
  }

  /**
   * @return array
   */
  public function contentFields() {
    $ret = array(
      'title_field',
      'title_field_language',
      'field_full_url',
      'field_term_id',      
      'field_definition',
      'field_definition_language',
      'field_context',
      'field_context_language',
      'field_synonyms',
      'field_synonyms_language',
      'field_term_reference',
      'field_term_reference_language',
      'field_notes',
      'field_notes_language',
      'field_father'
    );
    return array_combine($ret, $ret);
  }
}
