<?php

/**
 * @file
 * Migrate base class from a WordPress blog into govCMS.
 */

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
