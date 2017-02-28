jQuery(document).ready(function () {

	// jQuery('.trim-title').dotdotdot({
	// 	ellipsis: '...',
	// 	height: 45,
	// 	watch: true,
	// 	wrap: 'word',
	// });

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

	jQuery(".key-article-next-prev-buttons button a").click(function(){
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
	
	jQuery(".key-article-next-prev-buttons button a").click(function(){
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
	jQuery(".key-article-next-prev-buttons button a[href*='#introduction']").click(function(){
		jQuery(".key-articles-menu-container > ul > li > ul").hide();
	});
	/*end key articles acordion*/


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

		}
	}
});