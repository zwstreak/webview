#ifndef WEBVIEW_RENDERER_HTML_TEXT_HPP
#define WEBVIEW_RENDERER_HTML_TEXT_HPP
#include "Include.hpp"

bool html_element_is_text(lxb_tag_id_t id);
CCNode* html_transpile_text(DOMNode element);
CCNode* html_create_text_node(DOMNode node);
void html_post_process_text(Node* node);

#endif