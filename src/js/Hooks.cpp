#include <include/js/Hooks.hpp>
#include <include/js/hooks/Console.hpp>
#include <include/js/hooks/Document.hpp>
#include <include/js/hooks/Global.hpp>
#include <include/js/JSEngine.hpp>

#define JS_HOOK_FUNC(category, name) JS_NewCFunction(ctx, hooks::category::name, #name, 1)

void JSHooks::registerGlobal(JSEngine* engine, JSContext* ctx) {
	JSValue global = JS_GetGlobalObject(ctx);
	JS_SetPropertyStr(ctx, global, "setTimeout", JS_HOOK_FUNC(global, setTimeout));
	JS_FreeValue(ctx, global);
}

void JSHooks::registerDocument(JSEngine* engine, JSContext* ctx) {
	JSValue global = JS_GetGlobalObject(ctx);
	JSValue document = JS_NewObjectClass(ctx, JSEngine::document_id);
	JS_SetOpaque(document, engine);
	JS_SetPropertyStr(ctx, document, "getElementById", JS_HOOK_FUNC(document, getElementById));
	JS_SetPropertyStr(ctx, document, "getElementsByClassName", JS_HOOK_FUNC(document, getElementsByClassName));
	JS_SetPropertyStr(ctx, document, "getElementsByTagName", JS_HOOK_FUNC(document, getElementsByTagName));
	JS_SetPropertyStr(ctx, global, "document", document);
	JS_FreeValue(ctx, global);
}

void JSHooks::registerWindow(JSEngine* engine, JSContext* ctx) {
	JSValue global = JS_GetGlobalObject(ctx);
	JSValue window = JS_NewObjectClass(ctx, JSEngine::window_id);
	JS_SetOpaque(window, engine);
	JS_SetPropertyStr(ctx, window, "document", JS_GetPropertyStr(ctx, global, "document"));
	JS_SetPropertyStr(ctx, global, "window", window);
	JS_FreeValue(ctx, global);
}

void JSHooks::registerConsole(JSEngine* engine, JSContext* ctx) {
	JSValue global = JS_GetGlobalObject(ctx);
	JSValue console = JS_NewObjectClass(ctx, JSEngine::console_id);
	JS_SetOpaque(console, engine);
	JS_SetPropertyStr(ctx, console, "log", JS_HOOK_FUNC(console, log));
	JS_SetPropertyStr(ctx, console, "warn", JS_HOOK_FUNC(console, warn));
	JS_SetPropertyStr(ctx, console, "error", JS_HOOK_FUNC(console, error));
	JS_SetPropertyStr(ctx, global, "console", console);
	JS_FreeValue(ctx, global);
}

void JSHooks::registerHooks(JSEngine* engine, JSContext* ctx) {
	JSHooks::registerGlobal(engine, ctx);
	JSHooks::registerConsole(engine, ctx);
	JSHooks::registerDocument(engine, ctx);
	JSHooks::registerWindow(engine, ctx);
}