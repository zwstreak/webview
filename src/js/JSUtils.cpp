#include <include/js/JSUtils.hpp>
#include <include/renderer/WebviewRenderer.hpp>
#include <include/js/JSEngine.hpp>
#include <fmt/format.h>

std::string stringifyHTMLChildren(JSEngine* engine, std::vector<NodeID> children) {
	std::string result = "";
	for (auto& child : children) {
		result += stringifyHTML(engine, child);
	}

	return result;
}

std::string stringifyHTML(JSEngine* engine, NodeID loc) {
	Node* node = engine->getNodes()->get(loc);
	if (node->type == DOM_TEXT) {
		return trim(node->content);
	}

	std::string children = "";
	for (auto& child : node->childrenNodes) {
		children += stringifyHTML(engine, child);
	}

	return fmt::format("<{0}>{1}</{0}>", node->tagName, children);
}

std::string getJSString(JSContext* ctx, JSValue value) {
	const char* cstr = JS_ToCString(ctx, value);
	std::string str = std::string(cstr);
	JS_FreeCString(ctx, cstr);
	return str;
}