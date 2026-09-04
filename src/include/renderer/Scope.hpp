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
	CCNode* get();
	void addChild(CCNode* node);
	void updateLayout();
	WebviewScope(CCMenu* parent);
private:
	std::vector<CCNode*> scopes;
};

#endif