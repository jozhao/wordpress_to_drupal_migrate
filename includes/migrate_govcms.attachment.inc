<?php

/**
 * Class GovCMSMigrateWordPressAttachment.
 */
class GovCMSMigrateWordPressAttachment extends WordPressAttachment {
  /**
   * GovCMSMigrateWordPressAttachment constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    // Add custom content types dependencies.
    $arguments['dependencies'][] = 'EexOpportunities';
    $arguments['dependencies'][] = 'CaseStudies';
    $arguments['dependencies'][] = 'Events';
    $arguments['dependencies'][] = 'EexResources';
    $arguments['dependencies'][] = 'EexContact';
    $arguments['dependencies'][] = 'EexGlossary';
    $arguments['dependencies'][] = 'Programs';
    $arguments['dependencies'][] = 'EeoOpportunities';
    parent::__construct($arguments);
  }
}
