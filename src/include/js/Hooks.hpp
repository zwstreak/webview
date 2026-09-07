#ifndef WEBVIEW_JS_HOOKS_HPP
#define WEBVIEW_JS_HOOKS_HPP
#include <quickjs.h>

#define JS_PARAMS JSContext* ctx, JSValue this_val, int argc, JSValue* argv
#define JS_HOOK_CONSOLE(member) hooks::console::##member##(JS_PARAMS)
#define JS_HOOK_DOCUMENT(member) hooks::document::##member##(JS_PARAMS)

class JSHooks {
private:
	static void registerDocument(JSContext* ctx);
	static void registerConsole(JSContext* ctx);
public:
	static void registerHooks(JSContext* ctx);
};

#endif