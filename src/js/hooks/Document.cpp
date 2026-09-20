#include <include/js/hooks/Document.hpp>
#include <include/js/bindings/Element.hpp>
#include <include/js/JSEngine.hpp>
#include <include/js/Utils.hpp>

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

	std::string names = getJSString(ctx, argv[0]);
	std::vector<Node*> nodes = JSEngine::get()->nodes->getByClassName(names);
	JSValue array = JS_NewArray(ctx);
	for (size_t i = 0; i < nodes.size(); i++) {
		JSValue obj = JS_NewElementFromNode(ctx, nodes[i]);
		JS_SetPropertyInt64(ctx, array, i, obj);
	}

	return array;
}

JSValue JS_HOOK_DOCUMENT(getElementsByTagName) {
	if (argc < 1) {
		return JS_ThrowTypeError(ctx, "expected \"tag\" argument.");
	}

	std::string tag = getJSString(ctx, argv[0]);
	std::vector<Node*> nodes = JSEngine::get()->nodes->getByTagName(tag);
	JSValue array = JS_NewArray(ctx);
	for (size_t i = 0; i < nodes.size(); i++) {
		JSValue obj = JS_NewElementFromNode(ctx, nodes[i]);
		JS_SetPropertyInt64(ctx, array, i, obj);
	}

	return array;
}