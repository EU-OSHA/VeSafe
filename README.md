VeSafe
======

##Pre-requisites

Note: setting up a LAMP stack is outside the scope of this project, it depends on the
operating system and is subject to each developer's decision. 
We are providing a general guide to setup your project.

In order to make the project work the following assumptions are made:

  * You have a working LAMP stack on your dev machine
  * You have `drush` installed and working on your computer. To install Drush I recommend to install from source repo like this:

    ```
    cd /opt
    git clone https://github.com/drush-ops/drush.git
    cd drush
    git checkout 8.1.3 (if is not working properly, try 7.3.0)
    composer install (subsequent updates to Drush requires to re-run composer install.)
    ```
   
   * Add drush executable to your $PATH (i.e. `ln -s /opt/drush/drush /usr/bin`), open a console and run `drush init` to set up .drush directory as well as aliases and shortcuts



##Project setup

### Setup database

Create a database called `osha_vesafe` in your MySQL database.
You can either use `root` with password, or setup another user and password to connect from Drupal


### Prepare drush

Assuming you open a console and `drush` works, edit `~/.drush/drushrc.php` and add this snippet:

   ```php

    <?php
    $repo_dir = drush_get_option('root') ? drush_get_option('root') : getcwd();
    $success = drush_shell_exec('cd %s && git rev-parse --show-toplevel 2> ' . drush_bit_bucket(), $repo_dir);
    if ($success) {
       $output = drush_shell_exec_output();
       $repo = $output[0];
       $options['config'] = $repo . '/drush/drushrc.php';
       $options['include'] = $repo . '/drush/commands';
       $options['alias-path'] = $repo . '/drush/aliases';
    }
   ```

### Setup Apache VH

Checkout locally the VeSafe from repository, and create a VirtualHost **in** Apache to point to the $PROJECT/docroot/ directory, for example: 

    ```
    <VirtualHost *:8080>
        ServerName vesafe.local.ro
        DocumentRoot /Users/cristiroma/Work/osha/vesafe/docroot/
        <Directory /Users/cristiroma/Work/osha/vesafe/docroot/>
            AllowOverride All
            Order allow,deny
            Allow from all
            # Required for httpd 2.4
            Require all granted
        </Directory>
    </VirtualHost>
    ```

Then restart apache to pick the new VH, then check http://vesafe.local.ro works. At this stage Drupal should ask to make a new installation. **DON'T! MOVE ON!**

Notes:  
* You need to add the domain  (i.e. `vesafe.local.ro`) to your local `hosts` file (`/etc/hosts` or `C:\Windows\System32\drivers\etc\hosts`) like this
  
  ``
  127.0.0.1  vesafe.local.ro
  ``

* You can checkout your project locally using git:

```
git clone git@github.com:EU-OSHA/VeSafe.git
git checkout develop
```

Later, please work on your own branch! Branching and development is described in detail here: https://github.com/EU-OSHA/osha-website/wiki


### Project setup 

* Copy `conf/config.template.json` to `conf/config.json` and customize to suit your environment, for example:

    ```json
    {
        "db" : {
            "host": "localhost",
            "username" : "root",
            "password" : "root",
            "port": 3306,
            "database" : "osha_vesafe"
        },
        "admin" : {
            "username": "vesafe_admin",
            "password": "password",
            "email": "account@example.com"
        },
        "uri": "http://vesafe.local.ro",
        "solr_server": {
            "name": "Apache Solr server",
            "enabled": 1,
            "description": "",
            "scheme": "http",
            "host": "localhost",
            "port": 8080,
            "path": "/solr",
            "http_user": "",
            "http_password": "",
            "excerpt": 1,
            "retrieve_data": 1,
            "highlight_data": 1,
            "skip_schema_check": null,
            "solr_version": "",
            "http_method": "AUTO",
            "apachesolr_read_only": null,
            "apachesolr_direct_commit": 1,
            "apachesolr_soft_commit": 1
        },
        "variables": {
            "site_mail": "your.email@domain.org",
            "site_name": "VeSafe",
            "osha_data_dir": "/home/osha/data",
            "file_temporary_path": "/tmp"
        }
    }
    ```

* Create file `drush/aliases/aliases.local.php` and define your drush staging alias, like this:

  Note: replace `yourname` below with your username, i.e. `cristiroma`, `john` whatever.

  ```php
  $aliases['staging'] = array(
    'uri' => 'http://vesafe.edw.ro',
    'db-allows-remote' => TRUE,
    'remote-host' => '5.9.54.24',
    'remote-user' => 'php',
    'root' => '/var/www/html/osha-vesafe/docroot',
    'path-aliases' => array(
      '%files' => 'sites/default/files',
    ),
    'command-specific' => array(
      'sql-sync' => array(
        'simulate' => '1',
        'source-dump' => '/tmp/osha-vesafe-dump-yourname.sql',
      ),
    ),
  );
  ```
  
  Note: After this if you go in the `docroot` and run `drush` in console you should see something like this:

  ```
  cristiroma ~/Work/osha/vesafe/docroot $ drush sa
  @none
  @osha
  @osha.staging
  @self
  default
  ```

  If you run `drush @osha.staging st` you connect to staging instance (vesafe.edw.ro) via SSH and check it's status:

  ```
  cristiroma ~/Work/osha/vesafe/docroot $ drush @osha.staging st
   Drupal version                  :  7.X
   Site URI                        :  http://vesafe.edw.ro
   Database driver                 :  mysql
   Database hostname               :  localhost
   Database port                   :  3306
   Database username               :  osha_vesafe
   Database name                   :  osha_vesafe
   Drupal bootstrap                :  Successful
   Drupal user                     :
   Default theme                   :  vesafe_frontend
   Administration theme            :  osha_admin
   PHP executable                  :  /usr/bin/php
   PHP configuration               :  /etc/php.ini
   PHP OS                          :  Linux
   Drush script                    :  /opt/drush/drush.php
   Drush version                   :  8.x.x
   Drush temp directory            :  /tmp
   Drush configuration             :  /var/www/html/osha-vesafe/drush/drushrc.php /home/php/.drush/drushrc.php
   Drush alias files               :  /var/www/html/osha-vesafe/drush/aliases/osha.aliases.drushrc.php /var/www/html/osha-vesafe/docroot/../drush/aliases/osha.aliases.drushrc.php 
   Install profile                 :  vesafe_profile
   Drupal root                     :  /var/www/html/osha-vesafe/docroot
   Drupal Settings File            :  sites/default/settings.php
   Site path                       :  sites/default
   File directory path             :  sites/default/files
   Temporary file directory path   :  /tmp
  ```


* Create `docroot/sites/default/settings.local.php` file, example:

  Note: Later you can add more settings here, custom to your installation, like `memcached`, `varnish` etc.

  ```php
  <?php
  $databases = array (
    'default' =>
      array (
        'default' =>
          array (
            'database' => 'osha_vesafe',
            'username' => 'root',
            'password' => 'root',
            'host' => 'localhost',
            'port' => '',
            'driver' => 'mysql',
            'prefix' => '',
          ),
      ),
  );
  ```

* Run `install_from_staging.sh`

*Warning*: Running `install_from_staging.sh` on an existing instance *will destroy* that instance (database) loosing all db changes (i.e. panels, blocks etc.)!

The console output should look like this:

```

cristiroma ~/Work/osha/vesafe $ ./install_from_staging.sh 
Command variable-get needs a higher bootstrap level to run - you will need to invoke drush from a more functional Drupal environment to run this command.              [error]
The drush command 'vget environment' could not be executed.                                                                                                            [error]
Do you really want to drop all tables in the database osha_vesafe? (y/n): y
SQL Sync running... NOTE: if you do not have ssh passwordless logins setup, you may be asked for your password multiple times.You will destroy data in osha_vesafe and replace with data from 5.9.54.24/osha_vesafe.
Do you really want to continue? (y/n): y
Starting to dump database on Source.                                                                                                                                   [ok]
Database dump saved to /tmp/osha-vesafe-dump-cristiroma.sql.gz                                                                                                         [success]
You will delete files in /tmp/target-dump.sql.gz and replace with data from php@5.9.54.24:/tmp/osha-vesafe-dump-cristiroma.sql.gz
Do you really want to continue? (y/n): y
Copying dump file from Source to Destination.                                                                                                                          [ok]
Starting to import dump file onto Destination database.                                                                                                                [ok]

environment was set to "local".                                                                                                                                        [success]

The following operations will be done on the target database:
 * Reset passwords and email addresses in users table
 * Truncate Drupal's sessions table
 * Delete all data submitted to webforms (depending on the site config, may contain sensitive data).

Do you really want to sanitize the current database? (y/n): y
Devified!                                                                                                                                                              [success]
Devify Solr ServerNo Solr Server (machine name: solr_server) found in databaseNo database updates required                                                                                                                                           [success]
Devify Solr ServerLdap read devified!                                                                                                                                                    [success]
Ldap write devified!                                                                                                                                                   [success]
cristiroma ~/Work/osha/vesafe $ 

```

**Note:** 
If the script fails, you can look into the script and try to execute commands one-by-one using `drush -v -d` to debug.

##Repository Layout##
Breakdown for what each directory/file is used for. See also readme inside directories.

* [conf](https://github.com/EU-OSHA/osha-website/tree/master/conf)
 * Project specific configuration files
* [docroot](https://github.com/EU-OSHA/osha-website/tree/master/docroot)
 * Drupal root directory
* [drush](https://github.com/EU-OSHA/osha-website/tree/master/drush)
 * Contains project specific drush commands, aliases, and configurations.
* [results](https://github.com/EU-OSHA/osha-website/tree/master/results)
 * This directory is just used to export test results to. A good example of this
   is when running drush test-run with the --xml option. You can export the xml
   to this directory for parsing by external tools.
* [scripts](https://github.com/EU-OSHA/osha-website/tree/master/scripts)
 * A directory for project-specific scripts.
* [test](https://github.com/EU-OSHA/osha-website/tree/master/tests)
 * A directory for external tests. This is great for non drupal specific tests
 such as selenium, qunit, casperjs.
* [.gitignore](https://github.com/EU-OSHA/osha-website/blob/master/.gitignore)
 * Contains the a list of the most common excluded files.

##Branches##

This repo branching model follows the article ["A successful Git branching model"](http://nvie.com/posts/a-successful-git-branching-model)

Summary:

* _master_ - The production branch, updated with each release.
* _develop_ - Main development branch. Tests are performed on this branch
* _release-_* - Release branches

-- edw
