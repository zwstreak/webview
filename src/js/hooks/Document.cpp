#include <include/js/hooks/Document.hpp>
#include <include/js/bindings/Element.hpp>
#include <include/js/bindings/HTMLCollection.hpp>
#include <include/js/JSEngine.hpp>
#include <include/js/JSUtils.hpp>
#include <include/js/Directives.hpp>

JSValue JS_HOOK_DOCUMENT(getElementById) {
	if (argc < 1) {
		return JS_ThrowTypeError(ctx, "expected \"id\" argument.");
	}

	JSEngine* engine = GET_ENGINE(document, engine);
	std::string id = getJSString(ctx, argv[0]);
	std::optional<Node*> optNode = engine->getNodes()->getById(id);
	if (optNode == std::nullopt) {
		return JS_UNDEFINED;
	}

	Node* node = optNode.value();
	return JS_NewElementFromNode(engine, ctx, node);
}

JSValue JS_HOOK_DOCUMENT(getElementsByClassName) {
	if (argc < 1) {
		return JS_ThrowTypeError(ctx, "expected \"names\" argument.");
	}

	JSEngine* engine = GET_ENGINE(document, engine);
	std::string names = getJSString(ctx, argv[0]);
	std::vector<Node*> nodes = engine->getNodes()->getByClassName(names);
	std::vector<NodeID> ids = {};
	for (auto& n : nodes) {
		ids.push_back(n->location);
	}

	return JS_NewHTMLCollection(engine, ctx, ids);
}

JSValue JS_HOOK_DOCUMENT(getElementsByTagName) {
	if (argc < 1) {
		return JS_ThrowTypeError(ctx, "expected \"tag\" argument.");
	}

	JSEngine* engine = GET_ENGINE(document, engine);
	std::string tag = getJSString(ctx, argv[0]);
	std::vector<Node*> nodes = engine->getNodes()->getByTagName(tag);
	std::vector<NodeID> ids = {};
	for (auto& n : nodes) {
		ids.push_back(n->location);
	}

	return JS_NewHTMLCollection(engine, ctx, ids);
}