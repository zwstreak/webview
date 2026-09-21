#ifndef WEBVIEW_JS_BINDINGS_ELEMENT_HPP
#define WEBVIEW_JS_BINDINGS_ELEMENT_HPP
#include <quickjs.h>
#include <include/renderer/WebviewRenderer.hpp>
#include <include/js/Hooks.hpp>

JSValue JS_NewElementFromNode(JSEngine* engine, JSContext* ctx, Node* node);

#endif