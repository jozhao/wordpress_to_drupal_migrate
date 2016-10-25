<?php

/**
 * @file
 * Migrate base class from a WordPress blog into govCMS.
 */

/**
 * Class GovCMSMigrateWordPressItemMigration.
 */
class GovCMSMigrateWordPressItemMigration extends MigrateWordPressItemMigration {
  /**
   * @param \stdClass $row
   */
  public function prepareRow($row) {
    // Always include this fragment at the beginning of every prepareRow()
    // implementation, so parent classes can ignore rows.
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    return TRUE;
  }
}
