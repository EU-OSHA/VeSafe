jQuery(document).ready(function () {

    jQuery('#vesafe-search-form-sidebar').submit(function() {
    	jQuery('#edit-submit-sidebar').attr('name','');
	});

    jQuery('#vesafe-search-form').submit(function() {
        jQuery('#edit-submit').attr('name','');
    });

    jQuery('#vesafe-search-form-gp').submit(function() {
        jQuery('#edit-submit-gp').attr('name','');
    });

	jQuery(".changer").addClass("notranslate");

	jQuery("#facetapi-facet-search-apidefault-solr-index-block-type").siblings("h2").addClass("type-icon");
	jQuery("#facetapi-facet-search-apidefault-solr-index-block-field-risks").siblings("h2").addClass("risk-icon");
	jQuery("#facetapi-facet-search-apidefault-solr-index-block-field-vehicles").siblings("h2").addClass("vehicle-icon");

	if(jQuery(".page-good-practices #edit-sort-by-field-like-count a").hasClass("active") || jQuery(".page-good-practices #edit-sort-by-field-publication-date a").hasClass("active")){

	}else{
		jQuery(".page-good-practices #edit-sort-by-field-publication-date a").addClass("active");
	}

	if(jQuery(".page-search #edit-sort-by-search-api-relevance a").hasClass("active") || jQuery(".page-search #edit-sort-by-field-publication-date a").hasClass("active")){

	}else{
		jQuery(".page-search #edit-sort-by-search-api-relevance a").addClass("active");
	}
	

	/*search filter menu open/close*/
	jQuery(".facetapi-facetapi-links").hide();
    jQuery(".type-icon").click(function(){
        jQuery(this).toggleClass("open");
        jQuery("#facetapi-facet-search-apidefault-solr-index-block-type").slideToggle();
    });
	jQuery(".risk-icon").click(function(){
		jQuery(this).toggleClass("open");
		jQuery("#facetapi-facet-search-apidefault-solr-index-block-field-risks").slideToggle();
	});
	jQuery(".vehicle-icon").click(function(){
		jQuery(this).toggleClass("open");
		jQuery("#facetapi-facet-search-apidefault-solr-index-block-field-vehicles").slideToggle();
	});

	/*search filter menu open/close FOR TABLET/MOBILE*/
	if(jQuery("h2.filters").is(":visible")){
		jQuery(".well").hide();
	}
	jQuery("h2.filters").click(function(){
		jQuery(".well").slideToggle();
		jQuery(this).toggleClass("open-filters");
	});

	/*key articles open/close menu for tablet/mobile*/
	if(jQuery(".key-articles-menu-container h2").is(":visible")){
		jQuery(".key-articles-menu-container > ul").hide();
	}
	jQuery(".key-articles-menu-container h2").click(function(){
		jQuery(".key-articles-menu-container > ul").slideToggle();
		jQuery(this).toggleClass("key-menu-arrow-close");
	});
	

	/*key articles menu/next/prev functionality*/
	jQuery(".key-article-content > div").addClass("close");
	jQuery(".key-article-content > div#introduction").removeClass("close").addClass("active");

	jQuery(".key-articles-menu-container a").click(function(){
		var href=jQuery(this).attr("href");
		jQuery(".key-article-content > div").addClass("close");
		jQuery(href).removeClass("close");
		jQuery(".key-article-content > #introduction").removeClass("active");
		jQuery(href).addClass("active");
		jQuery(".key-articles-menu-container a").css("font-weight", "normal");
		jQuery(this).css({ "font-weight": "bold", "text-decoration": "none" });
	});

	jQuery(".key-article-next-prev-buttons span a").click(function(){
		var href=jQuery(this).attr("href");
		jQuery(".key-article-content > div").addClass("close");
		jQuery(href).removeClass("close");
		jQuery(".key-article-content > #introduction").removeClass("active");
		jQuery(href).addClass("active");
	});
	/*end key articles functionality*/

	/*key articles menu acordion*/
	jQuery(".key-articles-menu-container > ul > li > ul").hide();
	jQuery(".key-articles-menu-container > ul > li, .key-articles-menu-container > ul > li").click(function(){
		jQuery(".key-articles-menu-container > ul > li > a, .key-articles-menu-container > ul > li > span").removeClass("key-menu-arrow-close");
		jQuery("> a, > span", this).toggleClass("key-menu-arrow-close");
		jQuery("a[href*='#introduction']", this).removeClass("key-menu-arrow-close");
		jQuery(".key-articles-menu-container > ul > li > ul").hide();
		jQuery("ul" ,this).show();
	});
	/*end key articles acordion*/

	/*key article clicking next/prev button change the acordion*/
	
	jQuery(".key-article-next-prev-buttons span a").click(function(){
		jQuery(".key-articles-menu-container > ul > li > ul").hide();
		jQuery(".key-articles-menu-container > ul > li > a, .key-articles-menu-container > ul > li > span").removeClass("key-menu-arrow-close");
		var href=jQuery(this).attr("href");
		jQuery(".key-articles-menu-container a").css("font-weight", "normal");
		jQuery(".key-articles-menu-container a[href*='"+href+"']").css({ "font-weight": "bold", "text-decoration": "none" });

		jQuery(".key-articles-menu-container a[href*='"+href+"']").parent().parent().parent().find("span").addClass("key-menu-arrow-open");
		//jQuery(".key-article-next-prev-buttons button a[href*='#introduction']").parent().removeClass("key-menu-arrow-close");
		jQuery(".key-articles-menu-container a[href*='"+href+"']").parent().parent().parent().find("ul").show();
		//jQuery(".key-articles-menu-container > ul > li > a, .key-articles-menu-container > ul > li > span", this).toggleClass("key-menu-arrow-close");
		//jQuery(".key-articles-menu-container > ul > li > ul").hide();
		//jQuery("ul" ,this).show();
	});
	jQuery(".key-article-next-prev-buttons span a[href*='#introduction']").click(function(){
		jQuery(".key-articles-menu-container > ul > li > ul").hide();
	});
	/*end key articles acordion*/


	/*Show more links for good practices*/
	jQuery(".see-more-btn").click(function(){
		jQuery(".hidden-links").slideToggle("fast", function(){
			if(jQuery(".hidden-links").is(":visible")){
				jQuery(".see-more-btn").text("See less links");
			}else{
				jQuery(".see-more-btn").text("See more links");
			}
		});
	});
	/*end show more links for good practices*/

	/*contact form submit scrolltop*/
	jQuery(".node-type-webform .page-content-container .webform-submit").click(function(){
		jQuery("html, body").animate({"scrollTop": "120px"}, 200);
	});
	/*end contact form submit scrolltop*/

	/*scroll upp the page on click footer button*/
	jQuery("#scroll-top").on("click", function() {
	    event.preventDefault();
    	jQuery("html, body").animate({"scrollTop": "0px"}, 200);
	});
	/*end scroll upp the page on click footer button*/

	/*fixing sticky menu*/
	/*hight of page*/
	var num = 150; //number of pixels before modifying styles
	if(jQuery("body").height()>=1200){
		jQuery(window).bind('scroll', function () {
		    if (jQuery(window).scrollTop() > num) {
		        jQuery("header").addClass("sticky-menu");
		    } else {
		        jQuery('header').removeClass('sticky-menu');
		    }
		});
	}
	/*end hight of page*/

	/*adding border to third level links menu*/
	jQuery(".node-type-good-practice #navbar ul.menu li:nth-child(2) a").css("border-bottom", "2px solid white");
	jQuery(".node-type-key-article #navbar ul.menu li:nth-child(3) a").css("border-bottom", "2px solid white");

	var windowWidth= jQuery(window).width();//window size

	jQuery(window).resize(function() {
	    windowWidth= jQuery(window).width();//window size, when resizing
	    if(windowWidth > 992){
	    }
	    if(windowWidth <= 750){
	    }
	});


	/*specific functions for pc, tablet and mobile */
	funcionesPc();

	funcionesPcTablet();

	funcionesTabletMovil();

	funcionesMovil();

	function funcionesPc () {
		if(windowWidth > 992){//<-----functions for Pc

		}
	}

	function funcionesPcTablet () {
		if(windowWidth > 750){//<-----functions for Pc and/or tablet

		}
	}

	function funcionesTabletMovil () {
		if(windowWidth <= 992){//<-----functions for tablet and/or mobile

		}//<-----End: functions for tablet and/or mobile
	}

	function funcionesMovil () {
		if(windowWidth <= 750){//<-----functions for mobile
			/*google translator hide on mobile when click nav toogle*/
			jQuery(".navbar-toggle").click(function(){
		        jQuery("#block-gtranslate-gtranslate").stop().slideToggle();
		    });
		}
	}

	printAppliedFacets(); 

	function printAppliedFacets() {
		var appliedFacets = jQuery('div.region-sidebar-first li.leaf a.facetapi-active');
		if (appliedFacets.size() == 0){
			jQuery('div#applied-filters').hide();
		}
		if (appliedFacets.size() > 0){
			var href = '', text = '', html = '';
			for (var i = 0; i < appliedFacets.size(); i++) {
				// Get the href of the link to remove the facet
				href = jQuery(appliedFacets[i]).attr('href');

				// Get the text of the element
				text = jQuery(appliedFacets[i]).text();
				text = jQuery(appliedFacets[i]).parent().text().replace(text, '');

				// Generate the HTML code for the element
				html += '<span><a href="' + href + '">X</a>' + text + '</span>';
			}
			// Apply the generated HTML to the applied filters div
			jQuery('div#applied-filters').html(html);
		}
	}

	jQuery('div.region-sidebar-first li.leaf a.facetapi-active').parent().css("font-weight", "bold");


    openFacetsType();

    function openFacetsType() {
        var appliedFacets = jQuery('div.region-sidebar-first .facetapi-facet-type li.leaf a.facetapi-active');
        if (appliedFacets.size() > 0){
            jQuery('div.region-sidebar-first .facetapi-facet-type').show();
            jQuery("h2.type-icon").addClass("open");

        }
    }
	
	openFacetsRisk(); 

	function openFacetsRisk() {
		var appliedFacets = jQuery('div.region-sidebar-first .facetapi-facet-field-risks li.leaf a.facetapi-active');
		if (appliedFacets.size() > 0){
			jQuery('div.region-sidebar-first .facetapi-facet-field-risks').show();
			jQuery("h2.risk-icon").addClass("open");

		}
	}

	openFacetsVehicle(); 

	function openFacetsVehicle() {
		var appliedFacets = jQuery('div.region-sidebar-first .facetapi-facet-field-vehicles li.leaf a.facetapi-active');
		if (appliedFacets.size() > 0){
			jQuery('div.region-sidebar-first .facetapi-facet-field-vehicles').show();
			jQuery("h2.vehicle-icon").addClass("open");
		}
	}
});

function vesafeBackURL(referrer){
	referrer_found = document.referrer.indexOf(referrer);
    if(referrer_found!=-1){
    	document.location.href = document.referrer;
	}else{
        document.location.href = referrer;
	}
	return FALSE;
}
