<?php

/**
 * @file
 * Menu migration class.
 */

/**
 * Class MigrateWordPressMenu.
 */
class MigrateWordPressMenu extends WordPressMigration {
  /**
   * MigrateWordPressMenu constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    parent::__construct($arguments);
  }
}

/**
 * Class WordPressMenuLinksSource.
 */
class MigrateWordPressMenuLinksSource extends WordPressItemSource {
  private $_menu_name;

  /**
   * WordPressMenuLinksSource constructor.
   * @param array|string $filename
   * @param string $cache_key
   */
  public function __construct($filename, $cache_key, $menu_name = 'Main') {
    parent::__construct($filename, 'nav_menu_item', $cache_key);
    $this->setMenuName($menu_name);
  }

  /**
   * Count menu items.
   * @return int
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

        // If menu name is matched, return count number.
        if ($post_type == $this->postType && $menu_name == $this->getMenuName()) {
          $count++;
        }
      }
    }

    return $count;
  }

  /**
   * @return mixed
   */
  public function getMenuName() {
    return $this->_menu_name;
  }

  /**
   * @param mixed $_menu_name
   */
  public function setMenuName($menu_name) {
    $this->_menu_name = $menu_name;
  }
}

/**
 * Class MigrateWordPressMenuLinks.
 */
class MigrateWordPressMenuLinks extends WordPressMigration {
  /**
   * MigrateWordPressMenuLinks constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    // Construct the source object.
    $this->source = new MigrateWordPressMenuLinksSource($this->wxrFile, $this->machineName);
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

    // Set up menu parent.
    $this->addFieldMapping('plid', 'menu_parent')
      ->defaultValue('0')
      ->sourceMigration($this->getMachineName());
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

    // Set not migration field.
    $this->addFieldMapping(NULL, 'guid')
      ->description('same as link, plus isPermaLink attribute?')
      ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'description')
      ->description('Always empty?')
      ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'content:encoded')
      ->description('Not with menu')
      ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'content')
      ->description('Not with menu')
      ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'pubDate')
      ->description('Use post_date')
      ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'dc:creator')
      ->description('Not with Menu')
      ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'wp:post_id')
      ->description('Not with Menu')
      ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'wp:post_date')
      ->description('Not with Menu')
      ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'wp:post_date_gmt')
      ->description('Not with Menu')
      ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'wp:comment_status')
      ->description('Not with menu')
      ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'wp:ping_status')
      ->description('What does this mean?')
      ->issueGroup(t('Open issues'))
      ->issuePriority(MigrateFieldMapping::ISSUE_PRIORITY_MEDIUM);
    $this->addFieldMapping(NULL, 'wp:post_name')
      ->description('Looks like last component of path')
      ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'wp:post_parent')
      ->description('Not with menu')
      ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'wp:post_type')
      ->description('Not with menu')
      ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'wp:post_password')
      ->description('Not with menu')
      ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'wp:is_sticky')
      ->description('Not with menu')
      ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'category')
      ->description('Not with menu')
      ->issueGroup(t('DNM'));
    $this->addFieldMapping(NULL, 'tag')
      ->description('Not with menu')
      ->issueGroup(t('DNM'));
  }

  /**
   * Prepare source row.
   * @param $row
   * @return bool
   */
  public function prepareRow($row) {
    // Always include this fragment at the beginning of every prepareRow()
    // implementation, so parent classes can ignore rows.
    if (parent::prepareRow($row) === FALSE) {
      // drupal_debug($row, 'prepareRow: return FALSE at beginning.');

      return FALSE;
    }

    $wp_row = $row->xml->children($this->arguments['namespaces']['wp']);
    // Skip any of the wrong post type
    if ($wp_row->post_type != 'nav_menu_item') {
      $this->skippedItems[] = $row->{'wp:post_id'};

      return FALSE;
    }

    // Skip if not main menu.
    $menu_name = $this->xpathValue($row->xml->xpath('category[@domain="nav_menu"]'));
    if ($menu_name != 'Main') {
      $this->skippedItems[] = $row->{'wp:post_id'};

      return FALSE;
    }

    $menu_item_object = $this->xpathValue($row->xml->xpath('wp:postmeta/wp:meta_key[.=\'_menu_item_object\']/following-sibling::wp:meta_value'));
    if ($menu_item_object != 'page') {
      $this->skippedItems[] = $row->{'wp:post_id'};

      return FALSE;
    }

    $menu_item_parent = $this->xpathValue($row->xml->xpath('wp:postmeta/wp:meta_key[contains(text(), \'_menu_item_menu_item_parent\')]/following-sibling::wp:meta_value'));
    $menu_item_object_id = $this->xpathValue($row->xml->xpath('wp:postmeta/wp:meta_key[contains(text(), \'_menu_item_object_id\')]/following-sibling::wp:meta_value'));
    $menu_item_name = $this->xpathValue($row->xml->xpath('title'));

    // Try to find node id.
    $source_migrates = $this->dependencies;
    $nid = $this->handleSourceMigration($source_migrates, $menu_item_object_id);
    $node = node_load($nid);
    if (!$node) {
      $this->skippedItems[] = $row->{'wp:post_id'};

      return FALSE;
    }
    $row->link = 'node/' . $nid;
    $row->title = !empty($menu_item_name) ? $menu_item_name : $node->title;

    // Set up menu parent.
    $row->menu_parent = !empty($menu_item_parent) ? $menu_item_parent : '0';

    // Make sure we actually have a menu link.
    if (!isset($row->link) || empty($row->title)) {
      $this->skippedItems[] = $row->{'wp:post_id'};

      return FALSE;
    }

    return TRUE;
  }

  /**
   * Return xpath value.
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
