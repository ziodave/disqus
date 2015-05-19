<?php

$plugin = array(
  'title' => t('Disqus Comments'),
  'description' => t('Display Disqus comment box in a pane'),
  'category' => t('Disqus'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'render callback' => 'disqus_ctools_comments_render',
);


function disqus_ctools_comments_render($subtype, $conf, $panel_args, $context) {
  if (!user_access('view disqus comments')) {
    return;
  }

  $node = $context->data;
  if (isset($node->disqus) && $node->disqus['status']) {
    $block = new stdClass();
    $block->module  = 'comments';
    $block->content = array('disqus' =>  array('#type' => 'disqus', '#disqus' => $node->disqus));
    $block->delta   = $node->nid;
    return $block;
   }
}