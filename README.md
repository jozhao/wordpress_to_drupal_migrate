# Wordpress to Drupal migrate

Migrate content from external WordPress to Drupal (7.x). 

This project provides an example on how to migrate custom content types contents, fields and vocabularies from WordPress to govCMS Drupal (7.x).

A drush command can also be used for creating the migration instance. Please check migrate_wordpress.drush.inc file for details.

##Installation
Just download and activate this module ("migrate_wordpress") as normal.

###Target Drupal/govCMS site preparation
- Set up content types, fields and vocabularies (tags, categories etc.) before migration.
- Disable "redirect" module and re-enable it after migration.
- Set custom blog migration class: ```$conf['wordpress_migrate_blog_class'] = 'GovCMSMigrateWordPress';```
- Check if private files path is set. If it does not exist, set a valid path for example ```$conf['file_private_path'] = 'sites/private/files';```

###Migrate UI
- "User" migration. Set mapping "status" to 0

###Post migration
- Set up url alias patterns
- Search configurations
- Site information configurations
- Double check sitemap.xml

##Major issues
- Menu migration (Under development)
- Custom content types contents migration (hard-code)
- Custom vocabularies (hard-code)
- Custom fields (hard-code)
