#include <include/js/Utils.hpp>
#include <include/renderer/WebviewRenderer.hpp>
#include <include/js/JSEngine.hpp>

std::string stringifyHTMLChildren(std::vector<NodeID> children) {
	std::string result = "";
	for (auto& child : children) {
		result += stringifyHTML(child);
	}

	return result;
}

std::string stringifyHTML(NodeID loc) {
	Node* node = JSEngine::getNodes()->get(loc);
	if (node->type == DOM_TEXT) {
		return trim(node->content);
	}

	std::string children = "";
	for (auto& child : node->childrenNodes) {
		children += stringifyHTML(child);
	}

	return std::format("<{0}>{1}</{0}>", node->tagName, children);
}

std::string getJSString(JSContext* ctx, JSValue value) {
	const char* cstr = JS_ToCString(ctx, value);
	std::string str = std::string(cstr);
	JS_FreeCString(ctx, cstr);
	return str;
}