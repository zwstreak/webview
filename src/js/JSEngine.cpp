#include <include/js/JSEngine.hpp>
#include <include/js/Hooks.hpp>

void JSEngine::execute(std::string script) {
	const char* code = "console.log('Hello world!');\nconsole.warn('Please no');\nconsole.error('Oop!');";
	JSValue value = JS_Eval(this->ctx, code, std::strlen(code), "test.js", JS_EVAL_TYPE_GLOBAL);
	JS_FreeValue(this->ctx, value);
}

void JSEngine::init() {
	this->runtime = JS_NewRuntime();
	this->ctx = JS_NewContext(runtime);
	JSHooks::registerHooks(this->ctx);
}

void JSEngine::free() {
	JS_FreeContext(this->ctx);
	JS_FreeRuntime(this->runtime);
	delete this;
}

JSEngine::JSEngine(WebviewNodes* nodes) {
	this->nodes = nodes;
	this->init();
}