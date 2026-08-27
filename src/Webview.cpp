#include <Geode/cocos/menu_nodes/CCMenu.h>
#include <Geode/utils/file.hpp>

#include <Webview.hpp>
#include <include/DocumentParser.hpp>

#include <filesystem>
namespace fs = std::filesystem;

ZWebview* ZWebview::create() {
    auto ptr = new ZWebview();
    if (ptr && ptr->init()) {
        ptr->autorelease();
        return ptr;
    }

    return nullptr;
}

bool ZWebview::run() {
    if (this->source.empty()) {
        return false;
    }

    DocumentParser* parser = DocumentParser::parse(this->source);
    parser->free();
    return true;
}

void ZWebview::loadSource(const std::string& source) {
    this->source = source;
}

bool ZWebview::loadResource(const std::string& resource) {
    fs::path resources = Mod::get()->getResourcesDir();
    Result<std::string> result = file::readString(resources / resource);
    if (!result) {
        return false;
    }

    this->loadSource(result.unwrapOr("huh"));
    return true;
}
