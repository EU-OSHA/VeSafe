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
<!-- <div class="page-title-container">
	<div class="container">
		<div class="page-title-wrapper">
			<h1><?php print($node->title); ?></h1>
		</div>
	</div>
</div> -->
<div class="back-arrow-container container">
	<div class="good-likes-wrapper">
		<a class="node-like-link" href="/node/<?php print $node->nid; ?>/like"><span class="good-likes"><?php print $node->field_like_count['und'][0]['value']; ?></span></a>
	</div>
	<div class="back-arrow-wrapper">
		<a href="/good-practices" class="back-arrow">Return to list</a>
	</div>
</div>
<!--page image block-->
<div class="jumbotron-container">
	<div class="page-image-wrapper">
		<img class="img-responsive" src="<?php print file_create_url($node->field_image['und'][0]['uri']); ?>" />
	</div>
</div>
<!--general content-->
<div class="page-content-container-inside container">
	<div class="good-practice-block">
		<div class="good-practices-tags-container col-md-12">
			<?php 
				// Create variable to store the taxonomy IDs to send to the Related Good Practices Block
				$riskFilters = [];
				$vehicleFilters = [];
				// Print risk tags
				if (isset($node->field_risks["und"])){
					$risks = $node->field_risks["und"];
					if (sizeof($risks) > 0){
						print '<div class="tags-block">';
							print '<span class="tags-title">Risks: </span>';
							foreach ($risks as $item) {
								if (isset($item["taxonomy_term"])) {
									print '<span class="taxonomy-term-tag">'.($item["taxonomy_term"]->name).'</span>';
									$riskFilters[] = $item["taxonomy_term"]->tid;	
								}else if (isset($item["tid"])) {
									$taxonomy = taxonomy_term_load($item["tid"]);
									print '<span class="taxonomy-term-tag">'.($taxonomy->name).'</span>';
									$vehicleFilters[] = $item["tid"];	
								}
							}
						print '</div>';
					}	
				}				
				
				// Print vehicle tags
				if (isset($node->field_vehicles["und"])){
					$vehicles = $node->field_vehicles["und"];
					if (sizeof($vehicles) > 0){
						print '<div class="tags-block">';
							print '<span class="tags-title">Vehicles: </span>';
							foreach ($vehicles as $item) {
								if (isset($item["taxonomy_term"])){
									print '<span class="taxonomy-term-tag">'.($item["taxonomy_term"]->name).'</span>';
									$vehicleFilters[] = $item["taxonomy_term"]->tid;	
								} else if (isset($item["tid"])) {
									$taxonomy = taxonomy_term_load($item["tid"]);
									print '<span class="taxonomy-term-tag">'.($taxonomy->name).'</span>';
									$vehicleFilters[] = $item["tid"];	
								}
								
							}
						print '</div>';
					}	
				}							
			?>
		</div>
		<div class="good-practice-content col-sm-9">
			<div class="good-practice-text">
				<section class="what-is-it">
					<h3>What is it?</h3>
					<?php print(render($node->field_gp_what_is_it["und"][0]["value"])); ?>
				</section>
				<section class="who-is-it-for">
					<h3>Who is it for?</h3>
					<?php print(render($node->field_gp_who_is_for["und"][0]["value"])); ?>
				</section>
				<section class="what-is-the-benefit">
					<h3>What is the benefit?</h3>
					<?php print(render($node->field_gp_what_is_the_benefit["und"][0]["value"])); ?>
				</section>
				<section class="getting-started">
					<h3>Getting started</h3>
					<?php print(render($node->field_gp_getting_started["und"][0]["value"])); ?>
				</section>
			</div>
		</div>
		<div class="resources-container col-sm-3">
			<?php if (isset($node->field_gp_external_links['und']) || isset($node->field_gp_factsheet['und'][0]["uri"])){
				print '<section class="links">';
					print '<h3>Links</h3>';
						if (isset($node->field_gp_external_links["und"])){
							$links = $node->field_gp_external_links["und"];
							foreach ($links as $item) {
								print '<a target="_blank" href="'.$item["url"].'">'.$item["title"].'</a>';
							}	
						}
						if (isset($node->field_gp_factsheet["und"][0]['uri'])){
							print '<a target="_blank" href="'.file_create_url($node->field_gp_factsheet["und"][0]["uri"]).'"">Download factsheet</a>';	
						}
				print '</section>';
			} ?>

			<?php if (isset($node->field_additional_resources["und"])) {
				print '<section class="additional-resources">';
				print '<h3>Additional Resources</h3>';
						$resources = $node->field_additional_resources["und"];
						if (sizeof($resources) > 4){
							print '<div>';
							for ($i = 0; $i < 4; $i++){
								print '<a target="_blank" href="'.$resources[$i]["url"].'">'.$resources[$i]["title"].'</a>';
							}
							print '</div>';
							print '<div class="hidden-links">';
							for ($i = 4; $i < sizeof($resources); $i++){
								print '<a target="_blank" href="'.$resources[$i]["url"].'">'.$resources[$i]["title"].'</a>';
							}
							print '</div>';
							print '<span class="see-more-btn">See more links</span>';
						}else {
							print '<div>';
							foreach ($resources as $item) {
								print '<a target="_blank" href="'.$item["url"].'">'.$item["title"].'</a>';
							}
							print '</div>';
						}
						print '</section>';
					}
			?>
		</div>			
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

			$view = views_embed_view('related_good_practices', $display_id = 'block_1',$riskFilters.'/'.$vehicleFilters);
			if (strpos($view, 'view-content')){
				print '<div class="related-good-practices col-md-12">';
					print '<h3>Related Good Practices</h3>';
					print '<div class="related-slider-big hidden-xs">';
						print $view;
					print '</div>';

					// View for Responsive Design
					print '<div class="related-slider-small hidden-sm hidden-md hidden-lg">';
						print views_embed_view('related_good_practices', $display_id = 'block_3',$riskFilters.'/'.$vehicleFilters);
					print '</div>';
				print '</div>';
			}			
		?>
	</div>
</div>