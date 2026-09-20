#include <include/js/bindings/Element.hpp>
#include <include/js/JSEngine.hpp>
#include <include/renderer/HTML/Containers.hpp>
#include <include/js/Utils.hpp>
#include <format>
#include <ranges>

#define ATOM_RW_FLAGS (JS_PROP_HAS_GET | JS_PROP_HAS_SET | JS_PROP_WRITABLE)
#define ATOM_R_FLAGS (JS_PROP_HAS_GET)

#define CREATE_ELEMENT() \
	JS_NewObjectClass(ctx, JSEngine::element_id); \
	JS_SetOpaque(element, node)

#define CREATE_PROPERTY_RW(prop) \
	JSAtom atom_##prop = JS_NewAtom(ctx, #prop); \
	JSValue getter_##prop = JS_NewCFunction(ctx, get_##prop, "get " #prop, 1); \
	JSValue setter_##prop = JS_NewCFunction(ctx, set_innerHTML, "set " #prop, 1); \
	JS_DefineProperty(ctx, element, atom_##prop, JS_UNDEFINED, getter_##prop, setter_##prop, ATOM_RW_FLAGS); \
	JS_FreeAtom(ctx, atom_##prop)

#define CREATE_PROPERTY_R(prop) \
	JSAtom atom_##prop = JS_NewAtom(ctx, #prop); \
	JSValue getter_##prop = JS_NewCFunction(ctx, get_##prop, "get " #prop, 1); \
	JS_DefineProperty(ctx, element, atom_##prop, JS_UNDEFINED, getter_##prop, JS_UNDEFINED, ATOM_R_FLAGS); \
	JS_FreeAtom(ctx, atom_##prop)

#define GET_NODE() static_cast<Node*>(JS_GetOpaque(this_val, JSEngine::element_id)); \
	if (node == nullptr) { return JS_ThrowTypeError(ctx, "expected a node object"); } \
	JSEngine* engine = JSEngine::get(); \
	if (engine == nullptr) { return JS_ThrowTypeError(ctx, "could not get the JS engine."); }

// children //
JSValue get_children(JS_PARAMS) {
	Node* node = GET_NODE();
	for (auto& childId : node->childrenNodes) {
		Node* child = engine->nodes->get(childId);
	}
	return JS_ThrowTypeError(ctx, "not impl yet.");
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
	JSValue element = CREATE_ELEMENT();
	CREATE_PROPERTY_RW(innerHTML);
	CREATE_PROPERTY_R(children);

	return element;
}