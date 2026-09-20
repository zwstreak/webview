#include <include/js/Element.hpp>
#include <include/js/JSEngine.hpp>
#include <include/renderer/HTML/Containers.hpp>
#include <include/js/Utils.hpp>
#include <format>
#include <ranges>

#define ATOM_FLAGS (JS_PROP_HAS_GET | JS_PROP_HAS_SET | JS_PROP_CONFIGURABLE | JS_PROP_WRITABLE)
#define CREATE_PROPERTY(prop, obj) \
	JSAtom atom_##prop = JS_NewAtom(ctx, #prop); \
	JSValue getter = JS_NewCFunction(ctx, get_##prop, "get " #prop, 1); \
	JSValue setter = JS_NewCFunction(ctx, set_innerHTML, "set " #prop, 1); \
	JS_DefineProperty(ctx, obj, atom_##prop, JS_UNDEFINED, getter, setter, ATOM_FLAGS); \
	JS_FreeAtom(ctx, atom_##prop)

#define GET_NODE() static_cast<Node*>(JS_GetOpaque(this_val, JSEngine::element_id)); \
	if (node == nullptr) { \
		return JS_ThrowTypeError(ctx, "expected a node object"); \
	}

JSValue get_innerHTML(JS_PARAMS) {
	Node* node = GET_NODE();
	std::string html = stringifyHTMLChildren(node->childrenNodes);
	return JS_NewString(ctx, html.c_str());
}

JSValue set_innerHTML(JS_PARAMS) {
	Node* node = GET_NODE();
	WebviewRenderer* renderer = WebviewRenderer::get();
	JSEngine* engine = JSEngine::get();
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
	JSValue object = JS_NewObjectClass(ctx, JSEngine::element_id);
	JS_SetOpaque(object, node);
	CREATE_PROPERTY(innerHTML, object);

	return object;
}