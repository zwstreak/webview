#ifndef WEBVIEW_HTML_RENDERER_BUTTON_HTTP
#define WEBVIEW_HTML_RENDERER_BUTTON_HTTP
#include "Include.hpp"

// this class started because of bg->scheduleOnce btw
class WebviewButton : public CCMenuItemSpriteExtra {
public:
	static WebviewButton* create(ButtonSprite* sprite);
	bool init(ButtonSprite* sprite);
private:
	void scheduleActivateEnd();

	void onActivate(CCObject* sender);
	void activateEnd(float dt);

	CCScale9Sprite* m_bg;
};

CCMenuItemSpriteExtra* html_transpile_button(Element data);

#endif