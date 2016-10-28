<?php

/**
 * @file
 * Migrate bundle from a WordPress blog into govCMS.
 */

/**
 * Class GovCMSMigrateWordPressBundle.
 */
class GovCMSMigrateWordPressBundle extends MigrateWordPressBundle {
  /**
   * Prepare source row.
   * @param \stdClass $row
   * @return bool|string
   */
  public function prepareRow($row) {
    return parent::prepareRow($row);
  }
}

/**
 * Class GovCMSMigrateWordPressPage.
 */
class GovCMSMigrateWordPressPage extends GovCMSMigrateWordPressBundle {
  /**
   * GovCMSMigrateWordPressPage constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['bundle'] = $arguments['page_type'];
    $arguments['post_type'] = 'page';
    parent::__construct($arguments);
  }

  /**
   * Prepare the row.
   * @param \stdClass $row
   * @return bool|string
   */
  public function prepareRow($row) {
    // Always include this fragment at the beginning of every prepareRow()
    // implementation, so parent classes can ignore rows.
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    // Fetch content from WordPress directly.
    try {
      $wp_link = (string) $row->xml->link;;
      $wp_link = str_replace('http://', 'https://', $wp_link);

      $wp_post = htmlqp($wp_link, 'div.entry-content');
      $row->content = $wp_post->html();
    } catch (Exception $exception) {
      return FALSE;
    }

    return TRUE;
  }
}

/**
 * Class GovCMSMigrateWordPressBlogEntry
 */
class GovCMSMigrateWordPressBlogEntry extends GovCMSMigrateWordPressItemMigration {
  /**
   * GovCMSMigrateWordPressBlogEntry constructor.
   * @param array $arguments
   */
  public function __construct(array $arguments) {
    $arguments['bundle'] = $arguments['post_type'];
    $arguments['post_type'] = 'post';
    parent::__construct($arguments);

    // Add custom taxonomy fields.
    $this->addFieldMapping('field_industry_sectors', 'field_industry_sectors')
      ->xpath('category[@domain="eex_industry"]');

    $this->addFieldMapping('field_technologies', 'field_technologies')
      ->xpath('category[@domain="eex_technology"]');
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
      ->xpath('category[@domain="eex_industry"]');

    $this->addFieldMapping('field_technologies', 'field_technologies')
      ->xpath('category[@domain="eex_technology"]');

    $this->addFieldMapping('field_cost_categories', 'field_cost_categories')
      ->xpath('category[@domain="eex_cost"]');

    $this->addFieldMapping('field_energy_savings', 'field_energy_savings')
      ->xpath('category[@domain="eex_energy_savings"]');

    $this->addFieldMapping('field_payback', 'field_payback')
      ->xpath('category[@domain="eex_payback"]');

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
      ->xpath('category[@domain="eex_industry"]');

    $this->addFieldMapping('field_technologies', 'field_technologies')
      ->xpath('category[@domain="eex_technology"]');

    // Add custom resource fields.
    $this->addFieldMapping('field_resource_source', 'field_resource_source')
      ->xpath('wp:postmeta/wp:meta_key[contains(text(), \'_eex_case_study_source\')]/following-sibling::wp:meta_value');
    $this->addFieldMapping('field_resource_year', 'field_resource_year')
      ->xpath('wp:postmeta/wp:meta_key[contains(text(), \'_eex_case_study_year\')]/following-sibling::wp:meta_value');
    $this->addFieldMapping('field_link_to_default_file', 'field_link_to_default_file')
      ->xpath('wp:postmeta/wp:meta_key[contains(text(), \'_eex_case_study_link_to_file\')]/following-sibling::wp:meta_value')
      ->defaultValue('1');
  }

  /**
   * Complete function.
   * @param \stdClass $node
   * @param \stdClass $row
   */
  public function complete(stdClass $node, stdClass $row) {
    parent::complete($node, $row);

    // Paragraphs migration.
    if (module_exists('paragraphs')) {
      // Paragraphs field.
      if (!isset($node->field_case_studies)) {

        $file_0 = $this->xpathValue($row->xml->xpath('wp:postmeta/wp:meta_key[contains(text(), \'_file_0\')]/following-sibling::wp:meta_value'));
        if (!empty($file_0)&& ($file_0 !== ',,,')) {
          $paragraph = new ParagraphsItemEntity(array(
            'field_name' => 'field_case_studies',
            'bundle' => 'pb_resources_listing',
          ));
          $paragraph->is_new = TRUE;
          $paragraph->setHostEntity('node', $node);

          $resource = explode(',', $file_0);

          $paragraph->field_resource_url[LANGUAGE_NONE][0]['url'] = $resource[0];
          $paragraph->field_resource_size[LANGUAGE_NONE][0]['value'] = $resource[1];
          $paragraph->field_resource_type[LANGUAGE_NONE][0]['value'] = $resource[2];
          $paragraph->field_resource_external[LANGUAGE_NONE][0]['value'] = $resource[3] == 'yes' ? 1 : 0;

          $paragraph->save();
        }

        $file_1 = $this->xpathValue($row->xml->xpath('wp:postmeta/wp:meta_key[contains(text(), \'_file_1\')]/following-sibling::wp:meta_value'));
        if (!empty($file_1) && ($file_1 !== ',,,')) {
          $paragraph = new ParagraphsItemEntity(array(
            'field_name' => 'field_case_studies',
            'bundle' => 'pb_resources_listing',
          ));
          $paragraph->is_new = TRUE;
          $paragraph->setHostEntity('node', $node);

          $resource = explode(',', $file_1);

          $paragraph->field_resource_url[LANGUAGE_NONE][0]['url'] = $resource[0];
          $paragraph->field_resource_size[LANGUAGE_NONE][0]['value'] = $resource[1];
          $paragraph->field_resource_type[LANGUAGE_NONE][0]['value'] = $resource[2];
          $paragraph->field_resource_external[LANGUAGE_NONE][0]['value'] = $resource[3] == 'yes' ? 1 : 0;

          $paragraph->save();
        }

        $file_2 = $this->xpathValue($row->xml->xpath('wp:postmeta/wp:meta_key[contains(text(), \'_file_2\')]/following-sibling::wp:meta_value'));
        if (!empty($file_2) && ($file_2 !== ',,,')) {
          $paragraph = new ParagraphsItemEntity(array(
            'field_name' => 'field_case_studies',
            'bundle' => 'pb_resources_listing',
          ));
          $paragraph->is_new = TRUE;
          $paragraph->setHostEntity('node', $node);

          $resource = explode(',', $file_2);

          $paragraph->field_resource_url[LANGUAGE_NONE][0]['url'] = $resource[0];
          $paragraph->field_resource_size[LANGUAGE_NONE][0]['value'] = $resource[1];
          $paragraph->field_resource_type[LANGUAGE_NONE][0]['value'] = $resource[2];
          $paragraph->field_resource_external[LANGUAGE_NONE][0]['value'] = $resource[3] == 'yes' ? 1 : 0;

          $paragraph->save();
        }
      }
    }
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
      ->xpath('category[@domain="eex_industry"]');

    $this->addFieldMapping('field_technologies', 'field_technologies')
      ->xpath('category[@domain="eex_technology"]');

    // Location field mapping.
    $this->addFieldMapping('field_locations', 'field_locations')
      ->xpath('category[@domain="eex_location"]');

    $this->addFieldMapping('field_event_date', 'field_event_date')
      ->xpath('wp:postmeta/wp:meta_key[contains(text(), \'eex_event_start_date\')]/following-sibling::wp:meta_value');
    $this->addFieldMapping('field_event_date:to', 'field_event_date_to')
      ->xpath('wp:postmeta/wp:meta_key[contains(text(), \'eex_event_end_date\')]/following-sibling::wp:meta_value');
    $this->addFieldMapping('field_event_location', 'field_event_location')
      ->xpath('wp:postmeta/wp:meta_key[contains(text(), \'eex_event_address\') or contains(text(), \'eex_event_location\')]/following-sibling::wp:meta_value');
    $this->addFieldMapping('field_event_website', 'field_event_website')
      ->xpath('wp:postmeta/wp:meta_key[contains(text(), \'eex_event_website\')]/following-sibling::wp:meta_value');
  }

  /**
   * @param \stdClass $row
   * @return bool|string
   */
  public function prepareRow($row) {
    // Always include this fragment at the beginning of every prepareRow()
    // implementation, so parent classes can ignore rows.
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    $row->field_event_date = drupal_json_encode([
      'from' => $this->xpathValue($row->xml->xpath('wp:postmeta/wp:meta_key[contains(text(), \'eex_event_start_date\')]/following-sibling::wp:meta_value')),
      'to' => $this->xpathValue($row->xml->xpath('wp:postmeta/wp:meta_key[contains(text(), \'eex_event_end_date\')]/following-sibling::wp:meta_value')),
    ]);

    return TRUE;
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
      ->xpath('category[@domain="eex_industry"]');

    $this->addFieldMapping('field_technologies', 'field_technologies')
      ->xpath('category[@domain="eex_technology"]');

    // Add custom resource fields.
    $this->addFieldMapping('field_resource_source', 'field_resource_source')
      ->xpath('wp:postmeta/wp:meta_key[contains(text(), \'_eex_resource_source\')]/following-sibling::wp:meta_value');
    $this->addFieldMapping('field_resource_year', 'field_resource_year')
      ->xpath('wp:postmeta/wp:meta_key[contains(text(), \'_eex_resource_year\')]/following-sibling::wp:meta_value');
    $this->addFieldMapping('field_link_to_default_file', 'field_link_to_default_file')
      ->xpath('wp:postmeta/wp:meta_key[contains(text(), \'_eex_resource_link_to_file\')]/following-sibling::wp:meta_value')
      ->defaultValue('1');
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
      ->xpath('category[@domain="eex_industry"]');

    $this->addFieldMapping('field_technologies', 'field_technologies')
      ->xpath('category[@domain="eex_technology"]');

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
      ->xpath('category[@domain="eex_industry"]');

    $this->addFieldMapping('field_technologies', 'field_technologies')
      ->xpath('category[@domain="eex_technology"]');

    // Location field mapping.
    $this->addFieldMapping('field_locations', 'field_locations')
      ->xpath('category[@domain="eex_location"]');
  }

  /**
   * @param \stdClass $row
   * @return bool
   */
  public function prepareRow($row) {
    // Always include this fragment at the beginning of every prepareRow()
    // implementation, so parent classes can ignore rows.
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    return TRUE;
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
      ->xpath('category[@domain="eeo_sector"]')
      ->callbacks('html_entity_decode');

    // Add custom taxonomy fields.
    $this->addFieldMapping('field_eeo_equipment_type', 'field_eeo_equipment_type')
      ->xpath('category[@domain="eeo_equipment_type"]');

    // Add custom taxonomy fields.
    $this->addFieldMapping('field_eeo_opportunity_type', 'field_eeo_opportunity_type')
      ->xpath('category[@domain="eeo_opportunity_type"]');

    // Add custom taxonomy fields.
    $this->addFieldMapping('field_eeo_business_response', 'field_eeo_business_response')
      ->xpath('category[@domain="eex_industry"]');
  }
}
