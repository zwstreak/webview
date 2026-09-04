#ifndef WEBVIEW_RENDERER_HPP
#define WEBVIEW_RENDERER_HPP
#include <include/renderer/Scope.hpp>
#include <include/parsers/HTMLParser.hpp>
#include <vector>
#include <Webview.hpp>

class WebviewRenderer {
public:
	static WebviewRenderer* create(ZWebview* target);
	void render(HTMLResult data);
	void free();
private:
	void addTitlebar();
	void renderHTML(std::vector<Element> children);
	void renderHTMLChild(Element child);

	WebviewScope* scope;
	ZWebview* webview;
	WebviewRenderer() = default;
};

#endif