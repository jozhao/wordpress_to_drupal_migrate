<?php

/**
 * @file
 * Attachment migration.
 */

/**
 * Class GovCMSMigrateWordPressAttachment.
 */
class GovCMSMigrateWordPressAttachment extends MigrateWordPressAttachment {
  /**
   * GovCMSMigrateWordPressAttachment constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('file_replace', NULL, FALSE)
      ->defaultValue(FILE_EXISTS_REPLACE);
  }
}
