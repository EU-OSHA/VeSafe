jQuery(document).ready(function () {
  var likedNodes, cookie;
  if (document.cookie.indexOf('liked-nodes') != -1) {

    getLikedNodes();
    var links = jQuery('a.node-like-link');
    var href = '';
    for (var i = 0; i < links.size(); i++) {
      href = jQuery(links[i]).attr('href');
      href = href.replace('/node/','');
      href = href.replace('/like', '');

      if (likedNodes.indexOf(href) > -1) {
        jQuery(links[i]).attr('title', 'Already liked');
        jQuery(links[i]).attr('data-toggle', 'tooltip');
        jQuery(links[i]).hover(function(){jQuery(this).tooltip('show');});
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
          if (cookie != null) {
            cookie += '%2C' + text;
            document.cookie = 'liked-nodes='+cookie;
          }else{
            document.cookie = 'liked-nodes='+text;
          }
          jQuery('.good-likes', link).text(Number(jQuery('.good-likes', link).text())+1);
        }
      },
      data: 'js=1'
    });
    
    jQuery(this).addClass('node-liked-link');
    //jQuery(this).attr('onclick', 'return false');
    jQuery(this).attr('href', '#');
    jQuery(this).removeClass('node-like-link');

    return false;
  });

  function getLikedNodes () {
    cookie = document.cookie.substring (document.cookie.indexOf('liked-nodes'));
    cookie = cookie.substring(0, cookie.indexOf(';'));
    cookie = cookie.replace('liked-nodes=','');

    if (document.cookie.match(/liked-nodes/g).length > 1) {
      var cookie2 = document.cookie;
      cookie2 = cookie2.replace('liked-nodes','');
      cookie2 = cookie2.substring(cookie2.indexOf('liked-nodes'));
      cookie2 = cookie2.substring(0,cookie2.indexOf(';'));
      cookie2 = cookie2.replace('liked-nodes=','');

      cookie = cookie + '%2C' + cookie2;
    }

    likedNodes = cookie.split('%2C');
  }
  
});
