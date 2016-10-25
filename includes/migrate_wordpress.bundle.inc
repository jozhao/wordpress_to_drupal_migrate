<?php

/**
 * @file
 * Migrate bundle from a WordPress blog.
 */

/**
 * Class MigrateWordPressBundle.
 */
class MigrateWordPressBundle extends MigrateWordPressItemMigration {
  /**
   * MigrateWordPressBundle constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    parent::__construct($arguments);
  }

  /**
   * Prepare the row.
   * @param \stdClass $row
   * @return bool|string
   */
  public function prepareRow($row) {
    return parent::prepareRow($row);
  }

  /**
   * Return xpath value as string.
   * @param $result
   * @return string
   */
  public function xpathValue($result) {
    return (string) reset($result);
  }
}
