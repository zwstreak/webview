#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    void onMoreGames(CCObject* sender) {
        FLAlertLayer::create("title", "description", "button")->show();
    }
};
