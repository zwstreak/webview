#include <include/js/hooks/Document.hpp>
#include <include/js/Element.hpp>
#include <include/js/JSEngine.hpp>

JSValue JS_HOOK_DOCUMENT(getElementById) {
	if (argc != 1) {
		return JS_EXCEPTION;
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