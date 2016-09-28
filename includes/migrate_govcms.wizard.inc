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
    parent::__construct();
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
   * Review form alter.
   * @param $form
   * @param $form_state
   */
  public function reviewFormAlter(&$form, &$form_state) {

  }
}
