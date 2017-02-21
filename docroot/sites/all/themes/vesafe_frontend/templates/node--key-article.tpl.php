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

<!--page title block-->
<div class="page-title-container">
	<div class="container">
		<div class="page-title-wrapper">
			<h1><?php print($node->title); ?></h1>
		</div>
		<div class="page-subtitle-wrapper">
			<h3><?php print($node->field_subtitle["und"][0]["value"]); ?></h3>
		</div>
	</div>
</div>
<div class="back-arrow-container container">
	<div class="back-arrow-wrapper">
		<span class="back-arrow">Volver al listado</span>
	</div>
</div>
<!--page image block-->
<div class="jumbotron-container">
	<div class="container-fluid">
		<div class="page-image-wrapper">
			<img src="<?php print file_create_url($node->field_image['und'][0]['uri']); ?>" />
		</div>
	</div>
</div>
<!--general content-->
<div class="page-content-container container">
	<div class="key-articles-menu-container col-md-3">
		<ul>
			<li><a href="#introduction">Introduction</a></li>
			<li>
				<span>General safety issues</span>
				<ul><?php
					$gsi = 	$node->field_ka_general_safety_issues["und"];
					foreach ($gsi as $issue) {
						$title = $issue["entity"]->title;
						$titleLink = strtolower($issue["entity"]->title);
						$titleLink = str_replace(' ', '-', $titleLink);

						print '<li><a href="#'.$titleLink.'">'.$title.'</a></li>';
					}
				?></ul>
			</li>
			<li>
				<span>General risk factors</span>
				<ul><?php
					$grf = $node->field_ka_general_risk_factors["und"];
					foreach ($grf as $issue) {
						$title = $issue["entity"]->title;
						$titleLink = strtolower($issue["entity"]->title);
						$titleLink = str_replace(' ', '-', $titleLink);

						print '<li><a href="#'.$titleLink.'">'.$title.'</a></li>';
					}
				?></ul>
			</li>
			<li>
				<span>Specific risk factors</span>
				<ul><?php
					$srf = $node->field_ka_specific_risk_factors["und"];
					foreach ($srf as $issue) {
						$title = $issue["entity"]->title;
						$titleLink = strtolower($issue["entity"]->title);
						$titleLink = str_replace(' ', '-', $titleLink);

						print '<li><a href="#'.$titleLink.'">'.$title.'</a></li>';
					}
				?></ul>
			</li>
		</ul>
	</div>
	<div id="introduction" class="key-article-content col-md-9">
		<div class="key-article-text">
			<h3 class="titulos-key-articles">Introduction</h3>
			<div class="body-key-article">
				<?php
					print (render($node->body["und"]["0"]["value"]));
				?>
			</div>
		</div>
		<div class="key-article-next-prev-buttons">

		<?php
			$previousHref = '#introduction';
			$previousTitle = 'Introduction';
			$nextHref = '';

			// General Safety Issues
			$gsi = $node->field_ka_general_safety_issues["und"];
			foreach ($gsi as $issue) {			
				// Get the title of the current Issue
				$title = $issue["entity"]->title;
				$titleLink = strtolower($issue["entity"]->title);
				$titleLink = str_replace(' ', '-', $titleLink);
				$nextHref = '#' . $titleLink;

				// Print Next Button From Previous div
						print '<button  type="button" class="next-button"><a href="'.$nextHref.'" class="next-button">'.$title.'</a></button>';
					print '</div>'; // Next-Previous Button div closure
				print '</div>'; // Key Article Theme div closure


				print '<div id="'.$titleLink.'" class="key-article-content col-md-9">'; // Key Article Theme div open
					print '<div  class="key-article-text">';
						print '<h3 class="titulos-key-articles">'.$title.'</h3>';
						print '<div class="body-key-article">';
							print render($issue["entity"]->body["und"][0]["value"]);
						print '</div>';
					print '</div>';
					print '<div class="key-article-next-prev-buttons">';
						print '<button  type="button" class="prev-button"><a href="'.$previousHref.'" class="previous-button">'.$previousTitle.'</a></button>';
				
				// Update previousHref and previousTitle for next div
				$previousHref = '#' . $titleLink;
				$previousTitle = $title;
			}

			// General Risk Factors
			$grf = $node->field_ka_general_risk_factors["und"];
			foreach ($grf as $issue) {
				// Get the title of the current Issue
				$title = $issue["entity"]->title;
				$titleLink = strtolower($issue["entity"]->title);
				$titleLink = str_replace(' ', '-', $titleLink);
				$nextHref = '#' . $titleLink;

				// Print Next Button From Previous div
						print '<button  type="button" class="next-button"><a href="'.$nextHref.'" class="next-button">'.$title.'</a></button>';
					print '</div>'; // Next-Previous Button div closure
				print '</div>'; // Key Article Theme div closure


				print '<div id="'.$titleLink.'" class="key-article-content col-md-9">'; // Key Article Theme div open
					print '<div  class="key-article-text">';
						print '<h3 class="titulos-key-articles">'.$title.'</h3>';
						print '<div class="body-key-article">';
							print render($issue["entity"]->body["und"][0]["value"]);
						print '</div>';
					print '</div>';
					print '<div class="key-article-next-prev-buttons">';
						print '<button  type="button" class="prev-button"><a href="'.$previousHref.'" class="previous-button">'.$previousTitle.'</a></button>';
				
				// Update previousHref and previousTitle for next div
				$previousHref = '#' . $titleLink;
				$previousTitle = $title;
			}

			// Specific Risk Factors
			$srf = $node->field_ka_specific_risk_factors["und"];
			foreach ($srf as $issue) {
				// Get the title of the current Issue
				$title = $issue["entity"]->title;
				$titleLink = strtolower($issue["entity"]->title);
				$titleLink = str_replace(' ', '-', $titleLink);
				$nextHref = '#' . $titleLink;

				// Print Next Button From Previous div
						print '<button  type="button" class="next-button"><a href="'.$nextHref.'" class="next-button">'.$title.'</a></button>';
					print '</div>'; // Next-Previous Button div closure
				print '</div>'; // Key Article Theme div closure


				print '<div id="'.$titleLink.'" class="key-article-content col-md-9">'; // Key Article Theme div open
					print '<div  class="key-article-text">';
						print '<h3 class="titulos-key-articles">'.$title.'</h3>';
						print '<div class="body-key-article">';
							print render($issue["entity"]->body["und"][0]["value"]);
						print '</div>';
					print '</div>';
					print '<div class="key-article-next-prev-buttons">';
						print '<button  type="button" class="prev-button"><a href="'.$previousHref.'" class="previous-button">'.$previousTitle.'</a></button>';
				
				// Update previousHref and previousTitle for next div
				$previousHref = '#' . $titleLink;
				$previousTitle = $title;
			}
		?>

		</div> <!-- Next-Previous Button div closure -->
	</div> <!-- Key Article Theme div closure -->
	<div class="related-good-practices col-md-12">
		<?php 
			$nid = $node->nid;
			print views_embed_view('related_good_practices', $display_id = 'block',$nid); 
		?>
	</div>
</div>
