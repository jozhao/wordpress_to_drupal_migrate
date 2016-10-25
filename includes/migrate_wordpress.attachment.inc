<?php

/**
 * @file
 * Attachment migration.
 */

/**
 * Class MigrateWordPressAttachment.
 */
class MigrateWordPressAttachment extends WordPressAttachment {
  /**
   * MigrateWordPressAttachment constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    parent::__construct($arguments);
  }
}