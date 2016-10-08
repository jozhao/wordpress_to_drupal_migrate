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

  /**
   * Return a count of all available source records.
   */
  public function computeCount() {
    $count = 0;
    foreach ($this->sourceUrls as $url) {
      $reader = new $this->readerClass($url, $this->elementQuery, $this->idQuery);
      foreach ($reader as $element) {
        // Only count relevant postType
        $field = 'wp:post_type';

        $post_type = current($element->xpath($field));

        // Check menu name.
        $menu = 'category[@domain="nav_menu"]';
        $menu_name = current($element->xpath($menu));

        // Hard code main menu here.
        if ($post_type == $this->postType && $menu_name == 'Main') {
          $count++;
        }
      }
    }

    return $count;
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
    // Always include this fragment at the beginning of every prepareRow()
    // implementation, so parent classes can ignore rows.
    if (parent::prepareRow($row) === FALSE) {
      drupal_debug($row, 'prepareRow: return FALSE at beginning.');

      return FALSE;
    }

    $wp_row = $row->xml->children($this->arguments['namespaces']['wp']);
    // Skip any of the wrong post type
    if ($wp_row->post_type != 'nav_menu_item') {
      $this->skippedItems[] = $row->{'wp:post_id'};

      // drupal_debug($row, 'prepareRow: return FALSE since the menu type is not nav_menu_item.');

      return FALSE;
    }

    // Skip if not main menu.
    $menu_name = $this->xpathValue($row->xml->xpath('category[@domain="nav_menu"]'));
    if ($menu_name != 'Main') {
      $this->skippedItems[] = $row->{'wp:post_id'};
      drupal_debug($row, 'prepareRow: return FALSE since the menu is not Main.');

      return FALSE;
    }

    $menu_item_object = $this->xpathValue($row->xml->xpath('wp:postmeta/wp:meta_key[.=\'_menu_item_object\']/following-sibling::wp:meta_value'));
    if ($menu_item_object != 'page') {
      $this->skippedItems[] = $row->{'wp:post_id'};
      drupal_debug($row, 'prepareRow: return FALSE since the menu item object is not page');
      drupal_debug($menu_item_object, 'prepareRow: $menu_item_object');

      return FALSE;
    }

    $menu_item_parent = $this->xpathValue($row->xml->xpath('wp:postmeta/wp:meta_key[contains(text(), \'_menu_item_menu_item_parent\')]/following-sibling::wp:meta_value'));
    $menu_item_object_id = $this->xpathValue($row->xml->xpath('wp:postmeta/wp:meta_key[contains(text(), \'_menu_item_object_id\')]/following-sibling::wp:meta_value'));
    drupal_debug($menu_item_object_id, 'prepareRow: $menu_item_object_id');

    // Try to find node id.
    $source_migrates = ['eexgovauEnergyEfficiencyExchangePage'];
    $nid = $this->handleSourceMigration($source_migrates, $menu_item_object_id);
    drupal_debug($nid, 'prepareRow: $nid');
    $node = node_load($nid);
    if (!$node) {
      $this->skippedItems[] = $row->{'wp:post_id'};

      return FALSE;
    }
    $row->link = 'node/' . $nid;
    $row->title = $node->title;

    // Make sure we actually have a menu link.
    if (!isset($row->link) || empty($row->title)) {
      $this->skippedItems[] = $row->{'wp:post_id'};

      return FALSE;
    }

    drupal_debug($row, 'prepareRow: return TRUE and set up this menu.');

    return TRUE;
  }

  /**
   * Reruan xpath value.
   * @param $result
   * @return string
   */
  public function xpathValue($result) {
    if (is_array($result)) {
      return (string) reset($result);
    }
    else {
      return (string) $result;
    }
  }
}
