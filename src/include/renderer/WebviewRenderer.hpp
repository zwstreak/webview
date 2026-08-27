#ifndef WEBVIEW_RENDERER_HPP
#define WEBVIEW_RENDERER_HPP
#include <vector>
#include <Webview.hpp>
#include <include/renderer/Scope.hpp>
#include <include/parsers/HTMLParser.hpp>

class WebviewRenderer {
public:
	static WebviewRenderer* create(ZWebview* target);
	void render(std::vector<Element> children);
	void free();
private:
	WebviewScope* scope;
	WebviewRenderer() = default;
};

#endif