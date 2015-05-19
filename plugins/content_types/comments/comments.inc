<?php

// Define the properties of the CTools plugin.
$plugin = array(
  'title'            => t('Disqus Comments'),
  'description'      => t('Display Disqus comment box in a pane'),
  'category'         => t('Disqus'),
  // The category will appear in the panel content selection screen.
  'required context' => new ctools_context_required(t('Node'), 'node'),
  // Tell CTools that we need the node context (comments will be bound to this node).
  'render callback'  => 'disqus_ctools_comments_render',
  // The callback function that CTool will call to render the plugin.
);


/**
 * This function is called by CTools to render the comments element (this function is set in the plugin configuration).
 *
 * @param object $context The node context, holding the currently selected node.
 */
function disqus_ctools_comments_render($subtype, $conf, $panel_args, $context) {

  // Return if the current user cannot view Disqus comments.
  if (!user_access('view disqus comments')) {
    return;
  }

  // Get the actual node and display the content block if Disqus is enabled.
  $node = $context->data;
  if (isset($node->disqus) && $node->disqus['status']) {
    $block          = new stdClass();
    $block->module  = 'comments';
    $block->content = array('disqus' => array('#type'   => 'disqus',
                                              '#disqus' => $node->disqus
    )
    );
    $block->delta   = $node->nid;
    return $block;
  }
}