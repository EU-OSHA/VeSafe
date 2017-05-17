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
<div>
</div>

<div class="back-arrow-container container">
    <div class="back-arrow-wrapper">
        <a href="/themes" class="back-arrow">Return to list</a>
    </div>
</div>
<!--page image block-->
<div class="jumbotron-container">
    <div class="page-image-wrapper">
        <img class="img-responsive"
             alt="<?php print $node->field_image[LANGUAGE_NONE][0]['alt'] ?>"
             title="<?php print $node->field_image[LANGUAGE_NONE][0]['title'] ?>"
             src="<?php echo image_style_url('generic_background', $node->field_image[LANGUAGE_NONE][0]['uri'])?>"/>
    </div>
</div>
<!--general content-->
<div class="page-content-container-inside container">
    <div class="key-articles-menu-container col-md-3 col-sm-5">
        <h2 class="key-menu-arrow-open hidden-md hidden-lg"><?php print t('Index');?></h2>
        <ul>
            <li><a href="#introduction"
                   class="key-introduction"><?php print t('Introduction')?></a></li>
            <li>
                <span class="key-safety key-menu-arrow-open">General safety issues</span>
                <ul><?php
                  if (isset($node->field_ka_general_safety_issues[LANGUAGE_NONE])) {
                    $gsi = $node->field_ka_general_safety_issues[LANGUAGE_NONE];
                    foreach ($gsi as $issue) {
                      $title = $issue["entity"]->title;
                      $titleLink = strtolower($issue["entity"]->title);
                      $titleLink = str_replace(' ', '-', $titleLink);
                      $titleLink = str_replace(',', '', $titleLink);
                      $titleLink = str_replace('.', '', $titleLink);
                      $titleLink = str_replace('(', '', $titleLink);
                      $titleLink = str_replace(')', '', $titleLink);

                      print '<li><a href="#' . $titleLink . '">' . $title . '</a></li>';
                    }
                  }
                  ?></ul>
            </li>
            <li>
                <span class="key-general-risk key-menu-arrow-open"><?php print t('General risk factors');?></span>
                <ul><?php
                  if (isset($node->field_ka_general_risk_factors[LANGUAGE_NONE])) {
                    $grf = $node->field_ka_general_risk_factors[LANGUAGE_NONE];
                    foreach ($grf as $issue) {
                      $title = $issue["entity"]->title;
                      $titleLink = strtolower($issue["entity"]->title);
                      $titleLink = str_replace(' ', '-', $titleLink);
                      $titleLink = str_replace(',', '', $titleLink);
                      $titleLink = str_replace('.', '', $titleLink);
                      $titleLink = str_replace('(', '', $titleLink);
                      $titleLink = str_replace(')', '', $titleLink);

                      print '<li><a href="#' . $titleLink . '">' . $title . '</a></li>';
                    }
                  }
                  ?></ul>
            </li>
            <li>
                <span class="key-specific-risk key-menu-arrow-open"><?php print t('Specific risk factors');?></span>
                <ul><?php
                  if (isset($node->field_ka_specific_risk_factors[LANGUAGE_NONE])) {
                    $srf = $node->field_ka_specific_risk_factors[LANGUAGE_NONE];
                    foreach ($srf as $issue) {
                      $title = $issue["entity"]->title;
                      $titleLink = strtolower($issue["entity"]->title);
                      $titleLink = str_replace(' ', '-', $titleLink);
                      $titleLink = str_replace(',', '', $titleLink);
                      $titleLink = str_replace('.', '', $titleLink);
                      $titleLink = str_replace('(', '', $titleLink);
                      $titleLink = str_replace(')', '', $titleLink);

                      print '<li><a href="#' . $titleLink . '">' . $title . '</a></li>';
                    }
                  }
                  ?></ul>
            </li>
        </ul>
    </div>
    <div class="key-article-content col-md-9 col-sm-12">
        <div id="introduction">
            <div class="key-article-text">
                <h2 class="titulos-key-articles"><?php print t('Introduction');?></h2>
                <div class="body-key-article">
                  <?php
                  print (render($node->body[LANGUAGE_NONE]["0"]["value"]));
                  ?>
                </div>
            </div>
            <div class="key-article-next-prev-buttons">

              <?php
              $previousHref = '#introduction';
              $previousTitle = t('Introduction');
              $nextHref = '';

              // General Safety Issues.
              if (isset($node->field_ka_general_safety_issues[LANGUAGE_NONE])) {
                $gsi = $node->field_ka_general_safety_issues[LANGUAGE_NONE];
                foreach ($gsi as $issue) {
                  // Get the title of the current Issue.
                  $title = $issue["entity"]->title;
                  $titleLink = strtolower($issue["entity"]->title);
                  $titleLink = str_replace(' ', '-', $titleLink);
                  $titleLink = str_replace(',', '', $titleLink);
                  $titleLink = str_replace('.', '', $titleLink);
                  $titleLink = str_replace('(', '', $titleLink);
                  $titleLink = str_replace(')', '', $titleLink);
                  $nextHref = '#' . $titleLink;

                  // Print Next Button From Previous div.
                  print '<span class="next-button"><a href="' . $nextHref . '" class="nexting-button">' . $title . '</a></span>';
                  print '</div>';
                  // Next-Previous Button div closure.
                  print '</div>';
                  // Key Article Theme div closure.
                  print '<div id="' . $titleLink . '">';
                  // Key Article Theme div open.
                  print '<div  class="key-article-text">';
                  print '<h2 class="titulos-key-articles">' . $title . '</h2>';
                  print '<div class="body-key-article">';
                  print render($issue["entity"]->body[LANGUAGE_NONE][0]["value"]);
                  print '</div>';
                  print '</div>';
                  print '<div class="key-article-next-prev-buttons">';
                  print '<span class="prev-button"><a href="' . $previousHref . '" class="previous-button">' . $previousTitle . '</a></span>';

                  // Update previousHref and previousTitle for next div.
                  $previousHref = '#' . $titleLink;
                  $previousTitle = $title;
                }
              }

              // General Risk Factors.
              if (isset($node->field_ka_general_risk_factors[LANGUAGE_NONE])) {
                $grf = $node->field_ka_general_risk_factors[LANGUAGE_NONE];
                foreach ($grf as $issue) {
                  // Get the title of the current Issue.
                  $title = $issue["entity"]->title;
                  $titleLink = strtolower($issue["entity"]->title);
                  $titleLink = str_replace(' ', '-', $titleLink);
                  $titleLink = str_replace(',', '', $titleLink);
                  $titleLink = str_replace('.', '', $titleLink);
                  $titleLink = str_replace('(', '', $titleLink);
                  $titleLink = str_replace(')', '', $titleLink);
                  $nextHref = '#' . $titleLink;

                  // Print Next Button From Previous div.
                  print '<span class="next-button"><a href="' . $nextHref . '" class="nexting-button">' . $title . '</a></span>';
                  print '</div>';
                  // Next-Previous Button div closure.
                  print '</div>';
                  // Key Article Theme div closure.
                  print '<div id="' . $titleLink . '">';
                  // Key Article Theme div open.
                  print '<div  class="key-article-text">';
                  print '<h2 class="titulos-key-articles">' . $title . '</h2>';
                  print '<div class="body-key-article">';
                  print render($issue["entity"]->body[LANGUAGE_NONE][0]["value"]);
                  print '</div>';
                  print '</div>';
                  print '<div class="key-article-next-prev-buttons">';
                  print '<span class="prev-button"><a href="' . $previousHref . '" class="previous-button">' . $previousTitle . '</a></span>';

                  // Update previousHref and previousTitle for next div.
                  $previousHref = '#' . $titleLink;
                  $previousTitle = $title;
                }
              }
              // Specific Risk Factors.
              if (isset($node->field_ka_specific_risk_factors[LANGUAGE_NONE])) {
                $srf = $node->field_ka_specific_risk_factors[LANGUAGE_NONE];
                foreach ($srf as $issue) {
                  // Get the title of the current Issue.
                  $title = $issue["entity"]->title;
                  $titleLink = strtolower($issue["entity"]->title);
                  $titleLink = str_replace(' ', '-', $titleLink);
                  $titleLink = str_replace(',', '', $titleLink);
                  $titleLink = str_replace('.', '', $titleLink);
                  $titleLink = str_replace('(', '', $titleLink);
                  $titleLink = str_replace(')', '', $titleLink);
                  $nextHref = '#' . $titleLink;

                  // Print Next Button From Previous div.
                  print '<span class="next-button"><a href="' . $nextHref . '" class="nexting-button">' . $title . '</a></span>';
                  print '</div>';
                  // Next-Previous Button div closure.
                  print '</div>';
                  // Key Article Theme div closure.
                  print '<div id="' . $titleLink . '">';
                  // Key Article Theme div open.
                  print '<div  class="key-article-text">';
                  print '<h2 class="titulos-key-articles">' . $title . '</h2>';
                  print '<div class="body-key-article">';
                  print render($issue["entity"]->body[LANGUAGE_NONE][0]["value"]);
                  print '</div>';
                  print '</div>';
                  print '<div class="key-article-next-prev-buttons">';
                  print '<span class="prev-button"><a href="' . $previousHref . '" class="previous-button">' . $previousTitle . '</a></span>';

                  // Update previousHref and previousTitle for next div.
                  $previousHref = '#' . $titleLink;
                  $previousTitle = $title;
                }
              }
              ?>
            </div> <!-- Next-Previous Button div closure -->
        </div> <!-- Key Article Theme div closure -->
    </div>
  <?php
  $nid = $node->nid;

  $view = views_embed_view('related_good_practices', $display_id = 'block', $nid);
  if (strpos($view, 'view-content')) {
    print '<div class="related-good-practices col-md-12">';
    print '<h3>' . t('Related Good Practices') . '</h3>';
    print '<div class="related-slider-big hidden-xs">';
    print $view;
    print '</div>';

    // View for Responsive Design.
    print '<div class="related-slider-small hidden-sm hidden-md hidden-lg">';
    print views_embed_view('related_good_practices', $display_id = 'block_2', $nid);
    print '</div>';
    print '</div>';
  }
  ?>
</div>
