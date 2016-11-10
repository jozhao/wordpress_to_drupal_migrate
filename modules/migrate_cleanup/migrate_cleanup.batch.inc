<?php

/**
 * @file
 * Batch file.
 */

/**
 * Process entity.
 *
 * @param $entity_id
 * @param $context
 */
function migrate_cleanup_rebuild_batch_process_entity($entity_id, &$context) {
  $entity = entity_load_single('node', $entity_id);
  // If entity can be loaded.
  if ($entity) {
    $node_wrapper = entity_metadata_wrapper('node', $entity);
    // Check if body value is set.
    if ($node_wrapper && $node_wrapper->body->value()) {
      $content = $entity->body['und'][0]['value'];
      // Check if content is empty.
      if (!empty($content)) {
        $actions = [
          'content',
          //'token',
        ];

        if (in_array('content', $actions)) {
          $content = str_replace('<p>&nbsp;</p>', '', $content);

          if (!empty($content)) {
            $entity->body['und'][0]['value'] = $content;
            node_save($entity);
          }
        }

        if (in_array('token', $actions)) {
          if (FALSE === strpos($content, '[')) {
            // Ignore this content.
          }
          else {
            // Load include file.
            module_load_include('inc', 'migrate_cleanup', 'includes/migrate_cleanup.wordpress.inc');

            $tokens = _migrate_cleanup_custom_tokens();

            // Find all registered tag names in $content.
            preg_match_all('@\[([^<>&/\[\]\x00-\x20=]++)@', $content, $matches);
            $tags = array_intersect(array_keys($tokens), $matches[1]);

            // Return if no tag found.
            if (!empty($tags)) {
              $content = _migrate_cleanup_token_process($content);

              if (!empty($content)) {
                $entity->body['und'][0]['value'] = $content;
                node_save($entity);
              }
            }
          }
        }
      }
    }
  }

  // Update batch progress information.
  if (!isset($context['results']['processed'])) {
    $context['results']['processed'] = 0;
  }
  $context['results']['processed']++;
  $context['message'] = t('We are processing the entity @title with id: @id', array(
    '@title' => $node_wrapper->label(),
    '@id' => $entity_id,
  ));
}

/**
 * Batch finished.
 *
 * @param $success
 * @param $results
 * @param $operations
 */
function migrate_cleanup_rebuild_batch_finished($success, $results, $operations) {
  if ($success) {
    $message = t('The contents has been cleaned and fixed.');
  }
  else {
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %error_operation with arguments: @arguments', array(
      '%error_operation' => $error_operation[0],
      '@arguments' => print_r($error_operation[1], TRUE),
    ));
  }

  // Clear cache.
  cache_clear_all();

  drupal_set_message($message);
}
