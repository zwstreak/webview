#ifndef WEBVIEW_JS_HOOKS_CONSOLE_HPP
#define WEBVIEW_JS_HOOKS_CONSOLE_HPP
#include "Include.hpp"

namespace hooks::console {
	JSValue log(JS_PARAMS);
	JSValue warn(JS_PARAMS);
	JSValue error(JS_PARAMS);
}

#endif