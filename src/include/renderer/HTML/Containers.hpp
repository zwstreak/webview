#ifndef WEBVIEW_RENDERER_HTML_CONTAINERS_HPP
#define WEBVIEW_RENDERER_HTML_CONTAINERS_HPP
#include "Include.hpp"

AxisLayout* html_container_get_default_layout();
void html_container_set_layout_default(CCNode* node, bool webview = false, float offset = 0.0f);
bool html_element_is_container(Element data);
CCNode* html_transpile_container(Element data);

#endif