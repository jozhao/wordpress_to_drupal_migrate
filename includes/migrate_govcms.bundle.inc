<?php

/**
 * @file
 * Migrate bundle from a WordPress blog into govCMS.
 */

/**
 * Class GovCMSMigrateWordPressBundle.
 */
class GovCMSMigrateWordPressBundle extends GovCMSMigrateWordPressItemMigration {
  /**
   * GovCMSMigrateWordPressBundle constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    parent::__construct($arguments);
  }
}

/**
 * Class GovCMSMigrateWordPressOpportunities.
 */
class GovCMSMigrateWordPressEexOpportunities extends GovCMSMigrateWordPressBundle {
  /**
   * GovCMSMigrateWordPressOpportunities constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['bundle'] = $arguments['opportunities_type'];
    $arguments['post_type'] = 'eex_opportunity';
    parent::__construct($arguments);
  }
}

/**
 * Class GovCMSMigrateWordPressEexCaseStudy.
 */
class GovCMSMigrateWordPressEexCaseStudy extends GovCMSMigrateWordPressBundle {
  /**
   * GovCMSMigrateWordPressEexCaseStudy constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['bundle'] = $arguments['case_studies_type'];
    $arguments['post_type'] = 'eex_case_study';
    parent::__construct($arguments);
  }
}

/**
 * Class GovCMSMigrateWordPressEexEvent.
 */
class GovCMSMigrateWordPressEexEvent extends GovCMSMigrateWordPressBundle {
  /**
   * GovCMSMigrateWordPressEexEvent constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['bundle'] = $arguments['events_type'];
    $arguments['post_type'] = 'eex_event';
    parent::__construct($arguments);
  }
}

/**
 * Class GovCMSMigrateWordPressEexResources.
 */
class GovCMSMigrateWordPressEexResources extends GovCMSMigrateWordPressBundle {
  /**
   * GovCMSMigrateWordPressEexResources constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['bundle'] = $arguments['additional_resources_type'];
    $arguments['post_type'] = 'eex_resources';
    parent::__construct($arguments);
  }
}

/**
 * Class GovCMSMigrateWordPressEexContact.
 */
class GovCMSMigrateWordPressEexContact extends GovCMSMigrateWordPressBundle {
  /**
   * GovCMSMigrateWordPressEexContact constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['bundle'] = $arguments['contacts_type'];
    $arguments['post_type'] = 'eex_contact';
    parent::__construct($arguments);
  }
}

/**
 * Class GovCMSMigrateWordPressGlossary.
 */
class GovCMSMigrateWordPressGlossary extends GovCMSMigrateWordPressBundle {
  /**
   * GovCMSMigrateWordPressGlossary constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['bundle'] = $arguments['glossary_type'];
    $arguments['post_type'] = 'eex_glossary_term';
    parent::__construct($arguments);
  }
}

/**
 * Class GovCMSMigrateWordPressEexProgram.
 */
class GovCMSMigrateWordPressEexProgram extends GovCMSMigrateWordPressBundle {
  /**
   * GovCMSMigrateWordPressEexProgram constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['bundle'] = $arguments['programs_type'];
    $arguments['post_type'] = 'eex_program';
    parent::__construct($arguments);
  }
}

/**
 * Class GovCMSMigrateWordPressEeoOpportunities.
 */
class GovCMSMigrateWordPressEeoOpportunities extends GovCMSMigrateWordPressBundle {
  /**
   * GovCMSMigrateWordPressEeoOpportunities constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['bundle'] = $arguments['eeo_opportunities_type'];
    $arguments['post_type'] = 'eeo_opportunity';
    parent::__construct($arguments);
  }
}
