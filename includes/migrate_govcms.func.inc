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
function _migrate_govcms_get_site_info() {
  $site_info = [
    'taxonomy' => [
      'eeo_business_response' => [
        'name' => 'Business Response',
        'vocabulary' => 'eeo_business_response',
        'source_name' => 'eeo_business_response',
        'fields' => [],
        'dependencies' => [],
        'migrate_name' => 'TaxonomyEeoBusinessResponse',
        'migrate_class' => [
          'WordPressTaxonomyEeoBusinessResponse' => 'GovCMSMigrateWordPressTaxonomyEeoBusinessResponse',
        ],
      ],
      'cost_categories' => [
        'name' => 'Cost Categories',
        'vocabulary' => 'cost_categories',
        'source_name' => 'eex_cost',
        'fields' => [],
        'dependencies' => [],
        'migrate_name' => 'TaxonomyCostCategories',
        'migrate_class' => [
          'WordPressTaxonomyCostCategories' => 'GovCMSMigrateWordPressTaxonomyCostCategories',
        ],
      ],
      'energy_savings' => [
        'name' => 'Energy Savings',
        'vocabulary' => 'energy_savings',
        'source_name' => 'eex_energy_savings',
        'fields' => [],
        'dependencies' => [],
        'migrate_name' => 'TaxonomyEnergySavings',
        'migrate_class' => [
          'WordPressTaxonomyEnergySavings' => 'GovCMSMigrateWordPressTaxonomyEnergySavings',
        ],
      ],
      'eeo_equipment_type' => [
        'name' => 'Equipment Type',
        'vocabulary' => 'eeo_equipment_type',
        'source_name' => 'eeo_equipment_type',
        'fields' => [],
        'dependencies' => [],
        'migrate_name' => 'TaxonomyEquipmentType',
        'migrate_class' => [
          'WordPressTaxonomyEquipmentType' => 'GovCMSMigrateWordPressTaxonomyEquipmentType',
        ],
      ],
      'industry_sectors' => [
        'name' => 'Industry Sectors',
        'vocabulary' => 'industry_sectors',
        'source_name' => 'eex_industry',
        'fields' => [],
        'dependencies' => [],
        'migrate_name' => 'TaxonomyIndustrySectors',
        'migrate_class' => [
          'WordPressTaxonomyIndustrySectors' => 'GovCMSMigrateWordPressTaxonomyIndustrySectors',
        ],
      ],
      'locations' => [
        'name' => 'Locations',
        'vocabulary' => 'locations',
        'source_name' => 'eex_location',
        'fields' => [],
        'dependencies' => [],
        'migrate_name' => 'TaxonomyLocations',
        'migrate_class' => [
          'WordPressTaxonomyLocations' => 'GovCMSMigrateWordPressTaxonomyLocations',
        ],
      ],
      'eeo_opportunity_type' => [
        'name' => 'Opportunity Type',
        'vocabulary' => 'eeo_opportunity_type',
        'source_name' => 'eeo_opportunity_type',
        'fields' => [],
        'dependencies' => [],
        'migrate_name' => 'TaxonomyOpportunityType',
        'migrate_class' => [
          'WordPressTaxonomyOpportunityType' => 'GovCMSMigrateWordPressTaxonomyOpportunityType',
        ],
      ],
      'payback' => [
        'name' => 'Payback',
        'vocabulary' => 'payback',
        'source_name' => 'eex_payback',
        'fields' => [],
        'dependencies' => [],
        'migrate_name' => 'TaxonomyPayback',
        'migrate_class' => [
          'WordPressTaxonomyPayback' => 'GovCMSMigrateWordPressTaxonomyPayback',
        ],
      ],
      'eeo_sector' => [
        'name' => 'Sector',
        'vocabulary' => 'eeo_sector',
        'source_name' => 'eeo_sector',
        'fields' => [],
        'dependencies' => [],
        'migrate_name' => 'TaxonomySector',
        'migrate_class' => [
          'WordPressTaxonomySector' => 'GovCMSMigrateWordPressTaxonomySector',
        ],
      ],
      'technologies' => [
        'name' => 'Technologies',
        'vocabulary' => 'technologies',
        'source_name' => 'eex_technology',
        'fields' => [],
        'dependencies' => [],
        'migrate_name' => 'TaxonomyTechnologies',
        'migrate_class' => [
          'WordPressTaxonomyTechnologies' => 'GovCMSMigrateWordPressTaxonomyTechnologies',
        ],
      ],
    ],
    'bundles' => [
      'opportunities' => [
        'name' => 'EEX Opportunities',
        'bundle_name' => 'opportunities',
        'source_name' => 'eex_opportunity',
        'fields' => [
          'field_industry_sectors',
          'field_technologies',
          'field_cost_categories',
          'field_energy_savings',
          'field_payback',
          'field_dollars',
          'field_bolts',
          'field_clocks',
        ],
        'dependencies' => [
          'TaxonomyIndustrySectors',
          'TaxonomyTechnologies',
          'TaxonomyCostCategories',
          'TaxonomyEnergySavings',
          'TaxonomyPayback',
        ],
        'migrate_name' => 'EexOpportunities',
        'migrate_class' => [
          'WordPressEexOpportunities' => 'GovCMSMigrateWordPressEexOpportunities',
        ],
      ],
      'case_studies' => [
        'name' => 'Case studies',
        'bundle_name' => 'case_studies',
        'source_name' => 'eex_case_study',
        'fields' => [
          'field_industry_sectors',
          'field_technologies',
        ],
        'dependencies' => [
          'TaxonomyIndustrySectors',
          'TaxonomyTechnologies',
        ],
        'migrate_name' => 'CaseStudies',
        'migrate_class' => [
          'WordPressEexCaseStudy' => 'GovCMSMigrateWordPressEexCaseStudy',
        ],
      ],
      'events' => [
        'name' => 'Events',
        'bundle_name' => 'events',
        'source_name' => 'eex_event',
        'fields' => [
          'field_industry_sectors',
          'field_technologies',
          'field_locations',
          'field_event_date',
          'field_event_location',
          'field_event_website',
          'field_feature_image',
        ],
        'dependencies' => [
          'TaxonomyIndustrySectors',
          'TaxonomyTechnologies',
          'TaxonomyLocations',
        ],
        'migrate_name' => 'Events',
        'migrate_class' => [
          'WordPressEexEvent' => 'GovCMSMigrateWordPressEexEvent',
        ],
      ],
      'additional_resources' => [
        'name' => 'Resources',
        'bundle_name' => 'additional_resources',
        'source_name' => 'eex_resources',
        'fields' => [
          'field_industry_sectors',
          'field_technologies',
        ],
        'dependencies' => [
          'TaxonomyIndustrySectors',
          'TaxonomyTechnologies',
        ],
        'migrate_name' => 'EexResources',
        'migrate_class' => [
          'WordPressEexResources' => 'GovCMSMigrateWordPressEexResources',
        ],
      ],
      'contacts' => [
        'name' => 'Contacts',
        'bundle_name' => 'contacts',
        'source_name' => 'eex_contact',
        'fields' => [
          'field_industry_sectors',
          'field_technologies',
          'field_contact_website',
          'field_contact_phone',
          'field_contact_email',
          'field_feature_image',
        ],
        'dependencies' => [
          'TaxonomyIndustrySectors',
          'TaxonomyTechnologies',
        ],
        'migrate_name' => 'EexContact',
        'migrate_class' => [
          'WordPressEexContact' => 'GovCMSMigrateWordPressEexContact',
        ],
      ],
      'glossary' => [
        'name' => 'Glossary',
        'bundle_name' => 'glossary',
        'source_name' => 'eex_glossary',
        'fields' => [],
        'dependencies' => [],
        'migrate_name' => 'EexGlossary',
        'migrate_class' => [
          'WordPressGlossary' => 'GovCMSMigrateWordPressGlossary',
        ],
      ],
      'programs' => [
        'name' => 'Programs',
        'bundle_name' => 'programs',
        'source_name' => 'eex_program',
        'fields' => [
          'field_industry_sectors',
          'field_technologies',
          'field_locations',
        ],
        'dependencies' => [
          'TaxonomyIndustrySectors',
          'TaxonomyTechnologies',
          'TaxonomyLocations',
        ],
        'migrate_name' => 'Programs',
        'migrate_class' => [
          'WordPressEexProgram' => 'GovCMSMigrateWordPressEexProgram',
        ],
      ],
      'eeo_opportunities' => [
        'name' => 'EEO Opportunities',
        'bundle_name' => 'eeo_opportunities',
        'source_name' => 'eeo_opportunity',
        'fields' => [
          'field_eeo_sector',
          'field_eeo_equipment_type',
          'field_eeo_opportunity_type',
          'field_eeo_business_response',
        ],
        'dependencies' => [
          'TaxonomySector',
          'TaxonomyEquipmentType',
          'TaxonomyOpportunityType',
          'TaxonomyEeoBusinessResponse',
        ],
        'migrate_name' => 'EeoOpportunities',
        'migrate_class' => [
          'WordPressEeoOpportunities' => 'GovCMSMigrateWordPressEeoOpportunities',
        ],
      ],
    ],
  ];

  return array_merge(_migrate_govcms_default_site_info(), $site_info);
}

/**
 * Site migration information default values.
 *
 * @return array
 */
function _migrate_govcms_default_site_info() {
  return [
    'source_select' => '0',
    'domain' => '',
    'wxr_filename' => '',
    'wxr_path' => 'public://migrate_govcms',
    'do_migration' => 1,
    'default_author' => 'govCMS',
    'page_type' => 'page',
    'blog_post_type' => 'blog_article',
    'path_action' => 1,
    'podcast_field' => '',
    'tag_field' => 'field_tags',
    'category_field' => 'field_category',
    'generate_redirects' => '',
    'comments' => '',
    'attachment_field' => '',
    'text_format' => 'rich_text',
    'text_format_comment' => 'filtered_html',
  ];
}
