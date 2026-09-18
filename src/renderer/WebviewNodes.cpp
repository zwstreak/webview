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

Node::Node(DOMNode element, cocos2d::CCNode* cocos, NodeID id, NodeID parent) {
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
	this->parent_id = parent;
	this->location = id;
}

// WebviewNodes //
Node* WebviewNodes::add(DOMNode element, cocos2d::CCNode* cocos, NodeID parent) {
	auto node = new Node(element, cocos, this->nodes.size() + 1, parent);
	this->nodes.push_back(node);
	return node;
}

Node* WebviewNodes::get(NodeID loc) {
	return this->nodes[loc - 1];
}

void WebviewNodes::remove(NodeID loc) {
	Node* parent = this->get(this->get(loc)->parent_id);
	if (parent != nullptr) {
		parent->childrenNodes.erase(std::find(
			parent->childrenNodes.begin(),
			parent->childrenNodes.end(),
			loc
		));
	}

	delete this->nodes[loc - 1];
	this->nodes[loc - 1] = nullptr;
}

void WebviewNodes::clearChildrenNodes(std::vector<NodeID> vec) {
	for (auto& child_id : vec) {
		this->get(child_id)->cocos->removeFromParent();
		this->remove(child_id);
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