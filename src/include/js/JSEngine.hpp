#ifndef WEBVIEW_JS_ENGINE_HPP
#define WEBVIEW_JS_ENGINE_HPP
#include <include/renderer/WebviewNodes.hpp>
#include <quickjs.h>

class JSEngine;
struct JSOpaque {
	JSEngine* engine;
	void* data;

	JSOpaque(void* data, JSEngine* engine): data(data), engine(engine) {}
};

class WebviewRenderer;
class JSEngine {
public:
	// TODO: move the class IDS to a seperate class
	static JSClassID element_id;
	static JSClassID collection_id;
	static JSClassID document_id;
	static JSClassID console_id;
	static JSClassID window_id;

	WebviewNodes* getNodes();
	WebviewRenderer* getRenderer();
	void storeOpaque(JSOpaque* opaque);

	void execute(std::string script);
	void init();
	void free();
	JSEngine(WebviewRenderer* renderer);
private:
	std::vector<JSOpaque*> opaque_pool;
	JSRuntime* runtime;
	JSContext* ctx;
	WebviewRenderer* _renderer;
};

JSOpaque* JSOpaque_new(void* data, JSEngine* engine);

#endif