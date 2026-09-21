#include <include/js/bindings/Element.hpp>
#include <include/js/bindings/HTMLCollection.hpp>
#include <include/js/JSEngine.hpp>
#include <include/renderer/HTML/Containers.hpp>
#include <include/js/JSUtils.hpp>
#include <include/js/Directives.hpp>
#include <ranges>

#define GET_NODE() GET_OPAQUE(element, node, Node*)

// children //
JSValue get_children(JS_PARAMS) {
	Node* node = GET_NODE();
	return JS_NewHTMLCollection(engine, ctx, node->childrenNodes);
}

// innerHTML //
JSValue get_innerHTML(JS_PARAMS) {
	Node* node = GET_NODE();
	std::string html = stringifyHTMLChildren(engine, node->childrenNodes);
	return JS_NewString(ctx, html.c_str());
}

JSValue set_innerHTML(JS_PARAMS) {
	Node* node = GET_NODE();
	std::string html = getJSString(ctx, argv[0]);
	std::vector<DOMNode> data = HTMLParser::parseFragment(html);
	
	engine->getNodes()->clearChildrenNodes(node->childrenNodes);
	for (auto& frag : data) {
		engine->getRenderer()->renderHTMLChild(frag, node->location);
	}
	
	node->cocos->updateLayout();
	return JS_UNDEFINED;
}

JSValue JS_NewElementFromNode(JSEngine* engine, JSContext* ctx, Node* node) {
	JSValue element = CREATE_OBJ_CLASS(element, node);
	CREATE_PROPERTY_RW(element, innerHTML);
	CREATE_PROPERTY_R(element, children);

	return element;
}