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
<!--page title block-->
<div class="page-title-container">
	<div class="container">
		<div class="page-title-wrapper">
			<h1><?php print($node->title); ?></h1>
		</div>
	</div>
</div>
<div class="back-arrow-container container">
	<div class="good-likes-wrapper">
		<span class="good-likes"><!--aqui la cantidad de likes--></span>
	</div>
	<div class="back-arrow-wrapper">
		<span class="back-arrow">Return to list</span>
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
	<div class="good-practices-menu-container col-md-12">
		<?php 
			// Create variable to store the taxonomy IDs to send to the Related Good Practices Block
			$riskFilters = [];
			$vehicleFilters = [];
			// Print risk tags
			$risks = $node->field_risks["und"];
			if (sizeof($risks) > 0){
				print '<div>';
					print '<span>Risks: </span>';
					foreach ($risks as $item) {
						print '<span>'.($item["taxonomy_term"]->name).'</span>';
						$riskFilters[] = $item["taxonomy_term"]->tid;
					}
				print '</div>';
			}
			
			// Print vehicle tags
			$vehicles = $node->field_vehicles["und"];
			if (sizeof($vehicles) > 0){
				print '<div>';
					print '<span>Vehicles: </span>';
					foreach ($vehicles as $item) {
						print '<span>'.($item["taxonomy_term"]->name).'</span>';
						$vehicleFilters[] = $item["taxonomy_term"]->tid;
					}
				print '</div>';
			}			
		?>
	</div>
	<div class="good-practice-content col-sm-9">
		<div class="good-practice-text">
			<section class="what-is-it">
				<h6>What is it?</h6>
				<?php print(render($node->field_gp_what_is_it["und"][0]["value"])); ?>
			</section>
			<section class="who-is-it-for">
				<h6>Who is it for?</h6>
				<?php print(render($node->field_gp_who_is_for["und"][0]["value"])); ?>
			</section>
			<section class="what-is-the-benefit">
				<h6>What is the benefit?</h6>
				<?php print(render($node->field_gp_what_is_the_benefit["und"][0]["value"])); ?>
			</section>
			<section class="what-is-the-benefit">
				<h6>Getting started</h6>
				<?php print(render($node->field_gp_getting_started["und"][0]["value"])); ?>
			</section>
		</div>
	</div>
	<div class="resources-container col-sm-3">
		<section class="links">
			<h6>Links</h6>
			<?php
				$links = $node->field_gp_external_links["und"];
				foreach ($links as $item) {
					print '<a href="'.$item["url"].'">'.$item["title"].'</a>';
				}
				print '<a href="'.file_create_url($node->field_gp_factsheet["und"][0]["uri"]).'"">Download factsheet</a>';
			?>
		</section>
		<section class="additional-resources">
			<h6>Additional Resources</h6>
			<?php
				$resources = $node->field_additional_resources["und"];
				foreach ($resources as $item) {
					print '<a href="'.$item["url"].'">'.$item["title"].'</a>';
				}
			?>
		</section>
	</div>
	<div class="related-good-practices col-md-12">
		<?php
			if (sizeof($riskFilters) == 0) {
				$riskFilters = 'all';
			}else{
				$riskFilters = implode('+',$riskFilters);
			}
			if (sizeof($vehicleFilters) == 0) {
				$vehicleFilters = 'all';
			}else{
				$vehicleFilters = implode('+', $vehicleFilters);	
			}
			
			print views_embed_view('related_good_practices', $display_id = 'block_1',$riskFilters.'/'.$vehicleFilters);
		?>
	</div>
</div>