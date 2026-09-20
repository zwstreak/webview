#include <include/js/hooks/Document.hpp>
#include <include/js/bindings/Element.hpp>
#include <include/js/bindings/HTMLCollection.hpp>
#include <include/js/JSEngine.hpp>
#include <include/js/JSUtils.hpp>

JSValue JS_HOOK_DOCUMENT(getElementById) {
	if (argc < 1) {
		return JS_ThrowTypeError(ctx, "expected \"id\" argument.");
	}

	std::string id = getJSString(ctx, argv[0]);
	auto optNode = JSEngine::get()->nodes->getById(id);
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

	JSEngine* engine = JSEngine::get();
	if (engine == nullptr) {
		return JS_ThrowTypeError(ctx, "could not get the JS engine.");
	}

	std::string names = getJSString(ctx, argv[0]);
	std::vector<Node*> nodes = engine->nodes->getByClassName(names);
	std::vector<NodeID> ids = {};
	for (auto& n : nodes) {
		ids.push_back(n->location);
	}

	return JS_NewHTMLCollection(ctx, ids);
}

JSValue JS_HOOK_DOCUMENT(getElementsByTagName) {
	if (argc < 1) {
		return JS_ThrowTypeError(ctx, "expected \"tag\" argument.");
	}

	JSEngine* engine = JSEngine::get();
	if (engine == nullptr) {
		return JS_ThrowTypeError(ctx, "could not get the JS engine.");
	}

	std::string tag = getJSString(ctx, argv[0]);
	std::vector<Node*> nodes = engine->nodes->getByTagName(tag);
	std::vector<NodeID> ids = {};
	for (auto& n : nodes) {
		ids.push_back(n->location);
	}

	return JS_NewHTMLCollection(ctx, ids);
}