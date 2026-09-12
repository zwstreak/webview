#ifndef WEBVIEW_RENDERER_HTML_HTML_HPP
#define WEBVIEW_RENDERER_HTML_HTML_HPP
#include "Include.hpp"

// going for C-style functions cuz classes are kinda unnecessary for this
CCNode* html_transpile_element(DOMNode element);
CCNode* html_transpile_node(DOMNode node);
void html_post_process(Node* node);

#endif