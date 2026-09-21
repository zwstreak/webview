#ifndef WEBVIEW_JS_ENGINE_HPP
#define WEBVIEW_JS_ENGINE_HPP
#include <include/renderer/WebviewNodes.hpp>
#include <quickjs.h>

class JSEngine {
public:
	// TODO: move the class IDS to a seperate class
	static JSClassID element_id;
	static JSClassID collection_id;
	static JSClassID document_id;
	static JSClassID console_id;
	static JSClassID window_id;
	static JSClassID engine_id;

	WebviewNodes* getNodes();
	void execute(std::string script);
	void init();
	void free();
	JSEngine(WebviewNodes* nodes);
private:
	JSRuntime* runtime;
	JSContext* ctx;
	WebviewNodes* _nodes;
};

#endif