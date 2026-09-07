#ifndef WEBVIEW_RENDERER_NODES_HPP
#define WEBVIEW_RENDERER_NODES_HPP
#include <vector>
#include <optional>
#include <include/parsers/HTMLParser.hpp>
#include <Geode/cocos/base_nodes/CCNode.h>

// RenderedNode //
struct RenderedNode {
	cocos2d::CCNode* node;
	std::vector<std::string> classList;
	std::string id;
	std::string tagName;
	Attributes attributes;
	lxb_tag_id_t tag;

	RenderedNode(Element element, cocos2d::CCNode* node);
};

// WebviewNodes //
class WebviewNodes {
public:
	std::optional<RenderedNode> getById(std::string id);
	std::vector<RenderedNode> getByClassName(std::string name);
	std::vector<RenderedNode> getByTagName(std::string tag);
	void add(RenderedNode node);
	WebviewNodes();
private:
	std::vector<RenderedNode> nodes;
};

#endif