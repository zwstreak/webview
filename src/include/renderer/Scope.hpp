#ifndef WEBVIEW_RENDERER_SCOPE_HPP
#define WEBVIEW_RENDERER_SCOPE_HPP
#include <vector>
#include <Webview.hpp>
#include <Geode/Geode.hpp>
using namespace geode::prelude;

class WebviewScope {
public:
	void enter(CCNode* node);
	void leave();
	void addChild(CCNode* node);
	void updateLayout();
	WebviewScope(ZWebview* webview);
private:
	std::vector<CCNode*> scopes;
};

#endif