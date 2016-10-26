<?php

/**
 * @file
 * Migrate base class from a WordPress blog.
 */

/**
 * Class MigrateWordPressItemSource.
 */
class MigrateWordPressItemSource extends WordPressItemSource {
  /**
   * @var
   */
  private $_bundle = '';

  /**
   * MigrateWordPressItemSource constructor.
   * @param array|string $filename
   * @param string $post_type
   * @param string $cache_key
   * @param array $namespaces
   */
  public function __construct($filename, $post_type, $cache_key, array $namespaces) {
    // Set source fields.
    $this->fields = $this->fields();
    parent::__construct($filename, $post_type, $cache_key, $namespaces);
  }

  /**
   * Set source fields.
   * @return array
   */
  public function fields() {
    $fields = parent::fields();
    $custom_fields = $this->getCustomFields();

    return $fields + $custom_fields;
  }

  /**
   * Get custom fields.
   * @return array
   */
  protected function getCustomFields() {
    $custom_fields = [];

    // Prepare custom content.
    $site_info = migrate_wordpress_site_info();
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
}

/**
 * Class MigrateWordPressItemMigration.
 */
class MigrateWordPressItemMigration extends WordPressItemMigration {
  /**
   * MigrateWordPressItemMigration constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['generate_redirects'] = !empty($arguments['generate_redirects']) ? $arguments['generate_redirects'] : '';
    parent::__construct($arguments);

    // Construct the source objects.
    $this->source = new MigrateWordPressItemSource($this->wxrFile, $this->postType, $this->machineName, $this->arguments['namespaces']);
    $this->source->setBundle($this->arguments['bundle']);
  }

  /**
   * Prepare source row.
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
      '[highlight]' => '<div class="highlight">',
      '[/highlight]' => '</div>',
      '[threecol_one]' => '<div class="threecol-one">',
      '[/threecol_one]' => '</div>',
      '[threecol_one_last]' => '<div class="threecol-one last">',
      '[/threecol_one_last]' => '</div>',
      '[line]' => '<div class="line_shortcut" style="padding-top:0px; padding-bottom:0px;"></div>',
      '<h1' => '<h2',
      '</h1>' => '</h2>',
      '[h2]' => '<h2>',
      '[/h2]' => '</h2>',
      '[h3]' => '<h3>',
      '[/h3]' => '</h3>',
    ];
    $row->content = str_replace(array_keys($replacements), $replacements, $row->content);

    // Interpret the [quote] tags
    $row->content = preg_replace_callback('|(\[quote.*?\])(.*?)(\[/quote\])|i',
      array($this, 'replaceQuotes'), $row->content);

    return TRUE;
  }

  /**
   * Interpret quote tags.
   * @param array $matches
   * @return string
   */
  protected function replaceQuotes(array $matches) {
    $quote_open = $matches[1];
    $content = $matches[2];
    $quote_close = $matches[3];

    preg_match('|cite=\s?"(.*?)"|i', $quote_open, $matches);
    $cite = $matches[1];

    $result = '<blockquote>';
    $result .= $content;
    $result .= '<p class="bc-cite">' . $cite . '</p>';
    $result .= '</blockquote>';

    return $result;
  }
}
