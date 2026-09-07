#include <include/js/Hooks.hpp>

// format: JSHook_[obj]_[prop]_[prop]_...
JSValue JSHook_console_log(JSContext* ctx, JSValue this_val, int argc, JSValue* argv) {
	for (int i = 0; i < argc; i++) {
		const char* str = JS_ToCString(ctx, argv[i]);
		if (!str) continue;

		geode::log::debug("[console.log] {}", str);
		JS_FreeCString(ctx, str);
	}

	return JS_UNDEFINED;
}

void JSHooks::registerConsole(JSContext* ctx) {
	JSValue global = JS_GetGlobalObject(ctx);
	JSValue console = JS_NewObject(ctx);
	JS_SetPropertyStr(ctx, console, "log", JS_NewCFunction(ctx, JSHook_console_log, "log", 1));
	JS_SetPropertyStr(ctx, global, "console", console);
	JS_FreeValue(ctx, global);
}

void JSHooks::registerHooks(JSContext* ctx) {
	JSHooks::registerConsole(ctx);
}