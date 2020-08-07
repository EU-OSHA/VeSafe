<?php


class NCWSingleThesaurusMigration extends AbstractNCWNodeMigration {

  protected $nid = NULL;

  public function __construct($arguments, $nid = NULL) {
    $content_type = 'thesaurus';
    $source = 'NCWSingleThesaurusSource';
    parent::__construct($arguments, $source, $content_type);
    $this->ignoreMetatagMigration();

    $this->addUnmigratedDestinations(array(
      'metatag_rating',
      'metatag_referrer',
      'metatag_set_cookie',
      'metatag_prev',
      'metatag_next',
      'metatag_geo.position',
      'metatag_geo.placename',
      'metatag_geo.region',
      'metatag_icbm',
      'metatag_refresh ',
      'metatag_pragma',
      'metatag_cache-control',
      'metatag_expires',
      'metatag_refresh',
    ));
  }
}


class NCWSingleThesaurusSource extends AbstractNCWNodeSource {

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
      'field_definition_format',
      'field_context',
      'field_context_format',
      'field_synonyms',
      'field_term_reference',
      'field_term_reference_format',
      'field_notes',
      'field_notes_format',
      'field_father'
    );
    return array_combine($ret, $ret);
  }
}
