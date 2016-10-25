<?php

/**
 * @file
 * Migrate taxonomy from a WordPress blog.
 */

/**
 * Class MigrateWordPressTaxonomy.
 */
class MigrateWordPressTaxonomy extends WordPressMigration {
  /**
   * MigrateWordPressTaxonomy constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'wp:term_id' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'WordPress term machine name',
        ),
        'wp:term_slug' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'WordPress term machine name',
          'default' => '',
        ),
      ),
      MigrateDestinationTerm::getKeySchema()
    );

    $fields = array(
      'wp:term_taxonomy' => 'Term taxonomy',
      'wp:term_slug' => 'Unique "machine name" of the term',
      'wp:term_parent' => 'Term parent',
      'wp:term_name' => 'User-friendly term name',
      'wp:term_description' => 'Description of term',
    );

    // Construct the source and destination objects.
    $source_options = array(
      'reader_class' => 'MigrateXMLReader',
      'cache_counts' => TRUE,
    );

    $this->source = new MigrateSourceXML($this->wxrFile, '/rss/channel/term',
      'wp:term_id', $fields, $source_options, $this->arguments['namespaces']);

    // Set taxonomy destination.
    $this->destination = new MigrateDestinationTerm($this->arguments['custom_vocabulary']);

    // The basic mappings
    $this->addFieldMapping('name', 'wp:term_name')
      ->xpath('wp:term_name')
      ->callbacks('html_entity_decode');
    $this->addFieldMapping('description', 'wp:term_description')
      ->xpath('wp:term_description')
      ->callbacks('html_entity_decode');
    $this->addFieldMapping('parent', 'wp:term_parent')
      ->sourceMigration($this->machineName)
      ->xpath('wp:term_parent');

    // Unmapped destination fields
    $this->addFieldMapping('parent_name');
    $this->addFieldMapping('format');
    $this->addFieldMapping('weight');
    $this->addFieldMapping('path');
  }

  /**
   * Prepare source mapping key.
   * @param array $source_key
   * @param object $row
   * @return array
   */
  public function prepareKey($source_key, $row) {
    $key = array();

    foreach ($source_key as $field_name => $field_schema) {
      if ($field_name == 'wp:term_slug') {
        $key[$field_name] = $this->xpathValue($row->xml->xpath('wp:term_slug'));
      }
      else {
        $key[$field_name] = $row->$field_name;
      }
    }

    return $key;
  }

  /**
   * Prepare source row.
   * @param $row
   * @return bool
   */
  public function prepareRow($row) {
    // Always include this fragment at the beginning of every prepareRow()
    // implementation, so parent classes can ignore rows.
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    // Source is required in arguments.
    if (empty($this->arguments['source'])) {
      return FALSE;
    }

    // Check if source is equal to term taxonomy.
    if ($this->arguments['source'] == $this->xpathValue($row->xml->xpath('wp:term_taxonomy'))) {
      $row->{'wp:term_slug'} = $this->xpathValue($row->xml->xpath('wp:term_slug'));

      return TRUE;
    }
    else {
      // Clean up not used values in map table; Or migration will be confused.
      $this->skippedItems[] = $this->xpathValue($row->xml->xpath('wp:term_id'));

      return FALSE;
    }
  }

  /**
   * Return is complete status.
   * @return bool
   */
  public function isComplete() {
    $total = $this->sourceCount(TRUE);
    // If the source is uncountable, we have no way of knowing if it's
    // complete, so stipulate that it is.
    if ($total < 0) {
      return TRUE;
    }
    $processed = $this->processedCount();

    return $processed > 0;
  }

  /**
   * Return xpath value as a string.
   * @param $result
   * @return string
   */
  public function xpathValue($result) {
    return (string) reset($result);
  }
}
