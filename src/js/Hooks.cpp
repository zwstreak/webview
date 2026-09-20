#include <include/js/Hooks.hpp>
#include <include/js/hooks/Console.hpp>
#include <include/js/hooks/Document.hpp>
#include <include/js/hooks/Global.hpp>

#define JS_HOOK_FUNC(category, name) JS_NewCFunction(ctx, hooks::category::name, #name, 1)

void JSHooks::registerGlobal(JSContext* ctx) {
	JSValue global = JS_GetGlobalObject(ctx);
	JS_SetPropertyStr(ctx, global, "setTimeout", JS_HOOK_FUNC(global, setTimeout));
	JS_FreeValue(ctx, global);
}

void JSHooks::registerDocument(JSContext* ctx) {
	JSValue global = JS_GetGlobalObject(ctx);
	JSValue document = JS_NewObject(ctx);
	JS_SetPropertyStr(ctx, document, "getElementById", JS_HOOK_FUNC(document, getElementById));
	JS_SetPropertyStr(ctx, document, "getElementsByClassName", JS_HOOK_FUNC(document, getElementsByClassName));
	JS_SetPropertyStr(ctx, document, "getElementsByTagName", JS_HOOK_FUNC(document, getElementsByTagName));
	JS_SetPropertyStr(ctx, global, "document", document);
	JS_FreeValue(ctx, global);
}

void JSHooks::registerConsole(JSContext* ctx) {
	JSValue global = JS_GetGlobalObject(ctx);
	JSValue console = JS_NewObject(ctx);
	JS_SetPropertyStr(ctx, console, "log", JS_HOOK_FUNC(console, log));
	JS_SetPropertyStr(ctx, console, "warn", JS_HOOK_FUNC(console, warn));
	JS_SetPropertyStr(ctx, console, "error", JS_HOOK_FUNC(console, error));
	JS_SetPropertyStr(ctx, global, "console", console);
	JS_FreeValue(ctx, global);
}

void JSHooks::registerHooks(JSContext* ctx) {
	JSHooks::registerGlobal(ctx);
	JSHooks::registerConsole(ctx);
	JSHooks::registerDocument(ctx);
}