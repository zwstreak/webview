#include <include/js/JSEngine.hpp>
#include <include/js/Hooks.hpp>

JSClassID JSEngine::element_id = 0;
JSEngine* JSEngine::_instance = nullptr;
JSEngine* JSEngine::get() {
	return JSEngine::_instance;
}

WebviewNodes* JSEngine::getNodes() {
	return JSEngine::get()->nodes;
}

void JSEngine::execute(std::string script) {
	JSValue value = JS_Eval(this->ctx, script.c_str(), script.length(), "script.js", JS_EVAL_TYPE_GLOBAL);
	if (JS_IsException(value)) {
		JSValue exception = JS_GetException(ctx);
		const char* msg = JS_ToCString(ctx, exception);
		geode::log::error("{}", msg);
		JS_FreeCString(ctx, msg);
	}

	JS_FreeValue(this->ctx, value);
}

void JSEngine::init() {
	this->runtime = JS_NewRuntime();
	this->ctx = JS_NewContext(runtime);

	JS_NewClassID(this->runtime, &JSEngine::element_id);
	JSClassDef element_def = { .class_name = "Element" };
	JS_NewClass(this->runtime, JSEngine::element_id, &element_def);

	JSHooks::registerHooks(this->ctx);
}

void JSEngine::free() {
	JS_FreeContext(this->ctx);
	JS_FreeRuntime(this->runtime);
	JSEngine::_instance = nullptr;
	delete this;
}

JSEngine::JSEngine(WebviewNodes* nodes) {
	if (JSEngine::_instance != nullptr) {
		geode::log::error("instance of JSEngine already exists.");
		return;
	}

	JSEngine::_instance = this;
	this->nodes = nodes;
	this->init();
}