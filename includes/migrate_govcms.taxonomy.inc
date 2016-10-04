<?php

/**
 * @file
 * Migrate taxonomy from a WordPress blog into govCMS.
 */

/**
 * Class GovCMSMigrateWordPressTaxonomy.
 */
class GovCMSMigrateWordPressTaxonomy extends WordPressMigration {
  /**
   * GovCMSMigrateWordPressTaxonomy constructor.
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
      return TRUE;
    }
    else {
      // Clean up not used values in map table; Or migration will be confused.
      $this->skippedItems[] = $this->xpathValue($row->xml->xpath('wp:term_id'));

      return FALSE;
    }
  }

  /**
   * Reruan xpath value.
   * @param $result
   * @return string
   */
  public function xpathValue($result) {
    return (string) reset($result);
  }
}

/**
 * Class GovCMSMigrateWordPressTaxonomyEeoBusinessResponse.
 */
class GovCMSMigrateWordPressTaxonomyEeoBusinessResponse extends GovCMSMigrateWordPressTaxonomy {
  /**
   * GovCMSMigrateWordPressTaxonomyEeoBusinessResponse constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['custom_vocabulary'] = 'eeo_business_response';
    parent::__construct($arguments);
  }
}

/**
 * Class GovCMSMigrateWordPressTaxonomyCostCategories.
 */
class GovCMSMigrateWordPressTaxonomyCostCategories extends GovCMSMigrateWordPressTaxonomy {
  /**
   * GovCMSMigrateWordPressTaxonomyCostCategories constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['custom_vocabulary'] = 'cost_categories';
    parent::__construct($arguments);
  }
}

/**
 * Class GovCMSMigrateWordPressTaxonomyEnergySavings.
 */
class GovCMSMigrateWordPressTaxonomyEnergySavings extends GovCMSMigrateWordPressTaxonomy {
  /**
   * GovCMSMigrateWordPressTaxonomyEnergySavings constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['custom_vocabulary'] = 'energy_savings';
    $arguments['source'] = 'eex_energy_savings';
    parent::__construct($arguments);
  }
}

/**
 * Class GovCMSMigrateWordPressTaxonomyEquipmentType.
 */
class GovCMSMigrateWordPressTaxonomyEquipmentType extends GovCMSMigrateWordPressTaxonomy {
  /**
   * GovCMSMigrateWordPressTaxonomyEquipmentType constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['custom_vocabulary'] = 'eeo_equipment_type';
    parent::__construct($arguments);
  }
}

/**
 * Class GovCMSMigrateWordPressTaxonomyIndustrySectors.
 */
class GovCMSMigrateWordPressTaxonomyIndustrySectors extends GovCMSMigrateWordPressTaxonomy {
  /**
   * GovCMSMigrateWordPressTaxonomyIndustrySectors constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['custom_vocabulary'] = 'industry_sectors';
    parent::__construct($arguments);
  }
}

/**
 * Class GovCMSMigrateWordPressTaxonomyLocations.
 */
class GovCMSMigrateWordPressTaxonomyLocations extends GovCMSMigrateWordPressTaxonomy {
  /**
   * GovCMSMigrateWordPressTaxonomyLocations constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['custom_vocabulary'] = 'locations';
    parent::__construct($arguments);
  }
}

/**
 * Class GovCMSMigrateWordPressTaxonomyOpportunityType.
 */
class GovCMSMigrateWordPressTaxonomyOpportunityType extends GovCMSMigrateWordPressTaxonomy {
  /**
   * GovCMSMigrateWordPressTaxonomyOpportunityType constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['custom_vocabulary'] = 'eeo_opportunity_type';
    parent::__construct($arguments);
  }
}

/**
 * Class GovCMSMigrateWordPressTaxonomyPayback.
 */
class GovCMSMigrateWordPressTaxonomyPayback extends GovCMSMigrateWordPressTaxonomy {
  /**
   * GovCMSMigrateWordPressTaxonomyPayback constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['custom_vocabulary'] = 'payback';
    parent::__construct($arguments);
  }
}

/**
 * Class GovCMSMigrateWordPressTaxonomySector.
 */
class GovCMSMigrateWordPressTaxonomySector extends GovCMSMigrateWordPressTaxonomy {
  /**
   * GovCMSMigrateWordPressTaxonomySector constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['custom_vocabulary'] = 'eeo_sector';
    parent::__construct($arguments);
  }
}

/**
 * Class GovCMSMigrateWordPressTaxonomyTechnologies.
 */
class GovCMSMigrateWordPressTaxonomyTechnologies extends GovCMSMigrateWordPressTaxonomy {
  /**
   * GovCMSMigrateWordPressTaxonomyTechnologies constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['custom_vocabulary'] = 'technologies';
    parent::__construct($arguments);
  }
}
