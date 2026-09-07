#include <include/renderer/WebviewNodes.hpp>
#include <include/Utils.hpp>
#include <ranges>

// TODO: move RenderedNode to a separate file?
// RenderedNode //
std::string getTagName(lxb_tag_id_t tag) {
	size_t tag_len = 0;
	const lxb_char_t* tag_name = lxb_tag_name_by_id(tag, &tag_len);
	return stringFromLXBC(tag_name, tag_len);
}

RenderedNode::RenderedNode(Element element, cocos2d::CCNode* node) {
	this->node = node;
	this->classList = getClassList(element.attributes);
	this->id = getAttribute("id", element.attributes);
	this->tagName = getTagName(element.tag);
	this->attributes = element.attributes;
	this->tag = element.tag;
}

// WebviewNodes //
void WebviewNodes::add(RenderedNode node) {
	this->nodes.push_back(node);
}

std::optional<RenderedNode> WebviewNodes::getById(std::string id) {
	auto match = this->nodes
		| std::views::filter([&id](const RenderedNode& node) { return node.id == id; })
		| std::views::take(1);

	if (!match.empty()) {
		return match.front();
	}
	return std::nullopt;
}

std::vector<RenderedNode> WebviewNodes::getByClassName(std::string name) {
	return this->nodes
		| std::views::filter([&name](const RenderedNode& node) { return hasClassName(name, node.classList); })
		| std::ranges::to<std::vector>();
}

WebviewNodes::WebviewNodes() {
	this->nodes = {};
}