#ifndef WEBVIEW_JS_ENGINE_HPP
#define WEBVIEW_JS_ENGINE_HPP
#include <include/renderer/WebviewNodes.hpp>
#include <quickjs.h>

class JSEngine {
public:
	void execute(std::string script);
	void init();
	void free();
	JSEngine(WebviewNodes* nodes);
private:
	WebviewNodes* nodes;
	JSRuntime* runtime;
	JSContext* ctx;
};

#endif