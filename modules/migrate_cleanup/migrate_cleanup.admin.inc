<?php

/**
 * @file
 * Module admin inc.
 */

/**
 * Form.
 *
 * @param $form
 * @param $form_state
 * @return mixed
 */
function migrate_cleanup_form() {
  $form['migrate_cleanup_rebuild'] = array(
    '#type' => 'fieldset',
    '#title' => t('Migrate - Clean up'),
    '#description' => t('Rebuild the contents, then update the values in the database.'),
  );

  $form['migrate_cleanup_rebuild']['migrate_cleanup_rebuild_run'] = array(
    '#type' => 'submit',
    '#value' => t('Cleanup the migrated contents'),
    '#suffix' => '<span class="description">' . t('This could take time and might put an increased load on your server.') . '</span>',
  );

  return $form;
}

/**
 * Submit form.
 *
 * @param $form
 * @param $form_state
 */
function migrate_cleanup_form_submit($form, &$form_state) {
  if ($form_state['values']['op'] == t('Cleanup the migrated contents')) {
    migrate_cleanup_process();
    drupal_set_message(t('Done, Cheers'));
  }
  else {
    drupal_set_message(t('An error has been detected'), 'error');
  }
}
