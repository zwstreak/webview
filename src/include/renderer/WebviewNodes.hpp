#ifndef WEBVIEW_RENDERER_NODES_HPP
#define WEBVIEW_RENDERER_NODES_HPP
#include <vector>
#include <optional>
#include <include/parsers/HTMLParser.hpp>
#include <Geode/cocos/base_nodes/CCNode.h>

// Node //
struct Node {
	cocos2d::CCNode* cocos;
	std::vector<std::string> classList;
	std::string id;
	std::string tagName;
	Attributes attributes;
	lxb_tag_id_t tag;
	std::string content;
	std::vector<Node*> childrenNodes;
	DOMNode element;

	Node(DOMNode element, cocos2d::CCNode* cocos);
};

// WebviewNodes //
class WebviewNodes {
public:
	std::optional<Node*> getById(std::string id);
	std::vector<Node*> getByClassName(std::string name);
	std::vector<Node*> getByTagName(std::string tag);
	Node* add(DOMNode element, cocos2d::CCNode* cocos);
	void free();
	WebviewNodes();
private:
	std::vector<Node*> nodes;
};

#endif