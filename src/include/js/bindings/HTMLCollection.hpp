#ifndef WEBVIEW_JS_BINDINGS_HTMLCOLLECTION_HPP
#define WEBVIEW_JS_BINDINGS_HTMLCOLLECTION_HPP
#include <quickjs.h>
#include <include/renderer/WebviewRenderer.hpp>
#include <include/js/Hooks.hpp>

struct CollectionHolder {
	std::vector<NodeID> data;
	CollectionHolder(const std::vector<NodeID>& data): data(data) {}
};

void HTMLCollection_finalizer(JSRuntime* rt, JSValue val);
JSValue JS_NewHTMLCollection(JSEngine* engine, JSContext* ctx, std::vector<NodeID> nodes);

#endif