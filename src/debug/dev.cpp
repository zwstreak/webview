#include <Geode/Geode.hpp>
#include <Geode/binding/CCMenuItemSpriteExtra.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/CreatorLayer.hpp>
#include <Webview.hpp>
using namespace geode::prelude;

#if WEBVIEW_DEBUG_MODE
class $modify(MyCreatorLayer, CreatorLayer) {
    bool init() {
        if (!CreatorLayer::init()) {
            return false;
        }

        this->removeAllChildren();

        CCNode* menu = CCMenu::create();
        menu->setPosition({0, 0});
        this->addChild(menu);

        // yes, the button restarting the game was intentional, press ESC to go back instead
        // im such an idiot for not putting this comment earlier lmao
        CCMenuItemSpriteExtra* back = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
            this,
            menu_selector(MyCreatorLayer::restart)
        );

        back->setAnchorPoint({0.0f, 1.0f});
        back->setPosition({15.0f, menu->getContentSize().height - 15.0f});
        menu->addChild(back);

        CCMenu* webview = zwk::Webview::create("<html><body><p>Hello</p></body></html>");
        menu->addChild(webview);

        return true;
    }

    void restart(CCObject* sender) {
        game::restart(false);
    }
};

class $modify(MyMenuLayer, MenuLayer) {
    void onPlay(CCObject* sender) {
        game::restart(true);
    }
};
#endif
