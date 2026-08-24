#include "Geode/cocos/menu_nodes/CCMenu.h"
#include <lexbor/html/parser.h>
#include <Webview.hpp>

WEBVIEW_API CCMenu* zwk::Webview::create(const std::string& source) {
    return CCMenu::create();
}
