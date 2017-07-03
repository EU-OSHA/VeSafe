<?php
/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template in this directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['content_full']: Content within a full-width container.
 * - $page['content_bottom']: Content after the full-width container.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see bootstrap_preprocess_page()
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see bootstrap_process_page()
 * @see template_process()
 * @see html.tpl.php
 *
 * @ingroup themeable
 */
?>
<header>
  <div class="site-header">
    <div class="top-header">
      <div class="top-header-container container">
        <div class="top-header-content row">
          <div class="header-logo col-xs-12 col-sm-8 col-md-8">
            <?php if ($logo): ?>
              <a class="logo navbar-btn pull-left" href="https://osha.europa.eu/" target="_blank" title="<?php print t('EU-OSHA corporate website'); ?>">
                <img src="<?php print $logo; ?>" alt="<?php print t('EU-OSHA logo'); ?>" />
              </a>
            <?php endif; ?>
            <?php if ($eu_logo): ?>
              <img class="eu-logo" src="<?php print $eu_logo; ?>" alt="<?php print t('European Union'); ?>" />
            <?php endif; ?>
            <div class="header-sitename">
              <?php if (!empty($site_name)): ?>
                <a class="sitename" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
                <img class="img-responsive" src="/sites/all/themes/vesafe_frontend/images/icons/logo-vesafe.png" alt="Vesafe"/></a>
              <?php endif; ?>
            </div>
          </div>
          
          <div class="header-blocks col-xs-12 col-sm-3 col-md-4">
            <?php print render($page['header_block']); ?>
          </div>
        </div>
      </div>
    </div>
    <?php if (!empty($primary_nav) || !empty($secondary_nav) || !empty($page['navigation'])): ?>
      <div class="menu-header">
        <div class="navbar-header-container container">
          <div class="navbar-header-content">
            <div id="navbar" class="navbar navbar-default">
              <!-- .btn-navbar is used as the toggle for collapsed navbar content -->
              <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
                <span class="sr-only">Toggle navigation</span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
                <span class="icon-bar"></span>
              </button>
              <div class="navbar-collapse collapse">
                <nav>
                  <?php if (!empty($primary_nav)): ?>
                    <?php print render($primary_nav); ?>
                  <?php endif; ?>
                </nav>
              </div>
            </div>
          </div>
        </div>
      </div>
    <?php endif; ?>
  </div>
</header>

<div class="breadcrumb-container">
  <div class="container">
    <?php 
     if (!empty($breadcrumb)): print $breadcrumb; endif;
    ?>
  </div>
</div>

<div class="page-title-container">
  <div class="container">
    <a id="main-content"></a>
    <?php print render($title_prefix); ?>
    <?php if (!empty($title)): ?>
      <div class="page-title-wrapper">
        <div class="page-title-container">
          <h1 class="page-header"><?php print $title; ?></h1>
        </div>
      </div>
    <?php endif; ?>
    <?php print render($title_suffix); ?>
    <?php if (!empty($page['after_title'])): ?>
      <div class="after_title">
        <?php print render($page['after_title']); ?>
      </div>
    <?php endif; ?>

    <?php
     if (isset($node->field_subtitle['und'][0]['value'])){
      print('<div class="after_title">');
        print($node->field_subtitle['und'][0]['value']);
      print('</div>');
      }else if ($_SERVER['REQUEST_URI'] == '/good-practices') {
        print '<p>Browse or sort good practice examples</p>';
      }
      ?>

  </div>
</div>

<div id="gTranslate-modal">The translations of this website from the original English are made by a machine translation service developed by Google. Consequently, the quality of those translations might not be accurate in all instances. You can know more about this system on <a href="https://en.wikipedia.org/wiki/Google_Translate" target="_blank">https://en.wikipedia.org/wiki/Google_Translate</a></div>


<?php if (!empty($page['highlighted'])): ?>
<div class="jumbotron-container">
    <div class="highlighted"><?php print render($page['highlighted']); ?></div>
</div>
<?php endif; ?>

<div class="page-content-container container">
  <?php if (!empty($page['sidebar_first'])): ?>
    <aside class="col-md-3">
        <h2 class="filters open-filters hidden-md hidden-lg"><?php print t('Search filters');?></h2>
      <?php print render($page['sidebar_first']); ?>
    </aside>  <!-- /#sidebar-first -->
  <?php endif; ?>
  <div<?php print $content_column_class; ?>>
    <?php print $messages; ?>
    <?php if (!empty($tabs)): ?>
      <?php print render($tabs); ?>
    <?php endif; ?>
    <?php if (!empty($page['help'])): ?>
      <?php print render($page['help']); ?>
    <?php endif; ?>
    <?php if (!empty($action_links)): ?>
      <ul class="action-links"><?php print render($action_links); ?></ul>
    <?php endif; ?>
    <div id="skip-to-content" style="visibility: hidden; height: 0px"><a href="#skip-to-content" rel="nofollow" accesskey="S" style="visibility: hidden;"><?php print t('Skip to content'); ?></a></div>
    <?php print render($page['content']); ?>
  </div>

  <?php if (!empty($page['sidebar_second'])): ?>
    <aside class="col-sm-3">
      <?php print render($page['sidebar_second']); ?>
    </aside>  <!-- /#sidebar-second -->
  <?php endif; ?>
</div>

<?php if (!empty($page['content_full'])): ?>
  <div class="content-full-container">
    <div class="container">
      <?php print render($page['content_full']); ?>
    </div>
  </div>
<?php endif; ?>

<?php if (!empty($page['content_bottom'])): ?>
  <div class="content-bottom-container">
    <div class="container">
      <?php print render($page['content_bottom']); ?>
    </div>
  </div>
<?php endif; ?>

<div class="site-footer-container">
  <footer class="site-footer container">
    <div class="footer-copyright">
      <?php print t("© @yyyy EU-OSHA | an agency of the European Union", array('@yyyy' => date("Y"))); ?>
    </div>
    <div class="footer-blocks">
      <?php print render($page['footer']); ?>
    </div>
    <a href="#" id="scroll-top" title="<?php print t('Go to Top')?>"><span>Go to Top</span></a>
  </footer>
</div>
