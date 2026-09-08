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
	void addTitlebar(std::vector<Element> head);
	
	void renderHTML(std::vector<Element> body);
	void renderHTMLChild(Element child);

	void executeScript(Element script);
	void executeJS(std::vector<Element> data);

	JSEngine* js;
	WebviewScope* scope;
	ZWebview* webview;
	WebviewRenderer() = default;
};

#endif