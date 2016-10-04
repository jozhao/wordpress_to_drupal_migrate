<?php

/**
 * @file
 * Migrate bundle from a WordPress blog into govCMS.
 */

/**
 * Class GovCMSMigrateWordPressBundle.
 */
class GovCMSMigrateWordPressBundle extends GovCMSMigrateWordPressItemMigration {
  /**
   * GovCMSMigrateWordPressBundle constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    parent::__construct($arguments);
  }
}

/**
 * Class GovCMSMigrateWordPressOpportunities.
 */
class GovCMSMigrateWordPressEexOpportunities extends GovCMSMigrateWordPressBundle {
  /**
   * GovCMSMigrateWordPressOpportunities constructor.
   * @param array $arguments
   *
   * Custom field example:
   * <wp:postmeta>
   *   <wp:meta_key><![CDATA[eex_opportunity_dollars]]></wp:meta_key>
   *   <wp:meta_value><![CDATA[1]]></wp:meta_value>
   * </wp:postmeta>
   */
  public function __construct(array $arguments) {
    $arguments['bundle'] = $arguments['opportunities_type'];
    $arguments['post_type'] = 'eex_opportunity';
    parent::__construct($arguments);

    // Add custom taxonomy fields.
    $this->addFieldMapping('field_industry_sectors', 'field_industry_sectors')
      ->sourceMigration('TaxonomyIndustrySectors')
      ->xpath('category[@domain="eex_industry"]/@nicename');
    $this->addFieldMapping('field_industry_sectors:source_type')
      ->defaultValue('tid');

    $this->addFieldMapping('field_technologies', 'field_technologies')
      ->sourceMigration('TaxonomyTechnologies')
      ->xpath('category[@domain="eex_technology"]/@nicename');
    $this->addFieldMapping('field_technologies:source_type')
      ->defaultValue('tid');

    $this->addFieldMapping('field_cost_categories', 'field_cost_categories')
      ->sourceMigration('TaxonomyCostCategories')
      ->xpath('category[@domain="eex_cost"]/@nicename');
    $this->addFieldMapping('field_cost_categories:source_type')
      ->defaultValue('tid');

    $this->addFieldMapping('field_energy_savings', 'field_energy_savings')
      ->sourceMigration('TaxonomyEnergySavings')
      ->xpath('category[@domain="eex_energy_savings"]/@nicename');
    $this->addFieldMapping('field_energy_savings:source_type')
      ->defaultValue('tid');

    $this->addFieldMapping('field_payback', 'field_payback')
      ->sourceMigration('TaxonomyPayback')
      ->xpath('category[@domain="eex_payback"]/@nicename');
    $this->addFieldMapping('field_payback:source_type')
      ->defaultValue('tid');

    // Add custom fields.
    $this->addFieldMapping('field_dollars', 'field_dollars')
      ->xpath('wp:postmeta/wp:meta_key[contains(text(), \'eex_opportunity_dollars\')]/following-sibling::wp:meta_value');

    $this->addFieldMapping('field_bolts', 'field_bolts')
      ->xpath('wp:postmeta/wp:meta_key[contains(text(), \'eex_opportunity_bolts\')]/following-sibling::wp:meta_value');

    $this->addFieldMapping('field_clocks', 'field_clocks')
      ->xpath('wp:postmeta/wp:meta_key[contains(text(), \'eex_opportunity_clocks\')]/following-sibling::wp:meta_value');
  }
}

/**
 * Class GovCMSMigrateWordPressEexCaseStudy.
 */
class GovCMSMigrateWordPressEexCaseStudy extends GovCMSMigrateWordPressBundle {
  /**
   * GovCMSMigrateWordPressEexCaseStudy constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['bundle'] = $arguments['case_studies_type'];
    $arguments['post_type'] = 'eex_case_study';
    parent::__construct($arguments);

    // Add custom taxonomy fields.
    $this->addFieldMapping('field_industry_sectors', 'field_industry_sectors')
      ->sourceMigration('TaxonomyIndustrySectors')
      ->xpath('category[@domain="eex_industry"]/@nicename');
    $this->addFieldMapping('field_industry_sectors:source_type')
      ->defaultValue('tid');

    $this->addFieldMapping('field_technologies', 'field_technologies')
      ->sourceMigration('TaxonomyTechnologies')
      ->xpath('category[@domain="eex_technology"]/@nicename');
    $this->addFieldMapping('field_technologies:source_type')
      ->defaultValue('tid');
  }
}

/**
 * Class GovCMSMigrateWordPressEexEvent.
 */
class GovCMSMigrateWordPressEexEvent extends GovCMSMigrateWordPressBundle {
  /**
   * GovCMSMigrateWordPressEexEvent constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['bundle'] = $arguments['events_type'];
    $arguments['post_type'] = 'eex_event';
    parent::__construct($arguments);

    // Add custom taxonomy fields.
    $this->addFieldMapping('field_industry_sectors', 'field_industry_sectors')
      ->sourceMigration('TaxonomyIndustrySectors')
      ->xpath('category[@domain="eex_industry"]/@nicename');
    $this->addFieldMapping('field_industry_sectors:source_type')
      ->defaultValue('tid');

    $this->addFieldMapping('field_technologies', 'field_technologies')
      ->sourceMigration('TaxonomyTechnologies')
      ->xpath('category[@domain="eex_technology"]/@nicename');
    $this->addFieldMapping('field_technologies:source_type')
      ->defaultValue('tid');

    // Location field mapping.
    $this->addFieldMapping('field_locations', 'field_locations')
      ->sourceMigration('TaxonomyLocations')
      ->xpath('category[@domain="eex_location"]/@nicename');
    $this->addFieldMapping('field_locations:source_type')
      ->defaultValue('tid');

    $this->addFieldMapping('field_event_date', 'field_event_date')
      ->xpath('wp:postmeta/wp:meta_key[contains(text(), \'eex_event_start_date\')]/following-sibling::wp:meta_value');
    $this->addFieldMapping('field_event_date:to')
      ->xpath('wp:postmeta/wp:meta_key[contains(text(), \'eex_event_end_date\')]/following-sibling::wp:meta_value');
    $this->addFieldMapping('field_event_location', 'field_event_location')
      ->xpath('wp:postmeta/wp:meta_key[contains(text(), \'eex_event_address\')]/following-sibling::wp:meta_value');
    $this->addFieldMapping('field_event_website', 'field_event_website')
      ->xpath('wp:postmeta/wp:meta_key[contains(text(), \'eex_event_website\')]/following-sibling::wp:meta_value');
  }
}

/**
 * Class GovCMSMigrateWordPressEexResources.
 */
class GovCMSMigrateWordPressEexResources extends GovCMSMigrateWordPressBundle {
  /**
   * GovCMSMigrateWordPressEexResources constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['bundle'] = $arguments['additional_resources_type'];
    $arguments['post_type'] = 'eex_resources';
    parent::__construct($arguments);

    // Add custom taxonomy fields.
    $this->addFieldMapping('field_industry_sectors', 'field_industry_sectors')
      ->sourceMigration('TaxonomyIndustrySectors')
      ->xpath('category[@domain="eex_industry"]/@nicename');
    $this->addFieldMapping('field_industry_sectors:source_type')
      ->defaultValue('tid');

    $this->addFieldMapping('field_technologies', 'field_technologies')
      ->sourceMigration('TaxonomyTechnologies')
      ->xpath('category[@domain="eex_technology"]/@nicename');
    $this->addFieldMapping('field_technologies:source_type')
      ->defaultValue('tid');
  }
}

/**
 * Class GovCMSMigrateWordPressEexContact.
 */
class GovCMSMigrateWordPressEexContact extends GovCMSMigrateWordPressBundle {
  /**
   * GovCMSMigrateWordPressEexContact constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['bundle'] = $arguments['contacts_type'];
    $arguments['post_type'] = 'eex_contact';
    parent::__construct($arguments);

    // Add custom taxonomy fields.
    $this->addFieldMapping('field_industry_sectors', 'field_industry_sectors')
      ->sourceMigration('TaxonomyIndustrySectors')
      ->xpath('category[@domain="eex_industry"]/@nicename');
    $this->addFieldMapping('field_industry_sectors:source_type')
      ->defaultValue('tid');

    $this->addFieldMapping('field_technologies', 'field_technologies')
      ->sourceMigration('TaxonomyTechnologies')
      ->xpath('category[@domain="eex_technology"]/@nicename');
    $this->addFieldMapping('field_technologies:source_type')
      ->defaultValue('tid');

    $this->addFieldMapping('field_contact_website', 'field_contact_website')
      ->xpath('wp:postmeta/wp:meta_key[contains(text(), \'eex_contact_website\')]/following-sibling::wp:meta_value');
    $this->addFieldMapping('field_contact_phone', 'field_contact_phone')
      ->xpath('wp:postmeta/wp:meta_key[contains(text(), \'eex_contact_phone\')]/following-sibling::wp:meta_value');
    $this->addFieldMapping('field_contact_email', 'field_contact_email')
      ->xpath('wp:postmeta/wp:meta_key[contains(text(), \'eex_contact_email\')]/following-sibling::wp:meta_value');
  }
}

/**
 * Class GovCMSMigrateWordPressGlossary.
 */
class GovCMSMigrateWordPressGlossary extends GovCMSMigrateWordPressBundle {
  /**
   * GovCMSMigrateWordPressGlossary constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['bundle'] = $arguments['glossary_type'];
    $arguments['post_type'] = 'eex_glossary_term';
    parent::__construct($arguments);
  }
}

/**
 * Class GovCMSMigrateWordPressEexProgram.
 */
class GovCMSMigrateWordPressEexProgram extends GovCMSMigrateWordPressBundle {
  /**
   * GovCMSMigrateWordPressEexProgram constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['bundle'] = $arguments['programs_type'];
    $arguments['post_type'] = 'eex_program';
    parent::__construct($arguments);

    // Add custom taxonomy fields.
    $this->addFieldMapping('field_industry_sectors', 'field_industry_sectors')
      ->sourceMigration('TaxonomyIndustrySectors')
      ->xpath('category[@domain="eex_industry"]/@nicename');
    $this->addFieldMapping('field_industry_sectors:source_type')
      ->defaultValue('tid');

    $this->addFieldMapping('field_technologies', 'field_technologies')
      ->sourceMigration('TaxonomyTechnologies')
      ->xpath('category[@domain="eex_technology"]/@nicename');
    $this->addFieldMapping('field_technologies:source_type')
      ->defaultValue('tid');

    // Location field mapping.
    $this->addFieldMapping('field_locations', 'field_locations')
      ->sourceMigration('TaxonomyLocations')
      ->xpath('category[@domain="eex_location"]/@nicename');
    $this->addFieldMapping('field_locations:source_type')
      ->defaultValue('tid');

  }
}

/**
 * Class GovCMSMigrateWordPressEeoOpportunities.
 */
class GovCMSMigrateWordPressEeoOpportunities extends GovCMSMigrateWordPressBundle {
  /**
   * GovCMSMigrateWordPressEeoOpportunities constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['bundle'] = $arguments['eeo_opportunities_type'];
    $arguments['post_type'] = 'eeo_opportunity';
    parent::__construct($arguments);

    // Add custom taxonomy fields.
    $this->addFieldMapping('field_eeo_sector', 'field_eeo_sector')
      ->sourceMigration('TaxonomySector')
      ->xpath('category[@domain="eeo_sector"]/@nicename');
    $this->addFieldMapping('field_eeo_sector:source_type')
      ->defaultValue('tid');

    // Add custom taxonomy fields.
    $this->addFieldMapping('field_eeo_equipment_type', 'field_eeo_equipment_type')
      ->sourceMigration('TaxonomyEquipmentType')
      ->xpath('category[@domain="eeo_equipment_type"]/@nicename');
    $this->addFieldMapping('field_eeo_equipment_type:source_type')
      ->defaultValue('tid');

    // Add custom taxonomy fields.
    $this->addFieldMapping('field_eeo_opportunity_type', 'field_eeo_opportunity_type')
      ->sourceMigration('TaxonomyOpportunityType')
      ->xpath('category[@domain="eeo_opportunity_type"]/@nicename');
    $this->addFieldMapping('field_eeo_opportunity_type:source_type')
      ->defaultValue('tid');

    // Add custom taxonomy fields.
    $this->addFieldMapping('field_eeo_business_response', 'field_eeo_business_response')
      ->sourceMigration('TaxonomyIndustrySectors')
      ->xpath('category[@domain="eex_industry"]/@nicename');
    $this->addFieldMapping('field_eeo_business_response:source_type')
      ->defaultValue('tid');
  }
}
