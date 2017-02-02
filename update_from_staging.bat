@echo off

rem Go to docroot/
cd docroot/

call drush sql-drop -y

rem Sync from edw staging
call drush downsync_sql @staging @self -y

rem Devify - development settings
call drush devify --yes
call drush devify_solr
rem Build the site
call drush osha_build -y
call drush devify_ldap
rem Sync files
call drush -y rsync @staging:%files @self:%files
