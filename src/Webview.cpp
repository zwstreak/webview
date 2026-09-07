#include <Geode/utils/file.hpp>
#include <include/parsers/HTMLParser.hpp>
#include <include/renderer/WebviewRenderer.hpp>
#include <include/js/JSEngine.hpp>
#include <Webview.hpp>

#include <filesystem>
namespace fs = std::filesystem;

ZWebview* ZWebview::create() {
    auto ptr = new ZWebview();
    if (ptr && ptr->init()) {
        ptr->autorelease();
        return ptr;
    }

    // oops
    delete ptr;
    return nullptr;
}

bool ZWebview::run() {
    if (this->source.empty()) {
        return false;
    }

    WebviewRenderer* renderer = WebviewRenderer::create(this);
    HTMLParser* parser = HTMLParser::parse(this->source);
    if (parser == nullptr) {
        return false;
    }

    HTMLResult result = parser->getResult();
    renderer->render(result);

    JSEngine* engine = new JSEngine(renderer->nodes);
    engine->execute("const element = document.getElementById('register'); console.warn(element.innerHTML); element.innerHTML = \"Hello\"");
    engine->free();

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
