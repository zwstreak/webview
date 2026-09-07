#ifndef WEBVIEW_JS_HOOKS_HPP
#define WEBVIEW_JS_HOOKS_HPP
#include <quickjs.h>

class JSHooks {
private:
	static void registerConsole(JSContext* ctx);
public:
	static void registerHooks(JSContext* ctx);
};

#endif