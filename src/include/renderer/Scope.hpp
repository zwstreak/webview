#ifndef WEBVIEW_RENDERER_SCOPE_HPP
#define WEBVIEW_RENDERER_SCOPE_HPP
#include <vector>
#include <Geode/Geode.hpp>
using namespace geode::prelude;

class WebviewScope {
public:
	void enter();
	void leave();
	void addChild(CCNode* node);
	CCMenu* release();
	CCMenu* get();
	WebviewScope(CCMenu* parent);
private:
	std::vector<CCMenu*> scopes;
	CCMenu* released;
};

#endif