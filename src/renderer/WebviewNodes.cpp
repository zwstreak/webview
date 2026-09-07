#include <include/renderer/WebviewNodes.hpp>
#include <include/Utils.hpp>
#include <ranges>

// TODO: move Node to a separate file?
// Node //
std::string getTagName(lxb_tag_id_t tag) {
	size_t tag_len = 0;
	const lxb_char_t* tag_name = lxb_tag_name_by_id(tag, &tag_len);
	return stringFromLXBC(tag_name, tag_len);
}

Node::Node(Element element, cocos2d::CCNode* cocos) {
	this->cocos = cocos;
	this->classList = getClassList(element.attributes);
	this->id = getAttribute("id", element.attributes);
	this->tagName = getTagName(element.tag);
	this->attributes = element.attributes;
	this->tag = element.tag;
	this->content = element.content;
}

// WebviewNodes //
void WebviewNodes::add(Element element, cocos2d::CCNode* cocos) {
	this->nodes.push_back(new Node(element, cocos));
}

void WebviewNodes::free() {
	for (auto& x : this->nodes) {
		delete x;
	}
	delete this;
}

std::optional<Node*> WebviewNodes::getById(std::string id) {
	auto match = this->nodes
		| std::views::filter([&id](const Node* node) { return node->id == id; })
		| std::views::take(1);

	if (!match.empty()) return match.front();
	return std::nullopt;
}

std::vector<Node*> WebviewNodes::getByClassName(std::string name) {
	return this->nodes
		| std::views::filter([&name](const Node* node) { return hasClassName(name, node->classList); })
		| std::ranges::to<std::vector>();
}

std::vector<Node*> WebviewNodes::getByTagName(std::string tag) {
	return this->nodes
		| std::views::filter([&tag](const Node* node) { return node->tagName == tag; })
		| std::ranges::to<std::vector>();
}

WebviewNodes::WebviewNodes() {
	this->nodes = {};
}