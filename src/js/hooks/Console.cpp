#include <include/js/hooks/Console.hpp>

JSValue JS_HOOK_CONSOLE(log) {
	for (int i = 0; i < argc; i++) {
		const char* str = JS_ToCString(ctx, argv[i]);
		if (!str) continue;

		geode::log::debug("[console.log] {}", str);
		JS_FreeCString(ctx, str);
	}

	return JS_UNDEFINED;
}