#ifndef WEBVIEW_RENDERER_HPP
#define WEBVIEW_RENDERER_HPP
#include <include/renderer/Scope.hpp>
#include <include/renderer/WebviewNodes.hpp>
#include <include/parsers/HTMLParser.hpp>
#include <vector>
#include <Webview.hpp>

class WebviewRenderer {
public:
	static WebviewRenderer* create(ZWebview* target);
	void render(HTMLResult data);
	void closeAndCleanup();
private:
	void addTitlebar(std::vector<Element> head);
	void renderHTML(std::vector<Element> body);
	void renderHTMLChild(Element child);

	WebviewScope* scope;
	WebviewNodes* nodes;
	ZWebview* webview;
	WebviewRenderer() = default;
};

#endif