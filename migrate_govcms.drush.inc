<?php

/**
 * Drush helper.
 */

/**
 * Implements hook_drush_command().
 */
function migrate_govcms_drush_command() {
  $items = [];

  $items['migrate-govcms-migrate-build'] = [
    'description' => 'Creates the WordPress migrations',
    'examples' => array(
      'migrate-govcms-migrate-build' => 'Creates the WordPress migrations',
    ),
    'drupal dependencies' => array('migrate_govcms'),
    'aliases' => array('mgmb'),
  ];

  return $items;
}

/**
 * Creating and Storing WordPress Migrate Migrations.
 */
function drush_migrate_govcms_migrate_build() {
  // Reset the file_get_stream_wrappers static cache.
  $wrappers_storage = &drupal_static('file_get_stream_wrappers', NULL, TRUE);

  module_load_include('inc', 'migrate_ui', 'migrate_ui.wizard');

  // Prepare custom content.
  $site_info = migrate_govcms_site_info();
  $site_info['wxr_file'] = $site_info['wxr_path'] . "/" . $site_info['wxr_filename'];
  $site_info['default_author'] = 'Site Factory admin';
  $site_info['attachment_field'] = 'field_image';

  $file_info = _migrate_govcms_file_object($site_info['wxr_file']);

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
  $form_state['wizard']->sourceDataFormValidate($form_state);
  $form_state['wizard']->customContentSelectFormValidate($form_state);
  $form_state['wizard']->reviewForm($form_state);

  // Submit the form.
  drupal_form_submit('migrate_ui_wizard', $form_state);
  // Save the settings into the wizard object.
  $form_state['wizard']->formSaveSettings();
  // Display success message.
  drush_print(dt('The migration is created successfully.'));
}

/**
 * @param $uri
 * @return bool|object
 */
function _migrate_govcms_file_object($uri) {
  return file_uri_to_object($uri, $use_existing = FALSE);
}
