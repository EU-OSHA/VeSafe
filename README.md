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

### Prepare drush 

Edit `~/.drush/drushrc.php` and add this snippet:

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


## Setup database

Create a database called `osha_vesafe` in your MySQL database.
You can either use `root` with password, or setup another user and password to connect from Drupal

## Setup Apache VH

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

## Project setup 

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

*Warning*: Running install.sh on an existing instance *will destroy* that instance (database) loosing all customisations



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
