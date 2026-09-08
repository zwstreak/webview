#include <include/js/hooks/Document.hpp>
#include <include/js/Element.hpp>
#include <include/js/JSEngine.hpp>

JSValue JS_HOOK_DOCUMENT(getElementById) {
	if (argc < 1) {
		return JS_ThrowTypeError(ctx, "expected \"id\" argument.");
	}

	const char* id = JS_ToCString(ctx, argv[0]);
	auto optNode = JSEngine::get()->nodes->getById(id);
	JS_FreeCString(ctx, id);
	
	if (optNode == std::nullopt) {
		return JS_UNDEFINED;
	}

	Node* node = optNode.value();
	return JS_NewElementFromNode(ctx, node);
}

JSValue JS_HOOK_DOCUMENT(getElementsByClassName) {
	if (argc < 1) {
		return JS_ThrowTypeError(ctx, "expected \"names\" argument.");
	}

	const char* names = JS_ToCString(ctx, argv[0]);
	auto nodes = JSEngine::get()->nodes->getByClassName(names);
	JS_FreeCString(ctx, names);

	JSValue array = JS_NewArray(ctx);
	for (size_t i = 0; i < nodes.size(); i++) {
		JSValue obj = JS_NewElementFromNode(ctx, nodes[i]);
		JS_SetPropertyInt64(ctx, array, i, obj);
	}

	return array;
}