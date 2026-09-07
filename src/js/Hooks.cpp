#include <include/js/Hooks.hpp>
#include <include/js/hooks/Console.hpp>

void JSHooks::registerConsole(JSContext* ctx) {
	JSValue global = JS_GetGlobalObject(ctx);
	JSValue console = JS_NewObject(ctx);
	JS_SetPropertyStr(ctx, console, "log", JS_NewCFunction(ctx, hooks::console::log, "log", 1));
	JS_SetPropertyStr(ctx, global, "console", console);
	JS_FreeValue(ctx, global);
}

void JSHooks::registerHooks(JSContext* ctx) {
	JSHooks::registerConsole(ctx);
}