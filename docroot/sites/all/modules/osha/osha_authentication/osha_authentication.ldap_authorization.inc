<?php
/**
 * @file
 * osha_authentication.ldap_authorization.inc
 */

/**
 * Implements hook_default_ldap_authorization().
 */
function osha_authentication_default_ldap_authorization() {
  $export = array();

  $consumer_type = new stdClass();
  $consumer_type->disabled = FALSE; /* Edit this to true to make a default consumer_type disabled initially */
  $consumer_type->api_version = 1;
  $consumer_type->sid = 'osha';
  $consumer_type->consumer_type = 'drupal_role';
  $consumer_type->consumer_module = 'ldap_authorization_drupal_role';
  $consumer_type->status = TRUE;
  $consumer_type->only_ldap_authenticated = TRUE;
  $consumer_type->use_first_attr_as_groupid = FALSE;
  $consumer_type->mappings = 'a:5:{i:0;a:6:{s:12:"user_entered";s:13:"administrator";s:4:"from";s:53:"cn=ADMIN,ou=MainSite,ou=Sites,dc=osha,dc=europa,dc=eu";s:10:"normalized";s:13:"administrator";s:10:"simplified";s:13:"administrator";s:5:"valid";b:0;s:13:"error_message";s:101:"Role <em class="placeholder">administrator</em>_name does not exist and role creation is not enabled.";}i:1;a:6:{s:12:"user_entered";s:8:"approver";s:4:"from";s:55:"cn=APPROVE,ou=MainSite,ou=Sites,dc=osha,dc=europa,dc=eu";s:10:"normalized";s:8:"approver";s:10:"simplified";s:8:"approver";s:5:"valid";b:0;s:13:"error_message";s:96:"Role <em class="placeholder">approver</em>_name does not exist and role creation is not enabled.";}i:2;a:6:{s:12:"user_entered";s:6:"editor";s:4:"from";s:52:"cn=EDIT,ou=MainSite,ou=Sites,dc=osha,dc=europa,dc=eu";s:10:"normalized";s:6:"editor";s:10:"simplified";s:6:"editor";s:5:"valid";b:0;s:13:"error_message";s:94:"Role <em class="placeholder">editor</em>_name does not exist and role creation is not enabled.";}i:3;a:6:{s:12:"user_entered";s:15:"project manager";s:4:"from";s:50:"cn=PM,ou=MainSite,ou=Sites,dc=osha,dc=europa,dc=eu";s:10:"normalized";s:15:"project manager";s:10:"simplified";s:15:"project manager";s:5:"valid";b:0;s:13:"error_message";s:103:"Role <em class="placeholder">project manager</em>_name does not exist and role creation is not enabled.";}i:4;a:6:{s:12:"user_entered";s:8:"reviewer";s:4:"from";s:54:"cn=REVIEW,ou=MainSite,ou=Sites,dc=osha,dc=europa,dc=eu";s:10:"normalized";s:8:"reviewer";s:10:"simplified";s:8:"reviewer";s:5:"valid";b:0;s:13:"error_message";s:96:"Role <em class="placeholder">reviewer</em>_name does not exist and role creation is not enabled.";}}';
  $consumer_type->use_filter = TRUE;
  $consumer_type->synch_to_ldap = FALSE;
  $consumer_type->synch_on_logon = TRUE;
  $consumer_type->revoke_ldap_provisioned = TRUE;
  $consumer_type->create_consumers = TRUE;
  $consumer_type->regrant_ldap_provisioned = TRUE;
  $export['drupal_role'] = $consumer_type;

  return $export;
}
