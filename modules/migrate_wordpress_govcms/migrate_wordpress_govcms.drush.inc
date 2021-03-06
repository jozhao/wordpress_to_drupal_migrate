<?php

/**
 * @file
 * Drush helper.
 */

/**
 * Implements hook_drush_command().
 */
function migrate_wordpress_govcms_drush_command() {
  $items = [];

  $items['migrate-wordpress-build-govcms'] = [
    'description' => 'Create the WordPress migrations',
    'examples' => array(
      'migrate-wordpress-build-govcms' => 'Create the WordPress migrations',
    ),
    'drupal dependencies' => array('migrate_wordpress'),
    'aliases' => array('mwbg'),
  ];

  return $items;
}

/**
 * Creating and Storing WordPress Migrate Migrations.
 */
function drush_migrate_wordpress_govcms_migrate_wordpress_build_govcms() {
  drush_log(dt('Start creating the migration.'), 'ok');
  // Reset the file_get_stream_wrappers static cache.
  $wrappers_storage = &drupal_static('file_get_stream_wrappers', NULL, TRUE);

  module_load_include('inc', 'migrate_ui', 'migrate_ui.wizard');

  // Prepare custom content.
  $site_info = migrate_wordpress_site_info();
  $site_info['wxr_file'] = $site_info['wxr_path'] . "/" . $site_info['wxr_filename'];
  $site_info['default_author'] = 'Site Factory admin';
  $site_info['attachment_field'] = 'field_image';

  drush_log(dt('Try to get XML file object information.'));
  $file_info = _migrate_wordpress_file_object($site_info['wxr_file']);

  drush_log(dt('Ready to build migration instance.'));
  $_FILES['files']['tmp_name']['wxr_file'] = $file_info->uri;
  $_FILES['files']['name']['wxr_file'] = $file_info->filename;
  $_FILES['files']['error']['wxr_file'] = 0;
  $_FILES['files']['size']['wxr_file'] = $file_info->filesize;

  // Add custom bundles.
  foreach ($site_info['bundles'] as $bundle => $bundle_values) {
    $site_info[$bundle . '_type'] = $bundle;
  }

  $form_state['values'] = $site_info;
  $form_state_values = $form_state['values'];

  // Build the import form.
  $form = drupal_get_form('migrate_ui_wizard', 'GovCMSMigrateWordPressWizard');
  $form = migrate_ui_wizard($form, $form_state, 'GovCMSMigrateWordPressWizard');
  // Create a Migrate Wizard object.
  $form_state['wizard'] = new GovCMSMigrateWordPressWizard();
  // Add migration extender.
  $form_state['wizard']->addExtender('GovCMSMigrateWordPressWizardExtender');
  drush_log(dt('Start building migration instance file.'));
  $form_state['wizard']->sourceDataFormValidate($form_state);
  drush_log(dt('Start adding migration bundles classes file.'));
  $form_state['wizard']->authorFormValidate($form_state);
  $form_state['wizard']->contentSelectFormValidate($form_state);
  $form_state['wizard']->contentBlogPostFormValidate($form_state);
  $form_state['wizard']->contentPageFormValidate($form_state);
  $form_state['wizard']->customContentSelectFormValidate($form_state);
  drush_log(dt('Start building migration instance classes.'));
  $form_state['wizard']->reviewForm($form_state);

  // Submit the form.
  drush_log(dt('Final step to save the migration settings.'));
  drupal_form_submit('migrate_ui_wizard', $form_state);
  // Save the settings into the wizard object.
  $form_state['wizard']->formSaveSettings();
  // Display success message.
  drush_log(dt('The migration is created successfully.'), 'ok');
}

/**
 * @param $uri
 * @return bool|object
 */
function _migrate_wordpress_file_object($uri) {
  return file_uri_to_object($uri, $use_existing = FALSE);
}
