#include <Geode/cocos/menu_nodes/CCMenu.h>
#include <Geode/utils/file.hpp>
#include <Webview.hpp>

#include <filesystem>
namespace fs = std::filesystem;

WEBVIEW_API CCMenu* zwk::Webview::create(const std::string& source) {
    return CCMenu::create();
}

WEBVIEW_API CCMenu* zwk::Webview::createFromResource(const std::string& resource) {
    fs::path resources = Mod::get()->getResourcesDir();
    Result<std::string> result = file::readString(resources / resource);
    if (!result) {
        return nullptr;
    }

    return zwk::Webview::create(result.unwrapOr("huh"));
}
