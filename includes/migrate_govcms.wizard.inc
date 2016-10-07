<?php

/**
 * @file
 * Migrate wizard UI.
 */

/**
 * Class GovCMSMigrateWordPressWizard.
 */
class GovCMSMigrateWordPressWizard extends WordPressMigrateWizard {
  /**
   * GovCMSMigrateWordPressWizard constructor.
   */
  public function __construct() {
    $this->addStep(t('Upload blog'), 'sourceDataForm');
    $this->addStep(t('Select content to import'), 'contentSelectForm');
    // Import custom content types.
    $this->addStep(t('Select custom content to import'), 'customContentSelectForm');
    $this->addStep(t('Review'), 'reviewForm');
  }

  /**
   * Getter function for the current step.
   */
  public function getCurrentStep() {
    return $this->currentStep;
  }

  /**
   * @return null|string
   */
  public function getSourceName() {
    return t('WordPress');
  }

  /**
   * Fetch and preprocess the uploaded WXR file.
   *
   * @param array $form_state
   */
  public function sourceDataFormValidate(&$form_state) {
    if ($_FILES['files']['error']['wxr_file'] && empty($form_state['values']['domain'])) {
      form_set_error('wxr_file', t('The file could not be uploaded, most likely
        because the file size exceeds the configured limit of !filesize',
        array('!filesize' => format_size(file_upload_max_size()))));

      return;
    }
    $directory = 'wordpress://';
    if (!file_prepare_directory($directory, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS)) {
      form_set_error('wxr_file',
        t('Could not prepare directory %directory - make sure your Drupal files directory exists and is writable',
          array('%directory' => $directory)));

      return;
    }

    $tmpfile = $_FILES['files']['tmp_name']['wxr_file'];
    // Note that for either path we take here, $tmpfile will be the name of
    // the uploaded/retrieved file, and $destination will be the name of the
    // desired final destination.
    if ($tmpfile) {
      // Handle uploaded file
      $filename = $_FILES['files']['name']['wxr_file'];
      $this->filename = $directory . str_replace(' ', '%20', $filename);
    }
    else {
      // Export the WordPress blog directly
      $domain = preg_replace('/http[s]?\:\/\//', '', $form_state['values']['domain']);

      // Login to the WordPress site
      $wordpress_version = 3;
      $login_url = 'http://' . $domain . '/wp-login.php';
      if (!($handle = fopen($login_url, 'r'))) {
        $wordpress_version = 2;
        $login_url = 'http://' . $domain . '/blog/wp-login.php';
        $handle = fopen($login_url, 'r');
      }
      if (!$handle) {
        form_set_error('credentials][domain', t('Could not find login page for !domain',
          array('!domain' => $domain)));
      }
      fclose($handle);

      // Use a temp file for cookies.
      $cookie_file = file_directory_temp() . '/wpimport-cookie.txt';

      $username = $form_state['values']['username'];
      $password = $form_state['values']['password'];
      $ch = curl_init();
      curl_setopt($ch, CURLOPT_URL, $login_url);
      curl_setopt($ch, CURLOPT_HEADER, 1);
      curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
      curl_setopt($ch, CURLOPT_USERAGENT, 'Importer');
      curl_setopt($ch, CURLOPT_COOKIESESSION, 1);
      curl_setopt($ch, CURLOPT_COOKIEJAR, $cookie_file);
      curl_setopt($ch, CURLOPT_COOKIEFILE, $cookie_file);
      curl_setopt($ch, CURLOPT_POST, 1);
      curl_setopt($ch, CURLOPT_POSTFIELDS, "log=$username&pwd=$password&testcookie=1");
      $login_result = curl_exec($ch);
      curl_close($ch);

      // Login successful? Grab the export
      if ((strpos($login_result, 'Set-Cookie: wordpress_logged_in')) ||
        (strpos($login_result, 'Set-Cookie: wordpressuser_')) ||
        (strpos($login_result, 'Set-Cookie: wordpress_test_cookie'))
      ) {
        $filename = $domain . '.xml';
        // The "domain" may have included a subdirectory - flatten things out
        $this->filename = $directory . '/' . str_replace('/', '_', $filename);
        $tmpfile = tempnam(sys_get_temp_dir(), 'wp_');
        $export_url = 'http://' . $domain;
        if ($wordpress_version == 2) {
          $export_url .= '/blog';
        }
        $export_url .= '/wp-admin/export.php?mm_start=all&mm_end=all&author=all' .
          '&export_taxonomy[category]=0&export_taxonomy[post_tag]=0&export_post_type=all' .
          '&export_post_status=all&download=true';
        $fp = fopen($tmpfile, 'w');
        if ($fp) {
          $ch = curl_init();
          curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
          curl_setopt($ch, CURLOPT_FILE, $fp);
          curl_setopt($ch, CURLOPT_COOKIEFILE, $cookie_file);
          curl_setopt($ch, CURLOPT_URL, $export_url);
          curl_exec($ch);
          curl_close($ch);
          fclose($fp);
          unlink($cookie_file);
        }
        else {
          form_set_error('credentials][domain', t('Could not create destination file !filename',
            array('!filename' => $tmpfile)));

          return;
        }
      }
      else {
        form_set_error('credentials][domain', t('Could not login at !login_url',
          array('!login_url' => $login_url)));

        return;
      }
    }

    $this->namespaces = WordPressBlog::preprocessFile($tmpfile, $this->filename);

    // Only include the author step if we have author data (which was introduced
    // in WXR 1.1)
    $blog = wordpress_migrate_blog($this->filename);
    if ($blog->getWxrVersion() != '1.0') {
      $this->addStep(t('Authors'), 'authorForm', $this->currentStep);
    }
    else {
      $this->authorMigration = FALSE;
      global $user;
      $this->defaultAuthorUid = $user->uid;
    }
    // Truncate the groupName so map/message table names don't get too long.
    $this->groupName = substr($blog->getTitle(), 0, 63 - strlen('migrate_message_blogpostcomment'));
    $this->groupTitle = t('!title (!url)',
      array(
        '!title' => $blog->getDisplayTitle(),
        '!url' => $blog->getBlogUrl(),
      ));
  }

  /**
   * Prepare for registration of any user-related migrations.
   *
   * @param array $form_state
   */
  public function authorFormValidate(&$form_state) {
    if ($form_state['values']['do_migration']) {
      $this->authorMigration = TRUE;
    }
    else {
      $this->authorMigration = FALSE;
    }
    $account = user_load_by_name($form_state['values']['default_author']);
    $this->defaultAuthorUid = $account->uid;
  }

  /**
   * @param $form_state
   */
  public function contentSelectFormValidate(&$form_state) {
    // Start clean in case we came here via Previous.
    unset($this->contentValues['blog']);
    unset($this->contentValues['page']);
    $this->removeStep(t('Blog posts'));
    $this->removeStep(t('Pages'));

    $this->contentValues['page']['page_type'] = $form_state['values']['page_type'];
    if ($this->contentValues['page']['page_type']) {
      $this->addStep(t('Pages'), 'contentPageForm', $this->currentStep);
    }
    $this->contentValues['blog']['post_type'] = $form_state['values']['blog_post_type'];
    if ($this->contentValues['blog']['post_type']) {
      $this->addStep(t('Blog posts'), 'contentBlogPostForm', $this->currentStep);
    }
  }

  /**
   * Save the selected type mappings, as an array keyed by source type and
   * containing the destination type (bundle).
   */
  public function contentBlogPostFormValidate(&$form_state) {
    $this->contentValues['blog'] += $form_state['values'];
    $this->contentValues['blog']['attachment_field'] = 'field_thumbnail';
  }

  /**
   * Save the selected type mappings, as an array keyed by source type and
   * containing the destination type (bundle).
   */
  public function contentPageFormValidate(&$form_state) {
    $this->contentValues['page'] += $form_state['values'];
    $this->contentValues['page']['tag_field'] = '';
    $this->contentValues['page']['category_field'] = '';
    $this->contentValues['page']['attachment_field'] = 'field_feature_image';
  }

  /**
   * Custom content types migrate form.
   *
   * @param $form_state
   * @return mixed
   * @see contentSelectForm()
   */
  protected function customContentSelectForm(&$form_state) {
    $form['overview'] = array(
      '#prefix' => '<p>',
      '#markup' => t('WordPress blogs contain custom content types. Here you may
       choose what types of Drupal nodes to create from each of those 
       content types, or omit one or both from the import entirely.'),
      '#suffix' => '</p>',
    );

    // Get destination node type(s)
    $node_types = node_type_get_types();
    $options = array('' => t('Do not import'));
    foreach ($node_types as $node_type => $info) {
      $options[$node_type] = $info->name;
    }

    // Get custom content types.
    $site_info = migrate_govcms_site_info();
    foreach ($site_info['bundles'] as $bundle => $bundle_values) {
      $form[$bundle][$bundle . '_type'] = [
        '#type' => 'select',
        '#title' => t('Import WordPress @content_type posts as', ['@content_type' => $bundle_values['name']]),
        '#options' => $options,
      ];
    }

    return $form;
  }

  /**
   * Add content migration page for each custom content type.
   *
   * @param $form_state
   */
  public function customContentSelectFormValidate(&$form_state) {
    $site_info = migrate_govcms_site_info();
    foreach ($site_info['bundles'] as $bundle => $bundle_values) {
      $this->contentValues[$bundle][$bundle . '_type'] = $form_state['values'][$bundle . '_type'];
      if ($this->contentValues[$bundle][$bundle . '_type']) {
        $this->addStep($bundle_values['name'], 'customContentPageForm', $this->currentStep, $bundle_values);
      }
    }
  }

  /**
   * Set up each custom content type migration.
   *
   * @param $form_state
   * @return mixed
   */
  protected function customContentPageForm(&$form_state) {
    $form['overview'] = array(
      '#prefix' => '<p>',
      '#markup' => t('Custom content type fields mapping.'),
      '#suffix' => '</p>',
    );

    // Get context.
    $context = $form_state['wizard']->getCurrentStep()->getContext();

    if (!empty($context['fields'])) {
      // Get bundle.
      $bundle = array_values($this->contentValues[$context['bundle_name']])[0];

      // Get Drupal content type with fields.
      $fields = ['' => t('Do not import')];
      $field_instances = field_info_instances("node", $bundle);

      foreach ($field_instances as $field_name => $values) {
        $fields[$field_name] = $values['label'];
      }

      foreach (array_values($context['fields']) as $field) {
        $form[$field] = [
          '#type' => 'select',
          '#title' => t('Import @field field into @content_type content type.', [
            '@field' => $field,
            '@content_type' => $context['bundle_name'],
          ]),
          '#options' => $fields,
        ];
      }
    }

    return $form + $this->contentForm($form_state, $context['bundle_name']);
  }

  /**
   * Save each custom content type fields mapping.
   *
   * @param $form_state
   */
  public function customContentPageFormValidate(&$form_state) {
    // Get context.
    $context = $form_state['wizard']->getCurrentStep()->getContext();
    // Save form values.
    $this->contentValues[$context['bundle_name']] += $form_state['values'];
  }

  /**
   * Review form.
   *
   * @param $form_state
   * @return mixed
   */
  public function reviewForm(&$form_state) {
    // Load default form.
    $form = parent::reviewForm($form_state);
    // Prepare custom content.
    $site_info = migrate_govcms_site_info();
    // Get vocabularies.
    $vocabularies = !empty($site_info['taxonomy']) ? $site_info['taxonomy'] : NULL;
    $bundles = !empty($site_info['bundles']) ? $site_info['bundles'] : NULL;
    $menus = !empty($site_info['menus']) ? $site_info['menus'] : NULL;
    // Init migration message.
    $message = '';

    // Add taxonomy migration.
    if (!empty($vocabularies)) {
      foreach ($vocabularies as $vocabulary => $vocabulary_values) {
        $class_name = array_values($vocabulary_values['migrate_class'])[0];
        $arguments = [
          'custom_vocabulary' => !empty($vocabulary_values['vocabulary']) ? $vocabulary_values['vocabulary'] : '',
          'source' => !empty($vocabulary_values['source_name']) ? $vocabulary_values['source_name'] : '',
        ];
        $this->addMigration($vocabulary_values['migrate_name'], $class_name, $arguments);
      }
    }

    foreach ($this->contentValues as $type => $values) {
      // Ignore types not in custom list.
      if (!isset($site_info['bundles'][$type])) {
        continue;
      }

      // Add custom migration classes.
      if ($this->contentValues[$type][$type . '_type']) {
        $class_name = array_values($bundles[$type]['migrate_class'])[0];
        // Add custom class into migration.
        $arguments = $this->contentValues[$type];
        // Load default values for drush.
        if (empty($arguments) || empty($arguments['text_format'])) {
          if (!empty($bundles[$type]['migrate_arguments'])) {
            foreach ($bundles[$type]['migrate_arguments'] as $aid => $argument) {
              $arguments[$aid] = $argument;
            }
          }
        }
        // Add dependencies.
        $arguments['dependencies'][] = 'Author';
        if (!empty($bundles[$type]['dependencies'])) {
          $arguments['dependencies'] = array_merge($arguments['dependencies'], $bundles[$type]['dependencies']);
        }
        $this->addMigration($bundles[$type]['migrate_name'], $class_name, $arguments);
        // Add into review list.
        $message .= t('<li>@type will be imported.</li>', ['@type' => $bundles[$type]['name']]);
      }
    }

    // Add menus migration.
    if (!empty($menus)) {
      foreach ($menus as $menu => $menu_values) {
        $class_name = array_values($menu_values['migrate_class'])[0];
        $arguments = [
          'menu_name' => $menu_values['menu_name'],
          'source' => $menu_values['source_name'],
        ];
        // Add dependencies.
        if ($this->contentValues['blog']['post_type']) {
          $arguments['dependencies'][] = 'BlogPost';
        }
        if ($this->contentValues['page']['page_type']) {
          $arguments['dependencies'][] = 'Page';
        }
        if (!empty($menu_values['dependencies'])) {
          $arguments['dependencies'] = array_merge($arguments['dependencies'], $menu_values['dependencies']);
        }
        $this->addMigration($menu_values['migrate_name'], $class_name, $arguments);
      }
    }

    // Display UI message.
    if (!empty($message)) {
      $form['overview'] = array(
        '#prefix' => '<div>',
        '#markup' => t('Custom content types.'),
        '#suffix' => '</div>',
      );

      $form['message_list'] = array(
        '#prefix' => '<ol>',
        '#markup' => $message,
        '#suffix' => '</ol>',
      );
    }

    return $form;
  }
}

/**
 * Class GovCMSMigrateWordPressWizardExtender.
 */
class GovCMSMigrateWordPressWizardExtender extends MigrateUIWizardExtender {
  /**
   * GovCMSMigrateWordPressWizardExtender constructor.
   * @param \GovCMSMigrateWordPressWizard $wizard
   * @param array $wizard_steps
   */
  public function __construct(\GovCMSMigrateWordPressWizard $wizard, array $wizard_steps) {
    parent::__construct($wizard, $wizard_steps);
  }

  /**
   * @param string $machine_name
   * @param string $class_name
   * @param array $arguments
   * @param \MigrateUIWizard $wizard
   * @return bool
   */
  public function addMigrationAlter($machine_name, $class_name, &$arguments, $wizard) {
    if ($machine_name == 'Attachment') {
      $arguments['dependencies'][] = 'EexOpportunities';
      $arguments['dependencies'][] = 'CaseStudies';
      $arguments['dependencies'][] = 'Events';
      $arguments['dependencies'][] = 'EexResources';
      $arguments['dependencies'][] = 'EexContact';
      $arguments['dependencies'][] = 'EexGlossary';
      $arguments['dependencies'][] = 'Programs';
      $arguments['dependencies'][] = 'EeoOpportunities';
    }

    return parent::addMigrationAlter($machine_name, $class_name, $arguments, $wizard);
  }
}
