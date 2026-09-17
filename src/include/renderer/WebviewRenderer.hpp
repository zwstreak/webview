#ifndef WEBVIEW_RENDERER_HPP
#define WEBVIEW_RENDERER_HPP
#include <include/renderer/Scope.hpp>
#include <include/renderer/WebviewNodes.hpp>
#include <include/parsers/HTMLParser.hpp>
#include <include/js/JSEngine.hpp>
#include <vector>
#include <Webview.hpp>

class WebviewRenderer {
public:
	static WebviewRenderer* create(ZWebview* target);
	static WebviewRenderer* get();
	void render(HTMLResult data);
	void closeAndCleanup();
	Node* renderHTMLChild(DOMNode child, NodeID parentId = NULL);
	WebviewNodes* nodes;
private:
	void addTitlebar(std::vector<DOMNode> head);
	void renderHTML(std::vector<DOMNode> body, NodeID parentId = NULL);
	void executeScript(DOMNode script);
	void executeJS(std::vector<DOMNode> data);

	static WebviewRenderer* instance;
	JSEngine* js;
	WebviewScope* scope;
	ZWebview* webview;
	WebviewRenderer() = default;
};

#endif