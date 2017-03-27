jQuery(document).ready(function () {
  var likedNodes = jQuery.cookie('liked-nodes');
  if (likedNodes != null && likedNodes != ''){
    likedNodes = likedNodes.split(',');
    var links = jQuery('a.node-like-link');
    var href = '';
    for (var i = 0; i < links.size(); i++) {
      href = jQuery(links[i]).attr('href');
      href = href.replace('/node/','');
      href = href.replace('/like', '');

      if (likedNodes.indexOf(href) > -1) {
        jQuery(links[i]).attr('title', 'You have already liked this Good Practice');
        jQuery(links[i]).attr('onclick', 'return false');
        jQuery(links[i]).attr('href', '#');
        jQuery(links[i]).addClass('node-liked-link');
        jQuery(links[i]).removeClass('node-like-link');
      }
    }
  }

  jQuery('a.node-like-link').click(function () {
    var link = this;
    jQuery.ajax({
      type: 'POST',
      url: this.href + '?vote=1',
      dataType: 'json',
      success: function (data) {
        if (typeof data.selector == 'string') {
          jQuery(link).attr('title', 'Thank you');
          jQuery(link).attr('data-toggle', 'tooltip');
          jQuery(link).tooltip('show');
          jQuery(data.selector).text(data.text);
          var text = data.selector;
          text = text.replace('#node-like-','');
          if (jQuery.cookie('liked-nodes') != null) {
            jQuery.cookie('liked-nodes', jQuery.cookie('liked-nodes') + ',' + text, { expires: 7300 });
          }else{
            jQuery.cookie('liked-nodes', text, { expires: 7300 });
          }
        }
      },
      data: 'js=1'
    });
    jQuery(this).addClass('node-liked-link');
    jQuery(this).removeClass('node-like-link');

    return false;
  });
});
