(function() {
    /**
     * @class tinymce.plugins.vesafeAdvanced
     */
    tinymce.create('tinymce.plugins.vesafeAdvanced', {
        init : function(ed, url) {
            jQuery('#wysiwyg-toggle-'+ed.id).hide();
            var visual_html = jQuery('#' + ed.id + '_visual_html').length;
            if(visual_html == 0){
                jQuery('label[for="' + ed.id + '"]').append('<ul class="tabs primary tinymce-visual-html" id="' + ed.id + '_visual_html"><li><a href="#" id="' + ed.id + '_visual" class="active">' + Drupal.t('Visual') + '</a></li><li><a href="#" id="' + ed.id + '_html">' + Drupal.t('HTML') + '</a></li></ul>');
                jQuery('#' + ed.id + '_visual_html a').bind('click', function(){
                    if(!jQuery(this).hasClass('active')){
                        jQuery('#' + ed.id + '_visual_html a').removeClass('active');
                        jQuery(this).addClass('active');
                        jQuery('#wysiwyg-toggle-'+ed.id).trigger( "click" );
                    }
                });
            }
            jQuery('#' + ed.id.replace('-value','-format')).hide();
            var format_select = jQuery('#' + ed.id.replace('-value','-format--2'));
            if(format_select.val() == 'full_html_minimal') {
                ed.addButton('vesafe_advanced', {title : Drupal.t('Switch'), cmd : 'tinyMCEAdvanced'});
            }else{
                ed.addButton('vesafe_minimal', {title : Drupal.t('Switch'), cmd : 'tinyMCEAdvanced'});
            }
            ed.addCommand("tinyMCEAdvanced", function() {
                if(format_select.val() == 'full_html_minimal') {
                    format_select.val('full_html');
                }else{
                    format_select.val('full_html_minimal');
                }
                format_select.change();
            });
        }
    });
    // Register plugin
    tinymce.PluginManager.add('vesafe_advanced', tinymce.plugins.vesafeAdvanced);
})();
