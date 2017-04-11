<?php
/**
 * Render footer menu as nav-pills.
 */
function bootstrap_menu_tree__menu_footer_menu(&$variables) {
  return '<ul class="menu nav nav-pills">' . $variables['tree'] . '</ul>';
}


/**
 * Implements hook_path_breadcrumbs_view_alter().
 *
 * {@inheritdoc}
 */
function vesafe_frontend_path_breadcrumbs_view_alter(&$breadcrumbs, $path_breadcrumbs, $contexts) {
  if (drupal_is_front_page()) {
    $breadcrumbs = null;
  }
}

/**
 * Implements hook_process_html_tag().
 */
function vesafe_frontend_process_html_tag(&$variables) {
  $tag = &$variables['element'];

  if ($tag['#tag'] == 'script') {
    $tag['#attributes']['type'] = 'text/javascript';
  }

  if ($tag['#tag'] == 'style') {
    $tag['#attributes']['type'] = "text/css";
  }
}

function vesafe_frontend_preprocess_page(&$vars) {
  global $language;
  if (drupal_is_front_page()) {
    unset($vars['page']['content']['system_main']['default_message']);
  }
  $vars['logo'] = '/sites/all/themes/vesafe_frontend/images/eu-osha-logo/EU-OSHA-'.($language->language).'.png';
  $vars['eu_logo'] = '/sites/all/themes/vesafe_frontend/images/europeLogo.png';
  $vars['vesafe_logo'] = '/sites/all/themes/vesafe_frontend/images/vesafeLogo.gif';

  // Set info status for contact confirmation submission
  if (!empty($vars['page']['contact_form_widget']['webform_client-block-43'])) {
    $node = node_load(43);
    $messages = drupal_get_messages('status');

    if (!empty($messages['status']) && !empty($node->webform['confirmation'])) {
      foreach ($messages['status'] as $idx => $message) {
        if (strcmp($message, $node->webform['confirmation']) == 0) {
          array_splice($messages['status'], $idx, 1);
          drupal_set_message('<div class="webform-confirmation">' . t($node->webform['confirmation']) . '</div>','info');
        }
      }
    }
  }
  // Add information about the number of sidebars.
  if (!empty($vars['page']['sidebar_first']) && !empty($vars['page']['sidebar_second'])) {
    $vars['content_column_class'] = ' class="col-sm-6"';
  }
  elseif (!empty($vars['page']['sidebar_first']) || !empty($vars['page']['sidebar_second'])) {
    $vars['content_column_class'] = ' class="col-md-9"';
  }
  else {
    $vars['content_column_class'] = '';
  }
}

function vesafe_frontend_css_alter(&$css) {
  global $theme_info, $base_theme_info;
  if (isset($css['sites/all/modules/contrib/panels/css/panels.css'])) {
    unset($css['sites/all/modules/contrib/panels/css/panels.css']);
  }
}

function vesafe_frontend_preprocess_region(&$variables, $hook) {
  if($variables['region'] == "header_block"){
    $variables['classes_array'][] = 'clearfix';
  }
}

function vesafe_frontend_preprocess_field(&$variables) {
  // Add theme suggestion for field based on field name and view mode.
  if (!empty($variables['element']['#view_mode'])) {
    $variables['theme_hook_suggestions'][] = 'field__' . $variables['element']['#field_name'] . '__' . $variables['element']['#view_mode'];
  }
}

function vesafe_frontend_preprocess_node(&$vars) {
  if (isset($vars['content']['links']['node']['#links']['node-readmore'])) {
//    $vars['content']['links']['node']['#links']['node-readmore']['title'] = t('See more');
  }
  $view_mode = $vars['view_mode'];
  $vars['theme_hook_suggestions'][] = 'node__' . $view_mode;
  $vars['theme_hook_suggestions'][] = 'node__' . $vars['node']->type . '__' . $view_mode;
  $vars['theme_hook_suggestions'][] = 'node__' . $vars['node']->nid . '__' . $view_mode;
  if (context_isset('context', 'segmentation_page')) {
    $vars['theme_hook_suggestions'][] = 'node__article_segment';
  }
//  vesafe_frontend_top_anchor($vars);
}

function vesafe_frontend_preprocess_image_style(&$variables) {
  $variables['attributes']['class'][] = 'img-responsive';
  if (empty($variables['alt'])) {
    $variables['alt'] = drupal_basename($variables['path']);
  }
}
/**
 * Implements theme_on_the_web_image().
 *
 * @param $variables
 *   An associative array with generated variables.
 *
 * @return
 *   HTML for a social media icon.
 */

/**
* Implements theme_pager().
*/
function vesafe_frontend_pager($variables) {
  // Overwrite pager links.
  $variables['tags'][0] = '«';
  $variables['tags'][1] = '‹';
  $variables['tags'][3] = '›';
  $variables['tags'][4] = '»';

  $tags = $variables['tags'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $quantity = $variables['quantity'];
  global $pager_page_array, $pager_total;

  // Calculate various markers within this pager piece:
  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);
  // current is the page we are currently paged to
  $pager_current = $pager_page_array[$element] + 1;
  // first is the first page listed by this pager piece (re quantity)
  $pager_first = $pager_current - $pager_middle + 1;
  // last is the last page listed by this pager piece (re quantity)
  $pager_last = $pager_current + $quantity - $pager_middle;
  // max is the maximum page number
  $pager_max = $pager_total[$element];
  // End of marker calculations.

  // Prepare for generation loop.
  $i = $pager_first;

  $li_first = theme('pager_first', array('text' => (isset($tags[0]) ? $tags[0] : t('« first')), 'element' => $element, 'parameters' => $parameters));
  $li_previous = theme('pager_previous', array('text' => (isset($tags[1]) ? $tags[1] : t('‹ previous')), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
  $li_next = theme('pager_next', array('text' => (isset($tags[3]) ? $tags[3] : t('next ›')), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
  $li_last = theme('pager_last', array('text' => (isset($tags[4]) ? $tags[4] : t('last »')), 'element' => $element, 'parameters' => $parameters));

  if ($pager_total[$element] > 1) {
    if ($li_first) {
      $items[] = array(
        'class' => array('pager-first'),
        'data' => $li_first,
      );
    }
    if ($li_previous) {
      $items[] = array(
        'class' => array('pager-previous'),
        'data' => $li_previous,
      );
    }

  // When there is more than one page, create the pager list.
    $items[] = array(
      'class' => array('pager-current'),
      'data' => $pager_current,
    );

    $items[] = array(
      'class' => array('pager-separator'),
      'data' => '/',
    );

    if ($pager_max - $pager_current) {
      $items[] = array(
        'class' => array('pager-item'),
        'data' => theme('pager_next', array('text' => $pager_max, 'element' => $element, 'interval' => ($pager_max - $pager_current), 'parameters' => $parameters)),
      );
    }
    else {
      $items[] = array(
        'class' => array('pager-item'),
        'data' => $pager_current,
      );
    }
    // End generation.
    if ($li_next) {
      $items[] = array(
        'class' => array('pager-next'),
        'data' => $li_next,
      );
    }
    if ($li_last) {
      $items[] = array(
        'class' => array('pager-last'),
        'data' => $li_last,
      );
    }
    return theme('item_list', array(
      'items' => $items,
      'attributes' => array('class' => array('pager')),
    ));
  }
}

/**
 * Colorbox theme function to add support for image field caption.
 *
 * @see theme_colorbox_image_formatter
 */
function vesafe_frontend_colorbox_image_formatter($variables) {
  $item = $variables['item'];
  $entity_type = $variables['entity_type'];
  $entity = $variables['entity'];
  $field = $variables['field'];
  $settings = $variables['display_settings'];
  $image = array(
    'path' => $item['uri'],
    'alt' => isset($item['alt']) ? $item['alt'] : '',
    'title' => isset($item['title']) ? $item['title'] : '',
    'style_name' => $settings['colorbox_node_style'],
  );
  if ($variables['delta'] == 0 && !empty($settings['colorbox_node_style_first'])) {
    $image['style_name'] = $settings['colorbox_node_style_first'];
  }
  if (isset($item['width']) && isset($item['height'])) {
    $image['width'] = $item['width'];
    $image['height'] = $item['height'];
  }
  if (isset($item['attributes'])) {
    $image['attributes'] = $item['attributes'];
  }
  // Allow image attributes to be overridden.
  if (isset($variables['item']['override']['attributes'])) {
    foreach (array('width', 'height', 'alt', 'title') as $key) {
      if (isset($variables['item']['override']['attributes'][$key])) {
        $image[$key] = $variables['item']['override']['attributes'][$key];
        unset($variables['item']['override']['attributes'][$key]);
      }
    }
    if (isset($image['attributes'])) {
      $image['attributes'] = $variables['item']['override']['attributes'] + $image['attributes'];
    }
    else {
      $image['attributes'] = $variables['item']['override']['attributes'];
    }
  }
  $entity_title = entity_label($entity_type, $entity);
  switch ($settings['colorbox_caption']) {
    case 'auto':
      // If the title is empty use alt or the entity title in that order.
      if (!empty($image['title'])) {
        $caption = $image['title'];
      }
      elseif (!empty($image['alt'])) {
        $caption = $image['alt'];
      }
      elseif (!empty($entity_title)) {
        $caption = $entity_title;
      }
      else {
        $caption = '';
      }
      break;
    case 'title':
      $caption = $image['title'];
      break;
    case 'alt':
      $caption = $image['alt'];
      break;
    case 'node_title':
      $caption = $entity_title;
      break;
    case 'custom':
      $caption = token_replace($settings['colorbox_caption_custom'], array(
        $entity_type => $entity,
        'file' => (object) $item
      ), array('clear' => TRUE));
      break;
    default:
      $caption = '';
  }
  // If our custom checkbox is used, overwrite caption.
  if (!empty($settings['use_image_caption_field'])) {
    if (!empty($item['image_field_caption']['value'])) {
      $caption = $item['image_field_caption']['value'];
    }
  }
  // Shorten the caption for the example styles or when caption shortening is active.
  $colorbox_style = variable_get('colorbox_style', 'default');
  $trim_length = variable_get('colorbox_caption_trim_length', 75);
  if (((strpos($colorbox_style, 'colorbox/example') !== FALSE) || variable_get('colorbox_caption_trim', 0)) && (drupal_strlen($caption) > $trim_length)) {
    $caption = drupal_substr($caption, 0, $trim_length - 5) . '...';
  }
  // Build the gallery id.
  list($id, $vid, $bundle) = entity_extract_ids($entity_type, $entity);
  $entity_id = !empty($id) ? $entity_type . '-' . $id : 'entity-id';
  switch ($settings['colorbox_gallery']) {
    case 'post':
      $gallery_id = 'gallery-' . $entity_id;
      break;
    case 'page':
      $gallery_id = 'gallery-all';
      break;
    case 'field_post':
      $gallery_id = 'gallery-' . $entity_id . '-' . $field['field_name'];
      break;
    case 'field_page':
      $gallery_id = 'gallery-' . $field['field_name'];
      break;
    case 'custom':
      $gallery_id = $settings['colorbox_gallery_custom'];
      break;
    default:
      $gallery_id = '';
  }
  if ($style_name = $settings['colorbox_image_style']) {
    $path = image_style_url($style_name, $image['path']);
  }
  else {
    $path = file_create_url($image['path']);
  }
  return theme('colorbox_imagefield', array(
    'image' => $image,
    'path' => $path,
    'title' => $caption,
    'gid' => $gallery_id,
    'entity' => $entity,
    'colorbox_style' => $style_name,
  ));
}
/**
 * @see theme_colorbox_imagefield().
 * @see colorbox_handler_field_colorbox.
 */
function vesafe_frontend_colorbox_imagefield($variables) {
  // Load the necessary js file for Colorbox activation.
  if (_colorbox_active() && !variable_get('colorbox_inline', 0)) {
    drupal_add_js(drupal_get_path('module', 'colorbox') . '/js/colorbox_inline.js');
  }
  if ($variables['image']['style_name'] == 'hide') {
    $image = '';
    $class[] = 'js-hide';
  }
  elseif (!empty($variables['image']['style_name'])) {
    $image = theme('image_style', $variables['image']);
  }
  else {
    $image = theme('image', $variables['image']);
  }
  $image_vars = array(
    'style_name' => $variables['colorbox_style'],
    'path' => $variables['image']['path'],
    'alt' => $variables['entity']->title,
  );
  $popup = theme('image_style', $image_vars);
  $caption = $variables['title'] . hwc_news_share_widget($variables['entity'], array('type' => 'article', 'label' => t('Share this gallery')));

  $width = 'auto';
  $height = 'auto';
  $gallery_id = $variables['gid'];
  $link_options = drupal_parse_url($variables['image']['path']);
  $link_options = array_merge($link_options, array(
    'html' => TRUE,
    'fragment' => 'colorbox-inline-' . md5($variables['image']['path']),
    'query' => array(
      'width' => $width,
      'height' => $height,
      'title' => $caption,
      'inline' => 'true'
    ),
    'attributes' => array(
      'class' => array('colorbox-inline'),
      'rel' => $gallery_id
    )
  ));
  // Remove any parameters that aren't set.
  $link_options['query'] = array_filter($link_options['query']);
  $link_tag = l($image, $variables['path'], $link_options);
  return $link_tag . '<div style="display: none;"><div id="colorbox-inline-' . md5($variables['image']['path']) . '">' . $popup . '</div></div>';
}

/**
 * @see theme_flickr_photoset.
 */
function vesafe_frontend_flickr_photoset($variables) {
  $photoset = $variables['photoset'];
  $owner = $variables['owner'];
  $size = $variables['size'];
  $media = isset($variables['media']) ? $variables['media'] : 'photos';
  $attribs = $variables['attribs'];
  $min_title = $variables['min_title'];
  $min_metadata = $variables['min_metadata'];
  $settings = $variables['settings'];
  $wrapper_class = $settings['image_class'];
  $variables['wrapper_class'] = $settings['image_class'];
  $output = '';
  $attribs['class'] = (!empty($attribs['class'])) ? $attribs['class'] . ' img-responsive' : 'img-responsive';
  if (module_exists('flickr_sets')) {
    $output = "<div class='flickr-photoset'>\n";
    $per_page = $settings['images_shown'];
    $photos = flickr_photosets_getphotos($photoset['id'], array(
      'per_page' => $per_page,
      'media' => $media,
    ));
    if ($photos['photoset']['total']) {
      foreach ((array) $photos['photoset']['photo'] as $photo) {
        // Insert owner into $photo because theme_flickr_photo needs it.
        $photo['owner'] = $owner;
        $output .= theme('flickr_photo', array(
          'photo' => $photo,
          'size' => $size,
          'format' => NULL,
          'attribs' => $attribs,
          'min_title' => $variables['min_title'],
          'min_metadata' => $variables['min_metadata'],
          'wrapper_class' => $wrapper_class,
        ));
      }
      if ($photos['photoset']['total'] > count($photos['photoset']['photo'])) {
        $output .= l(t('View all'), flickr_photoset_page_url($owner, $photoset['id']), array('attributes' => array('target' => '_blank')));
      }
    }
    else {
      $output .= t('No media in this set.');
    }
  }
  else {
    $img = flickr_img($photoset, $size, $attribs);
    $output = theme('pager');
    $photo_url = flickr_photoset_page_url($owner, $photoset['id']);
    $output .= "<div class='flickr-photoset" . $wrapper_class . "'>";
    $title = is_array($photoset['title']) ? $photoset['title']['_content'] : $photoset['title'];
    return l($img, $photo_url, array(
      'attributes' => array(
        'title' => $title),
      'absolute' => TRUE,
      'html' => TRUE,
    ));
  }
  $output .= '</div>';
  return $output;
}
/**
 * Anchor to top of the page
 */
function vesafe_frontend_top_anchor(&$vars) {
  $options = array(
    'attributes' => array(
      'class' => 'top_anchor',
    ),
    'external' => TRUE,
    'fragment' => 'top',
    'html' => TRUE,
  );
  $vars['top_anchor'] = l('<img alt="Anchor to top" src="'.file_create_url(path_to_theme().'/images/anchor-top.png').'" />', '', $options);
}

function vesafe_frontend_qt_quicktabs_tabset($vars) {
  $variables = array(
    'attributes' => array(
      'class' => array('quicktabs-tabs quicktabs-style-' . $vars['tabset']['#options']['style'], 'container'),
    ),
    'items' => array(),
  );
  foreach (element_children($vars['tabset']['tablinks']) as $key) {
    $item = array();
    if (is_array($vars['tabset']['tablinks'][$key])) {
      $tab = $vars['tabset']['tablinks'][$key];
      if ($key == $vars['tabset']['#options']['active']) {
        $item['class'] = array('active');
      }
      $tab['#options']['html'] = TRUE;
      $item['data'] = drupal_render($tab);
      $variables['items'][] = $item;
    }
  }
  $ul = theme('item_list', $variables);
  return '<div class="quicktabs-tabs-container">' . $ul . '</div>';
}

/**
 * Overrides theme_form_element_label().
 */
function vesafe_frontend_form_element_label(&$variables) {
  $element = $variables['element'];

  // This is also used in the installer, pre-database setup.
  $t = get_t();

  // Determine if certain things should skip for checkbox or radio elements.
  $skip = (isset($element['#type']) && ('checkbox' === $element['#type'] || 'radio' === $element['#type']));

  // If title and required marker are both empty, output no label.
  if ((!isset($element['#title']) || $element['#title'] === '' && !$skip) && empty($element['#required'])) {
    return '';
  }

  // If the element is required, a required marker is appended to the label.
  $required = !empty($element['#required']) ? theme('form_required_marker', array('element' => $element)) : '';

  $title = filter_xss_admin($element['#title']);

  $attributes = array();

  // Style the label as class option to display inline with the element.
  if ($element['#title_display'] == 'after' && !$skip) {
    $attributes['class'][] = $element['#type'];
  }
  // Show label only to screen readers to avoid disruption in visual flows.
  elseif ($element['#title_display'] == 'invisible') {
    $attributes['class'][] = 'element-invisible';
  }

  $skip_for = in_array($element['#type'], ['checkboxes']);
  if (!empty($element['#id']) && !$skip_for) {
    $attributes['for'] = $element['#id'];
  }

  // Insert radio and checkboxes inside label elements.
  $output = '';
  if (isset($variables['#children'])) {
    $output .= $variables['#children'];
  }

  // Append label.
  $output .= $t('!title !required', array('!title' => $title, '!required' => $required));

  // The leading whitespace helps visually separate fields from inline labels.
  return ' <label' . drupal_attributes($attributes) . '>' . $output . "</label>\n";
}

/**
 * Implements hook_block_view_alter.
 */
function vesafe_frontend_block_view_alter(&$data, $block){
  switch ($block->title){
    case 'Vehicles Facet':
    case 'Risks Facet':
      $items = array();
      foreach ($data['content']['facets']['#items'] as $item) {
        $text =  preg_replace('/<a href=\"(.*)\">(.*)\<span class=\"(.*)\">(.*)\<\/span\><\/a>/iU','$2',$item['data']);
        list($name,$count) = explode('(',$text);
        $items[(trim($name))] = preg_replace_callback('/<a href=\"(.*)\">(.*)\<span class=\"(.*)\">(.*)\<\/span\><\/a>/iU',
          function($m) {
            list($name,$count) = explode('(',$m[2]);
            return '<a href="' . str_replace(['[',']'],['%5B','%5D'],$m[1]) . '">' . $name . '</a>';
          },
          $item['data']);
      }
      ksort($items);
      $new_data = array();
      foreach($items as $i){
        $new_data[] = $i;
      }
      $data['content']['facets']['#items'] = $new_data;
      break;
  }
}

function vesafe_frontend_captcha($variables) {
  $element = $variables['element'];

  $element['captcha_widgets']['captcha_response']['#prefix'] = '<label for="security_code" class="security-code-captcha">' . $element['captcha_widgets']['captcha_response']['#title'] . '</label>';
  unset($element['captcha_widgets']['captcha_response']['#title']);

  if (!empty($element['#description']) && isset($element['captcha_widgets'])) {
    $captcha_holder = array(
      '#type' => 'container',
      '#title' => t('CAPTCHA'),
      '#description' => $element['#description'],
      '#children' => drupal_render_children($element),
      '#attributes' => array('class' => array('captcha')),
    );
    return drupal_render($captcha_holder);
  }
  else {
    return '<div class="captcha">' . drupal_render_children($element) . '</div>';
  }
}
