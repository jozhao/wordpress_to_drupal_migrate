<?php

/**
 * @file
 * Migrate taxonomy from a WordPress blog into govCMS.
 */

/**
 * Class GovCMSMigrateWordPressTaxonomy.
 */
class GovCMSMigrateWordPressTaxonomy extends MigrateWordPressTaxonomy {
  /**
   * GovCMSMigrateWordPressTaxonomy constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    parent::__construct($arguments);
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
