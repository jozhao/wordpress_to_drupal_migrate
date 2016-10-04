<?php

/**
 * @file
 * Migrate base class from a WordPress blog into govCMS.
 */

/**
 * Class GovCMSMigrateWordPressItemSource.
 */
class GovCMSMigrateWordPressItemSource extends WordPressItemSource {
  /**
   * @var
   */
  private $_bundle = '';

  /**
   * GovCMSMigrateWordPressItemSource constructor.
   * @param array|string $filename
   * @param string $post_type
   * @param string $cache_key
   * @param array $namespaces
   */
  public function __construct($filename, $post_type, $cache_key, array $namespaces) {
    $this->fields = $this->fields();
    parent::__construct($filename, $post_type, $cache_key, $namespaces);
  }

  /**
   * Set up source fields.
   */
  public function fields() {
    $fields = parent::fields();
    $custom_fields = $this->getCustomFields();

    return $fields + $custom_fields;
  }

  /**
   * @return mixed
   */
  public function getBundle() {
    return $this->_bundle;
  }

  /**
   * @param mixed $bundle
   */
  public function setBundle($bundle) {
    $this->_bundle = $bundle;
  }

  /**
   * @return array
   */
  public function getCustomFields() {
    $custom_fields = [];

    // Prepare custom content.
    $site_info = migrate_govcms_site_info();
    $migrate_fields = !empty($site_info['fields']) ? $site_info['fields'] : NULL;
    $bundles = !empty($site_info['bundles']) ? $site_info['bundles'] : NULL;
    $bundle = $this->getBundle();

    // Only load fields defined in migration site information.
    if (!empty($bundle) && !empty($migrate_fields) && isset($bundles[$bundle])) {
      $bundle_fields = $bundles[$bundle]['fields'];
      foreach ($bundle_fields as $bundle_field) {
        $custom_fields[$bundle_field] = $migrate_fields[$bundle_field]['migrate_description'];
      }
    }

    return $custom_fields;
  }
}

/**
 * Class GovCMSMigrateWordPressItemMigration.
 */
class GovCMSMigrateWordPressItemMigration extends WordPressItemMigration {
  /**
   * GovCMSMigrateWordPressItemMigration constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments = []) {
    parent::__construct($arguments);

    // Construct the source objects.
    $this->source = new GovCMSMigrateWordPressItemSource($this->wxrFile, $this->postType, $this->machineName, $this->arguments['namespaces']);
    $this->source->setBundle($this->arguments['bundle']);
  }

  /**
   * @param \stdClass $row
   */
  public function prepareRow($row) {
    // Always include this fragment at the beginning of every prepareRow()
    // implementation, so parent classes can ignore rows.
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    // Interpret the wordpress [] short tags.
    $replacements = [
      '[frame_box]' => '<div class="frame_box">',
      '[/frame_box]' => '</div>',
      '[info]' => '<div class="info_box">',
      '[/info]' => '</div>',
      '[line]' => '<div class="line_shortcut" style="padding-top:0px; padding-bottom:0px;"></div>',
      '<h1' => '<h2',
      '</h1>' => '</h2>',
    ];
    $row->content = str_replace(array_keys($replacements), $replacements, $row->content);

    return TRUE;
  }
}
