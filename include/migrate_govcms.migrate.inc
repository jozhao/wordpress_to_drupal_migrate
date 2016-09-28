<?php

/**
 * @file
 * govCMS migrate classes.
 */

/**
 * Class GovCMSMigrateWordPress.
 */
class GovCMSMigrateWordPress extends WordPressBlog {
  /**
   * Register migration classes.
   */
  public function migrationClasses() {
    $classes = parent::migrationClasses();
    $classes['WordPressGlossary'] = 'GovCMSMigrateWordPressGlossary';
    return $classes;
  }
}
