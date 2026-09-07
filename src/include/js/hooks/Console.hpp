#ifndef WEBVIEW_JS_HOOKS_CONSOLE_HPP
#define WEBVIEW_JS_HOOKS_CONSOLE_HPP
#include "Include.hpp"

namespace hooks::console {
	JSValue log(JS_HOOK_PARAMS);
	JSValue warn(JS_HOOK_PARAMS);
	JSValue error(JS_HOOK_PARAMS);
}

#endif