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
    'fields' => [
      'field_industry_sectors' => [
        'migrate_description' => 'Industry Sectors (as nicename) assigned to this item',
      ],
      'field_technologies' => [
        'migrate_description' => 'Technologies (as nicename) assigned to this item',
      ],
      'field_locations' => [
        'migrate_description' => 'Locations (as nicename) assigned to this item',
      ],
      'field_cost_categories' => [
        'migrate_description' => 'Cost Categories (as nicename) assigned to this item',
      ],
      'field_energy_savings' => [
        'migrate_description' => 'Energy Savings (as nicename) assigned to this item',
      ],
      'field_payback' => [
        'migrate_description' => 'Payback (as nicename) assigned to this item',
      ],
      'field_dollars' => [
        'migrate_description' => '',
      ],
      'field_bolts' => [
        'migrate_description' => '',
      ],
      'field_clocks' => [
        'migrate_description' => '',
      ],
      'field_event_date' => [
        'migrate_description' => '',
      ],
      'field_event_location' => [
        'migrate_description' => '',
      ],
      'field_event_website' => [
        'migrate_description' => '',
      ],
      'field_contact_website' => [
        'migrate_description' => '',
      ],
      'field_contact_phone' => [
        'migrate_description' => '',
      ],
      'field_contact_email' => [
        'migrate_description' => '',
      ],
      'field_feature_image' => [
        'migrate_description' => '',
      ],
      'field_eeo_sector' => [
        'migrate_description' => 'EEO Sector (as nicename) assigned to this item',
      ],
      'field_eeo_equipment_type' => [
        'migrate_description' => 'EEO Equipment Type (as nicename) assigned to this item',
      ],
      'field_eeo_opportunity_type' => [
        'migrate_description' => 'EEO Opportunity Type (as nicename) assigned to this item',
      ],
      'field_eeo_business_response' => [
        'migrate_description' => 'EEO Business Response (as nicename) assigned to this item',
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
        'migrate_arguments' => [
          'path_action' => 1,
          'podcast_field' => '',
          'comments' => '',
          'attachment_field' => '',
          'text_format' => 'rich_text',
          'text_format_comment' => 'rich_text',
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
        'migrate_arguments' => [
          'path_action' => 1,
          'podcast_field' => '',
          'comments' => '',
          'attachment_field' => '',
          'text_format' => 'rich_text',
          'text_format_comment' => 'rich_text',
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
        'migrate_arguments' => [
          'path_action' => 1,
          'podcast_field' => '',
          'comments' => '',
          'attachment_field' => '',
          'text_format' => 'rich_text',
          'text_format_comment' => 'rich_text',
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
        'migrate_arguments' => [
          'path_action' => 1,
          'podcast_field' => '',
          'comments' => '',
          'attachment_field' => '',
          'text_format' => 'rich_text',
          'text_format_comment' => 'rich_text',
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
        'migrate_arguments' => [
          'path_action' => 1,
          'podcast_field' => '',
          'comments' => '',
          'attachment_field' => '',
          'text_format' => 'rich_text',
          'text_format_comment' => 'rich_text',
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
        'migrate_arguments' => [
          'path_action' => 1,
          'podcast_field' => '',
          'comments' => '',
          'attachment_field' => '',
          'text_format' => 'rich_text',
          'text_format_comment' => 'rich_text',
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
        'migrate_arguments' => [
          'path_action' => 1,
          'podcast_field' => '',
          'comments' => '',
          'attachment_field' => '',
          'text_format' => 'rich_text',
          'text_format_comment' => 'rich_text',
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
        'migrate_arguments' => [
          'path_action' => 1,
          'podcast_field' => '',
          'comments' => '',
          'attachment_field' => '',
          'text_format' => 'rich_text',
          'text_format_comment' => 'rich_text',
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
    'wxr_filename' => 'wordpress_export.xml',
    'wxr_path' => 'public://migrate',
    'do_migration' => 0,
    'default_author' => 'admin',
    'page_type' => 'page',
    'blog_post_type' => 'blog_article',
    'path_action' => 1,
    'podcast_field' => '',
    'tag_field' => 'field_tags',
    'category_field' => 'field_categories',
    'generate_redirects' => '',
    'comments' => '',
    'attachment_field' => '',
    'text_format' => 'rich_text',
    'text_format_comment' => 'rich_text',
  ];
}
