<?php

// MIGRATIONS.
class NCWTaxonomyThesaurusMigration extends AbstractNCWTaxonomyTermMigration {

  protected $last_imported;

  /**
   * General initialization of a Migration object.
   */
  public function __construct($arguments) {
    parent::__construct($arguments, 'ThesaurusNCWTaxonomyTermSource', 'thesaurus');
    $this->description = 'Import taxonomy "Thesaurus" from NCW';
  }

}

// SOURCES.
class ThesaurusNCWTaxonomyTermSource extends AbstractNCWTaxonomyTermSource {
  public function contentFields() {
    return array(
      'field_thesaurus_code' => 'field_thesaurus_code',
    );
  }

}
