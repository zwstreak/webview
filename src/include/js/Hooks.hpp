#ifndef WEBVIEW_JS_HOOKS_HPP
#define WEBVIEW_JS_HOOKS_HPP
#include <quickjs.h>

#define JS_PARAMS JSContext* ctx, JSValue this_val, int argc, JSValue* argv
#define JS_HOOK_CONSOLE(member) hooks::console::member(JS_PARAMS)
#define JS_HOOK_DOCUMENT(member) hooks::document::member(JS_PARAMS)
#define JS_HOOK_GLOBAL(member) hooks::global::member(JS_PARAMS)

class JSEngine;
class JSHooks {
private:
	static void registerGlobal(JSEngine* engine, JSContext* ctx);
	static void registerDocument(JSEngine* engine, JSContext* ctx);
	static void registerWindow(JSEngine* engine, JSContext* ctx);
	static void registerConsole(JSEngine* engine, JSContext* ctx);
public:
	static void registerHooks(JSEngine* engine, JSContext* ctx);
};

#endif