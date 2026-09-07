#ifndef WEBVIEW_JS_ENGINE_HPP
#define WEBVIEW_JS_ENGINE_HPP
#include <include/renderer/WebviewNodes.hpp>

class JSEngine {
public:
	void execute(std::string script);
	JSEngine(WebviewNodes* nodes);
private:
	WebviewNodes* nodes;
};

#endif