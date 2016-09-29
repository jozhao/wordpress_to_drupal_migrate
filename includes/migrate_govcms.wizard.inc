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
  protected function customContentSelectFormValidate(&$form_state) {
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

    if (!empty($context['bundle_name']['fields'])) {
      // Get bundle.
      $bundle = array_values($this->contentValues[$context['bundle_name']])[0];

      // Get Drupal content type with fields.
      $fields = ['' => t('Do not import')];
      $field_instances = field_info_instances("node", $bundle);

      foreach ($field_instances as $field_name => $values) {
        $fields[$field_name] = $values['label'];
      }

      foreach (array_values($context['bundle_name']['fields']) as $field) {
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
  protected function customContentPageFormValidate(&$form_state) {
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
    $message = '';

    foreach ($this->contentValues as $type => $values) {
      // Ignore types not in custom list.
      if (!isset($site_info['bundles'][$type])) {
        continue;
      }

      // Add custom migration classes.
      if ($this->contentValues[$type][$type . '_type']) {
        $class_name = array_values($site_info['bundles'][$type]['migrate_class'])[0];
        // Add custom class into migration.
        $this->addMigration($site_info['bundles'][$type]['migrate_name'], $class_name, $this->contentValues[$type]);
        // Add into review list.
        $message .= t('<li>@type will be imported.</li>', ['@type' => $site_info['bundles'][$type]['name']]);
      }
    }

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
}
