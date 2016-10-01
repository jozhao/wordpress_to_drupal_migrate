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
        'migrate_name' => 'TaxonomyEeoBusinessResponse',
        'migrate_class' => [
          'WordPressTaxonomyEeoBusinessResponse' => 'GovCMSMigrateWordPressTaxonomyEeoBusinessResponse',
        ],
      ],
      'cost_categories' => [
        'name' => 'Cost Categories',
        'vocabulary' => 'cost_categories',
        'source_name' => 'eex_cost',
        'migrate_name' => 'TaxonomyCostCategories',
        'migrate_class' => [
          'WordPressTaxonomyCostCategories' => 'GovCMSMigrateWordPressTaxonomyCostCategories',
        ],
      ],
      'energy_savings' => [
        'name' => 'Energy Savings',
        'vocabulary' => 'energy_savings',
        'source_name' => 'eex_energy_savings',
        'migrate_name' => 'TaxonomyEnergySavings',
        'migrate_class' => [
          'WordPressTaxonomyEnergySavings' => 'GovCMSMigrateWordPressTaxonomyEnergySavings',
        ],
      ],
      'eeo_equipment_type' => [
        'name' => 'Equipment Type',
        'vocabulary' => 'eeo_equipment_type',
        'source_name' => 'eeo_equipment_type',
        'migrate_name' => 'TaxonomyEquipmentType',
        'migrate_class' => [
          'WordPressTaxonomyEquipmentType' => 'GovCMSMigrateWordPressTaxonomyEquipmentType',
        ],
      ],
      'industry_sectors' => [
        'name' => 'Industry Sectors',
        'vocabulary' => 'industry_sectors',
        'source_name' => 'eex_industry',
        'migrate_name' => 'TaxonomyIndustrySectors',
        'migrate_class' => [
          'WordPressTaxonomyIndustrySectors' => 'GovCMSMigrateWordPressTaxonomyIndustrySectors',
        ],
      ],
      'locations' => [
        'name' => 'Locations',
        'vocabulary' => 'locations',
        'source_name' => 'eex_location',
        'migrate_name' => 'TaxonomyLocations',
        'migrate_class' => [
          'WordPressTaxonomyLocations' => 'GovCMSMigrateWordPressTaxonomyLocations',
        ],
      ],
      'eeo_opportunity_type' => [
        'name' => 'Opportunity Type',
        'vocabulary' => 'eeo_opportunity_type',
        'source_name' => 'eeo_opportunity_type',
        'migrate_name' => 'TaxonomyOpportunityType',
        'migrate_class' => [
          'WordPressTaxonomyOpportunityType' => 'GovCMSMigrateWordPressTaxonomyOpportunityType',
        ],
      ],
      'payback' => [
        'name' => 'Payback',
        'vocabulary' => 'payback',
        'source_name' => 'eex_payback',
        'migrate_name' => 'TaxonomyPayback',
        'migrate_class' => [
          'WordPressTaxonomyPayback' => 'GovCMSMigrateWordPressTaxonomyPayback',
        ],
      ],
      'eeo_sector' => [
        'name' => 'Sector',
        'vocabulary' => 'eeo_sector',
        'source_name' => 'eeo_sector',
        'migrate_name' => 'TaxonomySector',
        'migrate_class' => [
          'WordPressTaxonomySector' => 'GovCMSMigrateWordPressTaxonomySector',
        ],
      ],
      'technologies' => [
        'name' => 'Technologies',
        'vocabulary' => 'technologies',
        'source_name' => 'eex_technology',
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
        'migrate_name' => 'EexOpportunities',
        'migrate_class' => [
          'WordPressEexOpportunities' => 'GovCMSMigrateWordPressEexOpportunities',
        ],
      ],
      'case_studies' => [
        'name' => 'Case studies',
        'bundle_name' => 'case_studies',
        'source_name' => 'eex_case_study',
        'migrate_name' => 'CaseStudies',
        'migrate_class' => [
          'WordPressEexCaseStudy' => 'GovCMSMigrateWordPressEexCaseStudy',
        ],
      ],
      'events' => [
        'name' => 'Events',
        'bundle_name' => 'events',
        'source_name' => 'eex_event',
        'migrate_name' => 'Events',
        'migrate_class' => [
          'WordPressEexEvent' => 'GovCMSMigrateWordPressEexEvent',
        ],
      ],
      'additional_resources' => [
        'name' => 'Resources',
        'bundle_name' => 'additional_resources',
        'source_name' => 'eex_resources',
        'migrate_name' => 'EexResources',
        'migrate_class' => [
          'WordPressEexResources' => 'GovCMSMigrateWordPressEexResources',
        ],
      ],
      'contacts' => [
        'name' => 'Contacts',
        'bundle_name' => 'contacts',
        'source_name' => 'eex_contact',
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
        'migrate_name' => 'EexGlossary',
        'migrate_class' => [
          'WordPressGlossary' => 'GovCMSMigrateWordPressGlossary',
        ],
      ],
      'programs' => [
        'name' => 'Programs',
        'bundle_name' => 'programs',
        'source_name' => 'eex_program',
        'migrate_name' => 'Programs',
        'migrate_class' => [
          'WordPressEexProgram' => 'GovCMSMigrateWordPressEexProgram',
        ],
      ],
      'eeo_opportunities' => [
        'name' => 'EEO Opportunities',
        'bundle_name' => 'eeo_opportunities',
        'source' => 'eeo_opportunity',
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
