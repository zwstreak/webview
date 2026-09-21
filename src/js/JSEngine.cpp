#include <include/js/JSEngine.hpp>
#include <include/js/Hooks.hpp>
#include <include/js/bindings/HTMLCollection.hpp>

JSClassID JSEngine::element_id = 0;
JSClassID JSEngine::collection_id = 0;
JSClassID JSEngine::document_id = 0;
JSClassID JSEngine::window_id = 0;
JSClassID JSEngine::console_id = 0;

WebviewRenderer* JSEngine::getRenderer() {
	return this->_renderer;
}

WebviewNodes* JSEngine::getNodes() {
	return this->getRenderer()->getNodes();
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

	JSClassDef element_def = { .class_name = "Element" };
	JSClassDef document_def = { .class_name = "Document" };
	JSClassDef console_def = { .class_name = "Console" };
	JSClassDef window_def = { .class_name = "Window" };
	JSClassDef collection_def = { 
		.class_name = "HTMLCollection",
		.finalizer = HTMLCollection_finalizer
	};

	JS_NewClassID(this->runtime, &JSEngine::element_id);
	JS_NewClassID(this->runtime, &JSEngine::collection_id);
	JS_NewClassID(this->runtime, &JSEngine::document_id);
	JS_NewClassID(this->runtime, &JSEngine::window_id);
	JS_NewClassID(this->runtime, &JSEngine::console_id);

	JS_NewClass(this->runtime, JSEngine::element_id, &element_def);
	JS_NewClass(this->runtime, JSEngine::collection_id, &collection_def);
	JS_NewClass(this->runtime, JSEngine::document_id, &document_def);
	JS_NewClass(this->runtime, JSEngine::window_id, &window_def);
	JS_NewClass(this->runtime, JSEngine::console_id, &console_def);

	JSHooks::registerHooks(this, this->ctx);
}

void JSEngine::storeOpaque(JSOpaque* opaque) {
	this->opaque_pool.push_back(opaque);
}

JSOpaque* JSOpaque_new(void* data, JSEngine* engine) {
	JSOpaque* ptr = new JSOpaque(data, engine);
	engine->storeOpaque(ptr);
	return ptr;
}

void JSEngine::free() {
	for (auto& opaque : this->opaque_pool) {
		if (opaque == nullptr) continue;
		delete opaque;
	}

	JS_FreeContext(this->ctx);
	JS_FreeRuntime(this->runtime);
	delete this;
}

JSEngine::JSEngine(WebviewRenderer* renderer) {
	this->_renderer = renderer;
	this->init();
}