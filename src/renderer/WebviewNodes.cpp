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

Node::Node(DOMNode element, cocos2d::CCNode* cocos, size_t id, Node* parent) {
	this->cocos = cocos;
	this->element = element;
	this->classList = getClassList(this->element.attributes);
	this->id = getAttribute("id", this->element.attributes);
	this->tagName = getTagName(this->element.tag);
	this->attributes = this->element.attributes;
	this->tag = this->element.tag;
	this->content = this->element.content;
	this->childrenNodes = {};
	this->type = this->element.type;
	this->parent = parent;
	this->vec_id = id;
}

// WebviewNodes //
Node* WebviewNodes::add(DOMNode element, cocos2d::CCNode* cocos, Node* parent) {
	auto node = new Node(element, cocos, this->nodes.size(), parent);
	this->nodes.push_back(node);
	return node;
}

void WebviewNodes::remove(size_t loc) {
	// ISSUE?: other parents can have the removed node inside childrenNodes
	// TODO: use vec_id for childrenNodes instead of the Node ptr itself
	delete this->nodes[loc];
	this->nodes[loc] = nullptr;
}

void WebviewNodes::clearNodes(std::vector<Node*> vec) {
	for (auto& child : vec) {
		child->cocos->removeFromParent();
		this->remove(child->vec_id);
	}
	vec.clear();
}

void WebviewNodes::free() {
	for (auto& x : this->nodes) {
		if (x == nullptr) continue;
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