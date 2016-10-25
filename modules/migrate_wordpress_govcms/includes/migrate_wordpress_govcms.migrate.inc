<?php

/**
 * @file
 * govCMS migrate classes.
 */

/**
 * Class GovCMSMigrateWordPress.
 */
class GovCMSMigrateWordPress extends MigrateWordPress {
  /**
   * Register migration classes.
   */
  public function migrationClasses() {
    $classes = parent::migrationClasses();
    $classes['WordPressEexOpportunities'] = 'GovCMSMigrateWordPressEexOpportunities';
    $classes['WordPressEexCaseStudy'] = 'GovCMSMigrateWordPressEexCaseStudy';
    $classes['WordPressEexEvent'] = 'GovCMSMigrateWordPressEexEvent';
    $classes['WordPressEexResources'] = 'GovCMSMigrateWordPressEexResources';
    $classes['WordPressEexContact'] = 'GovCMSMigrateWordPressEexContact';
    $classes['WordPressGlossary'] = 'GovCMSMigrateWordPressGlossary';
    $classes['WordPressEexProgram'] = 'GovCMSMigrateWordPressEexProgram';
    $classes['WordPressEeoOpportunities'] = 'GovCMSMigrateWordPressEeoOpportunities';
    $classes['WordPressPage'] = 'GovCMSMigrateWordPressPage';
    $classes['WordPressBlogEntry'] = 'GovCMSMigrateWordPressBlogEntry';
    $classes['WordPressAttachment'] = 'GovCMSMigrateWordPressAttachment';

    return $classes;
  }
}
