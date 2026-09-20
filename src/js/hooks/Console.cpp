#include <include/js/hooks/Console.hpp>
#include <functional>

JSValue consoleMethod(JSContext* ctx, int argc, JSValue* argv, std::function<void(std::string str)> fn) {
	std::string out = "";
	for (int i = 0; i < argc; i++) {
		const char* str = JS_ToCString(ctx, argv[i]);
		if (!str) continue;
		out += str;
		JS_FreeCString(ctx, str);
	}

	fn(out);
	return JS_UNDEFINED;
}

JSValue JS_HOOK_CONSOLE(log) {
	return consoleMethod(ctx, argc, argv, [](std::string str) {
		geode::log::info("{} (CONSOLE)", str);
	});
}

JSValue JS_HOOK_CONSOLE(warn) {
	return consoleMethod(ctx, argc, argv, [](std::string str) {
		geode::log::warn("{} (CONSOLE)", str);
	});
}

JSValue JS_HOOK_CONSOLE(error) {
	return consoleMethod(ctx, argc, argv, [](std::string str) {
		geode::log::error("{} (CONSOLE)", str);
	});
}