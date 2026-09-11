#ifndef WEBVIEW_HTML_RENDERER_BUTTON_HTTP
#define WEBVIEW_HTML_RENDERER_BUTTON_HTTP
#include "Include.hpp"

// this class started because of bg->scheduleOnce btw
class WebviewButton : public CCMenuItemSpriteExtra {
public:
	ccColor3B m_bgColor;
	ccColor3B m_bgClickColor;
	ccColor3B m_bgHoverColor;
	CCScale9Sprite* m_bg;
	CCLabelTTF* m_label;

	static WebviewButton* create(ButtonSprite* sprite);
	bool initMembers(ButtonSprite* sprite);
	bool init(ButtonSprite* sprite);
	void selected();
	void unselected();
	void mouseEnter();
	void mouseLeave();
	void update(float dt);
private:
	bool m_isHovering;
};

WebviewButton* html_transpile_button(DOMNode data);

#endif