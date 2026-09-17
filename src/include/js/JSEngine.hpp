#ifndef WEBVIEW_JS_ENGINE_HPP
#define WEBVIEW_JS_ENGINE_HPP
#include <include/renderer/WebviewNodes.hpp>
#include <quickjs.h>

class JSEngine {
public:
	static JSEngine* get();
	static WebviewNodes* getNodes();
	static JSClassID element_id;
	WebviewNodes* nodes;

	void execute(std::string script);
	void init();
	void free();
	JSEngine(WebviewNodes* nodes);
private:
	static JSEngine* _instance;
	JSRuntime* runtime;
	JSContext* ctx;
};

#endif