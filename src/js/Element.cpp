#include <include/js/Element.hpp>
#include <include/js/JSEngine.hpp>

#define ATOM_FLAGS (JS_PROP_HAS_GET | JS_PROP_HAS_SET | JS_PROP_CONFIGURABLE | JS_PROP_WRITABLE)

JSValue get_innerHTML(JS_PARAMS) {
	Node* node = static_cast<Node*>(JS_GetOpaque(this_val, JSEngine::element_id));
	if (node == nullptr) {
		return JS_ThrowTypeError(ctx, "expected a node object");
	}

	return JS_NewString(ctx, node->content.c_str());
}

JSValue set_innerHTML(JS_PARAMS) {
	Node* node = static_cast<Node*>(JS_GetOpaque(this_val, JSEngine::element_id));
	if (node == nullptr) {
		return JS_ThrowTypeError(ctx, "expected a node object");
	}

	const char* html = JS_ToCString(ctx, argv[0]);
	JS_FreeCString(ctx, html);
	return JS_UNDEFINED;
}

void define_innerHTML(JSContext* ctx, JSValue object) {
	JSAtom atom = JS_NewAtom(ctx, "innerHTML");
	JSValue getter = JS_NewCFunction(ctx, get_innerHTML, "get_innerHTML", 1);
	JSValue setter = JS_NewCFunction(ctx, set_innerHTML, "set_innerHTML", 1);
	JS_DefineProperty(ctx, object, atom, JS_UNDEFINED, getter, setter, ATOM_FLAGS);
	JS_FreeAtom(ctx, atom);
}

JSValue JS_NewElementFromNode(JSContext* ctx, Node* node) {
	JSValue object = JS_NewObjectClass(ctx, JSEngine::element_id);
	JS_SetOpaque(object, node);
	JS_SetPropertyStr(ctx, object, "id", JS_NewString(ctx, node->id.c_str()));
	define_innerHTML(ctx, object);

	return object;
}