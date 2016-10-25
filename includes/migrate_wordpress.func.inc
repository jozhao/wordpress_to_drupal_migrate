<?php

/**
 * @file
 * Migrate functions.
 */

/**
 * Return site migration information.
 *
 * @return array
 */
function _migrate_wordpress_get_site_info() {
  return [
    'source_select' => '0',
    'domain' => '',
    'wxr_filename' => 'wordpress_export.xml',
    'wxr_path' => 'public://migrate',
    'do_migration' => 1,
    'default_author' => 'admin',
    'page_type' => 'page',
    'blog_post_type' => 'blog_article',
    'path_action' => 1,
    'podcast_field' => '',
    'tag_field' => 'field_tags',
    'category_field' => 'field_categories',
    'generate_redirects' => '',
    'comments' => '',
    'attachment_field' => '',
    'text_format' => 'rich_text',
    'text_format_comment' => 'rich_text',
  ];
}
