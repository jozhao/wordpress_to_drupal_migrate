<?php

/**
 * Menu migration class.
 */

/**
 * Class GovCMSMigrateWordPressMenu.
 */
class GovCMSMigrateWordPressMenu extends WordPressMigration {
  /**
   * GovCMSMigrateWordPressMenu constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    parent::__construct($arguments);
  }
}

/**
 * Class GovCMSMigrateWordPressMenuLinks.
 */
class GovCMSMigrateWordPressMenuLinks extends WordPressMigration {
  /**
   * GovCMSMigrateWordPressMenuLinks constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // Construct the source object.
    $this->source = new WordPressAttachmentSource($this->wxrFile, $this->machineName);
    $this->destination = new MigrateDestinationMenuLinks();

    // post_id is the unique ID of items in WordPress
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'wp:post_id' => array(
          'type' => 'int',
          'not null' => TRUE,
          'unsigned' => TRUE,
          'description' => 'WordPress post ID',
        ),
      ),
      MigrateDestinationFile::getKeySchema()
    );
  }
}
