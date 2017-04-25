<?php

/**
 * Given an array of Drupal role names, try to load them and return unique list
 * that can be assigned to user.
 *
 * @param array $proposed_roles
 *  List of roles names that to assign.
 *
 * @return array
 *   Array of array($rid => role_name)
 */
function osha_authentication_extract_user_roles($proposed_roles) {
  $ret = array();
  $roles_names = array('authenticated user');
  $roles_names = array_merge($roles_names, array_values($proposed_roles));
  // Load the actual roles from DB
  foreach($roles_names as $role_name) {
    if ($r = user_role_load_by_name($role_name)) {
      $ret[$r->rid] = $role_name;
    }
    else {
      // @todo:
    }
  }
  return $ret;
}

/**
 * Extract a single role from the DN of a group.
 *
 * @param string $group_dn
 *
 * @return array
 *  array with role, language. May be null
 */
function osha_authentication_get_role_from_dn($group_dn) {
  $role = NULL;
  $language = NULL;
  if ($group_dn == 'cn=ADMIN,ou=VESAFE,ou=Sites,dc=osha,dc=europa,dc=eu') {
    $role = VeSafeWorkflow::ROLE_ADMINISTRATOR;
  }
  else if ($group_dn == 'cn=APPROVE,ou=VESAFE,ou=Sites,dc=osha,dc=europa,dc=eu') {
    $role = VeSafeWorkflow::ROLE_APPROVER;
  }
  else if ($group_dn == 'cn=PM,ou=VESAFE,ou=Sites,dc=osha,dc=europa,dc=eu') {
    $role = VeSafeWorkflow::ROLE_PROJECT_MANAGER;
  }
  else if ($group_dn == 'cn=REVIEW,ou=VESAFE,ou=Sites,dc=osha,dc=europa,dc=eu') {
    $role = VeSafeWorkflow::ROLE_REVIEWER;
  }
  else if ($group_dn == 'cn=EDIT,ou=VESAFE,ou=Sites,dc=osha,dc=europa,dc=eu') {
    $role = VeSafeWorkflow::ROLE_EDITOR;
  }
  // Report unknown values
  else {
    watchdog('osha_authentication', 'Unknown DN: !dn', array('!dn' => $group_dn), WATCHDOG_WARNING);
  }
  return array($role, $language);
}


function osha_authentication_ldap_fetch_user_groups($username, $ldap_server) {
  $ret = array();
  /** @var LDAPServer $ldap_server */
  $ldap_groups = $ldap_server->search('ou=VESAFE,ou=Sites,dc=osha,dc=europa,dc=eu', 'memberUid=' . $username);
  if (!$ldap_groups) {
    return $ret;
  }
  unset($ldap_groups['count']);
  foreach($ldap_groups as $group) {
    $ret[$group['dn']] = $group['dn'];
  }
  return $ret;
}

/**
 * Check Drupal users no longer in LDAP and block them.
 *
 * @param $ldap_server
 */
function osha_authentication_block_disabled_ldap_accounts($ldap_server, $ldap_accounts = NULL) {
  if (!$ldap_accounts) {
    $ldap_accounts = osha_authentication_ldap_get_site_users($ldap_server);
  }
  try {
    $local_accounts = entity_load('user');
    foreach ($local_accounts as $account) {
      // Do not touch 'admin' accounts NOT coming from LDAP
      if ($account->uid > 1 && !empty($account->data['ldap_user']['init']['sid'])) {
        // Block LDAP accounts no longer member of any group from ou=MainSite,ou=Sites,dc=osha,dc=europa,dc=eu
        // Unblock users which are added again
        $status = array_key_exists($account->name, $ldap_accounts) ? 1 : 0;
        if (!$status) {
          // Remove user roles
          db_delete('users_roles')->condition('uid', $account->uid)->execute();
          if ($account->status == 1) {
            watchdog('osha_authentication', 'Blocking inactive account (no longer in LDAP/part of any group): !user', array('!user' => $account->name), WATCHDOG_WARNING);
          }
        }
        else {
          if ($account->status == 0) {
            watchdog('osha_authentication', 'Reactivating acount: !user', array('!user' => $account->name), WATCHDOG_WARNING);
          }
        }
        $account->status = $status;
        // Set user status
        db_update('users')->fields(array(
          'status' => $status
        ))->condition('uid', $account->uid)->execute();
        // user_save($account, array('roles' => array()));
      }
    }
    return;
  }
  catch(Exception $e) {
    //@todo: Handle exception
  }
}

/**
 * Querying all cn=MainSite groups and extract unique memberUid to build the
 * list of website users
 *
 * @param stdClass $ldap_server
 *   LDAP data provider
 *
 * @return Array of user objects (name, mail) found in the groups keyed by uid
 */
function osha_authentication_ldap_get_site_users($ldap_server) {
  $ret = array();
  /** @var LDAPServer $ldap_server */
  $ldap_groups = $ldap_server->search('ou=VESAFE,ou=Sites,dc=osha,dc=europa,dc=eu', 'cn=*', array('dn', 'memberUid', 'cn'));
  if (!$ldap_groups) {
    return $ret;
  }
  unset($ldap_groups['count']);
  $uids = array();
  foreach($ldap_groups as $group) {
    if (isset($group['memberuid']) && $group['memberuid']['count'] > 0) {
      unset($group['memberuid']['count']);
      $uids = array_merge($uids, $group['memberuid']);
    }
  }
  $uids = array_unique($uids);
  foreach($uids as $uid) {
    if ($ldap_account = $ldap_server->search('ou=people,dc=osha,dc=europa,dc=eu', 'uid=' . $uid, array('dn', 'mail'))) {
      if (empty($ldap_account[0]['mail'][0])) {
        $mail = $uid . '@fake-domain.com';
      }
      else {
        $mail = $ldap_account[0]['mail'][0];
      }
      if (empty($ldap_account[0])) {
        watchdog('osha_authentication', 'Cannot find user with uid=<em>!uid</em>, but still present in memberUid property', array(
          '!uid' => $uid
        ), WATCHDOG_WARNING);
        continue;
      }
      $dn = $ldap_account[0]['dn'];
      $user = (object) array(
        'dn' => $dn,
        'name' => $uid,
        'mail' => $mail,
      );
      $ret[$uid] = $user;
    }
  }
  return $ret;
}

/**
 * Fetch LDAP accounts and membership and synchronize with Drupal accounts.
 * @param stdClass $ldap_server
 *   Server to query
 */
function osha_authentication_ldap_sync($ldap_server) {
  // Handle LDAP accounts synchronization
  $accounts = osha_authentication_ldap_get_site_users($ldap_server);

  // Block disabled accounts
  osha_authentication_block_disabled_ldap_accounts($ldap_server, $accounts);

  foreach($accounts as $username => $ldap_account) {
    if (!$account = user_load_by_name($username)) {
      // Set a random password
      $ldap_account->password = user_password(32);
      $ldap_account->status = 1;
      $ldap_account->timezone = NULL;
      if ($account = user_save($ldap_account)) {
        watchdog('osha_authentication', 'Creating Drupal account <em>!uid</em> from LDAP dn: !dn', array(
          '!dn' => $ldap_account->dn,
          '!uid' => $username
        ), WATCHDOG_WARNING);
      }
      else {
        watchdog('osha_authentication', 'Failed to save new Drupal account <em>!uid</em> from LDAP dn: !dn', array(
          '!dn' => $ldap_account->dn,
          '!uid' => $username
        ), WATCHDOG_ERROR);
      }
    }
    if ($account && $account->status == 1) {
      $edit = array();
      // Simulate login to update user data
      user_module_invoke('login', $edit, $account);
    }
  }
}
