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
 * Class GovCMSWordPressMenuLinksSource.
 */
class GovCMSWordPressMenuLinksSource extends WordPressItemSource {
  /**
   * GovCMSWordPressMenuLinksSource constructor.
   * @param array|string $filename
   * @param string $post_type
   * @param string $cache_key
   * @param array $namespaces
   */
  public function __construct($filename, $cache_key) {
    parent::__construct($filename, 'nav_menu_item', $cache_key);
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
    $this->source = new GovCMSWordPressMenuLinksSource($this->wxrFile, $this->machineName);
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
      MigrateDestinationMenuLinks::getKeySchema()
    );

    // Always main menu.
    $this->addFieldMapping('menu_name')->defaultValue('main-menu');
    // Path of the link.
    $this->addFieldMapping('link_path', 'link');
    // Set this path to node path.
    $this->addFieldMapping('router_path')->defaultValue('node/%');
    // Set link title as post title.
    $this->addFieldMapping('link_title', 'title')->xpath('title');
    // Internal.
    $this->addFieldMapping('external', 'external')->defaultValue('0');
    // Set expanded default.
    $this->addFieldMapping('expanded')->defaultValue('0');
    // Set menu weight.
    $this->addFieldMapping('weight', 'wp:menu_order')->xpath('wp:menu_order');
    // A flag to indicate that the user has manually created or edited.
    $this->addFieldMapping('customized')->defaultValue('0');
    // Will be overridden automatically.
    $this->addFieldMapping('has_children')->defaultValue('0');
    // Will be overridden automatically.
    $this->addFieldMapping('depth')->defaultValue('1');

    // Add un-migrated fields.
    $this->addUnmigratedDestinations(array(
      'module',
      'hidden',
      'options',
      'p1',
      'p2',
      'p3',
      'p4',
      'p5',
      'p6',
      'p7',
      'p8',
      'p9',
      'updated',
    ));
  }

  /**
   * @param $row
   */
  public function prepareRow($row) {
    $wp_row = $row->xml->children($this->arguments['namespaces']['wp']);
    // Skip any of the wrong post type
    if ($wp_row->post_type != 'nav_menu_item') {
      $this->skippedItems[] = $row->{'wp:post_id'};

      return FALSE;
    }

    // If the link has a query string, don't produce a path
    $row->link = (string) $row->xml->link;
    if (strpos($row->link, '?')) {
      unset($row->link);
    }
    else {
      // Otherwise, strip the domain portion of the URL
      $matches = array();
      if (preg_match('|https?://[^/]+/(.*)|', $row->link, $matches)) {
        $row->link = $matches[1];
        // Strip the last slash off of the URL (the Path module can't handle this)
        $row->link = rtrim($row->link, '/');
        // Convert the alias to the node path.
        $node_path = drupal_get_normal_path($row->link);
        // If is it external link.
        if ($node_path == $row->link) {
          $row->external = 1;
        }
        $row->link = $node_path;
      }
      else {
        unset($row->link);
      }
    }

    // Set menu link title if it is empty.
    if (empty($row->title)) {
      $row->title = 'test';
    }

    // Make sure we actually have a menu link.
    if (!isset($row->link)) {
      return FALSE;
    }

    return TRUE;
  }
}
