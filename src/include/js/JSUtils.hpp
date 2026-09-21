#ifndef WEBVIEW_JS_UTILS_HPP
#define WEBVIEW_JS_UTILS_HPP
#include <include/Utils.hpp>
#include <include/renderer/WebviewNodes.hpp>
#include <quickjs.h>

// utility functions that are specific to the JS runtime
std::string stringifyHTMLChildren(JSEngine* engine, std::vector<NodeID> children);
std::string stringifyHTML(JSEngine* engine, NodeID node);
std::string getJSString(JSContext* ctx, JSValue value);

#endif