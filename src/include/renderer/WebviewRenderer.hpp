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
	void render(HTMLResult data);
	void closeAndCleanup();
	WebviewNodes* nodes;
private:
	void addTitlebar(std::vector<DOMNode> head);
	
	void renderHTML(std::vector<DOMNode> body, Node* parent = nullptr);
	void renderHTMLChild(DOMNode child, Node* parent = nullptr);

	void executeScript(DOMNode script);
	void executeJS(std::vector<DOMNode> data);

	JSEngine* js;
	WebviewScope* scope;
	ZWebview* webview;
	WebviewRenderer() = default;
};

#endif