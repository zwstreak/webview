#include <include/js/bindings/Element.hpp>
#include <include/js/bindings/HTMLCollection.hpp>
#include <include/js/JSEngine.hpp>
#include <include/renderer/HTML/Containers.hpp>
#include <include/js/JSUtils.hpp>
#include <include/js/Directives.hpp>
#include <format>
#include <ranges>

#define GET_NODE() GET_OPAQUE(element, node, Node*)

// children //
JSValue get_children(JS_PARAMS) {
	Node* node = GET_NODE();
	return JS_NewHTMLCollection(ctx, node->childrenNodes);
}

// innerHTML //
JSValue get_innerHTML(JS_PARAMS) {
	Node* node = GET_NODE();
	std::string html = stringifyHTMLChildren(node->childrenNodes);
	return JS_NewString(ctx, html.c_str());
}

JSValue set_innerHTML(JS_PARAMS) {
	Node* node = GET_NODE();
	WebviewRenderer* renderer = WebviewRenderer::get();
	if (engine == nullptr || renderer == nullptr) {
		return JS_ThrowSyntaxError(ctx, "could not set innerHTML");
	}

	std::string html = getJSString(ctx, argv[0]);
	std::vector<DOMNode> data = HTMLParser::parseFragment(html);
	engine->nodes->clearChildrenNodes(node->childrenNodes);
	for (auto& frag : data) {
		renderer->renderHTMLChild(frag, node->location);
	}
	
	node->cocos->updateLayout();
	return JS_UNDEFINED;
}

JSValue JS_NewElementFromNode(JSContext* ctx, Node* node) {
	JSValue element = CREATE_OBJ_CLASS(element, node);
	CREATE_PROPERTY_RW(element, innerHTML);
	CREATE_PROPERTY_R(element, children);

	return element;
}