#ifndef WEBVIEW_JS_UTILS_HPP
#define WEBVIEW_JS_UTILS_HPP
#include <include/Utils.hpp>
#include <include/renderer/WebviewNodes.hpp>
#include <quickjs.h>

// utility functions that are specific to the JS runtime
std::string stringifyHTMLChildren(std::vector<Node*> children);
std::string stringifyHTML(Node* node);
std::string getJSString(JSContext* ctx, JSValue value);

#endif