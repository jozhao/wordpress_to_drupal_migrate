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

    // Unmapped destination fields
    $this->addFieldMapping('parent_name');
    $this->addFieldMapping('format');
    $this->addFieldMapping('weight');
    $this->addFieldMapping('path');
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
    parent::__construct($arguments);
  }
}
