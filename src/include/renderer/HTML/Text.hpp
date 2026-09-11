#ifndef WEBVIEW_RENDERER_HTML_TEXT_HPP
#define WEBVIEW_RENDERER_HTML_TEXT_HPP
#include "Include.hpp"

bool html_element_is_text(DOMNode element);
CCNode* html_transpile_text(DOMNode element);

#endif