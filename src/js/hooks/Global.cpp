#include <include/js/hooks/Global.hpp>
#include <include/Utils.hpp>
#include <thread>

JSValue JS_HOOK_GLOBAL(setTimeout) {
	if (argc < 2) {
		return JS_ThrowTypeError(ctx, "expected at least 2 arguments got %d instead.", argc);
	}

	if (!JS_IsFunction(ctx, argv[0])) {
		return JS_ThrowTypeError(ctx, "first argument must be a function.");
	}

	JSValue callback = JS_DupValue(ctx, argv[0]);
	double delay = 0;
	if (JS_ToFloat64(ctx, &delay, argv[1]) < 0) {
		JS_FreeValue(ctx, callback);
		return JS_ThrowTypeError(ctx, "second argument must be a valid number.");
	}

	sleep(delay, [&ctx, &callback]() {
		JSValue ret = JS_Call(ctx, callback, JS_UNDEFINED, 0, nullptr);
		JS_FreeValue(ctx, ret);
		JS_FreeValue(ctx, callback);
	});

	return JS_UNDEFINED;
}