# Wordpress to Drupal migrate
Migrate content from external Wordpress to Drupal (7.x) govCMS. 

This project provides an example on how to migrate custom content types contents, fields and vocabularies from Wordpress to Drupal (7.x).

##Installation
Just download and activate this module ("migrate_govcms") as normal.

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