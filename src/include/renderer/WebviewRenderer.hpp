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
	void renderHTML(std::vector<Element> children);
	void addBackground(CCNode* parent);
	WebviewScope* scope;
	WebviewRenderer() = default;
};

#endif