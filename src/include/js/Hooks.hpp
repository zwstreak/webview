#ifndef WEBVIEW_JS_HOOKS_HPP
#define WEBVIEW_JS_HOOKS_HPP
#include <quickjs.h>

#define JS_HOOK_PARAMS JSContext* ctx, JSValue this_val, int argc, JSValue* argv
#define JS_HOOK_CONSOLE(member) hooks::console::##member##(JS_HOOK_PARAMS)

class JSHooks {
private:
	static void registerConsole(JSContext* ctx);
public:
	static void registerHooks(JSContext* ctx);
};

#endif