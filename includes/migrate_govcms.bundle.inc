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
 * Class GovCMSMigrateWordPressGlossary.
 */
class GovCMSMigrateWordPressGlossary extends GovCMSMigrateWordPressBundle {
  /**
   * GovCMSMigrateWordPressGlossary constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['bundle'] = $arguments['bundle_glossary'];
    $arguments['post_type'] = 'glossary';
    parent::__construct($arguments);
  }
}
