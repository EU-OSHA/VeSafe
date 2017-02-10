jQuery(document).ready(function () {
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
        }
      },
      data: 'js=1'
    });
    return false;
  });
});
