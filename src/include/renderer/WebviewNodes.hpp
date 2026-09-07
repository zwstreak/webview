#ifndef WEBVIEW_RENDERER_NODES_HPP
#define WEBVIEW_RENDERER_NODES_HPP
#include <vector>
#include <optional>
#include <include/parsers/HTMLParser.hpp>
#include <Geode/cocos/base_nodes/CCNode.h>

// send nodes (sorry)
struct RenderedNode {
	cocos2d::CCNode* node;
	std::string id;
	Element element;
};

class WebviewNodes {
public:
	std::optional<RenderedNode> getById(std::string id);
	WebviewNodes();
private:
	std::vector<RenderedNode> nodes;
};

#endif