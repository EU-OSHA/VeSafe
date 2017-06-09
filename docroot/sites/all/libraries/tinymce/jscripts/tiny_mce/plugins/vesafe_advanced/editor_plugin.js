(function() {
    /**
     * @class tinymce.plugins.vesafeAdvanced
     */
    tinymce.create('tinymce.plugins.vesafeAdvanced', {
        init : function(ed, url) {
            jQuery('#wysiwyg-toggle-'+ed.id).hide();
            var visual_html = jQuery('#' + ed.id + '_visual_html').length;
            if(visual_html == 0){
                jQuery('#' + ed.id).after('<div class="form-wrapper"><div class="form-item">' + Drupal.t('Editor mode: ') + '<select id="' + ed.id + '_visual_html" name="' + ed.id + '_visual_html" class="form-select"><option value="visual">' + Drupal.t('Visual') + '</option><option name="html">' + Drupal.t('HTML') + '</option></select></div></div>');
                jQuery('#' + ed.id + '_visual_html').bind('change', function(){
                    jQuery('#wysiwyg-toggle-'+ed.id).trigger( "click" );
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
