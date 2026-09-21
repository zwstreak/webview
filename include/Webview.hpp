#ifndef WEBVIEW_API_HPP
#define WEBVIEW_API_HPP
#include <Geode/Geode.hpp>
#include <Geode/cocos/menu_nodes/CCMenu.h>
using namespace geode::prelude;

#ifdef GEODE_IS_WINDOWS
    #ifdef WEBVIEW_EXPORTING
        #define WEBVIEW_API __declspec(dllexport)
    #else
        #define WEBVIEW_API __declspec(dllimport)
    #endif
#else
    #define WEBVIEW_API __attribute__((visibility("default")))
#endif

// lowkey the $class was just making code uglier
class WEBVIEW_API ZWebview : public CCMenu {
public:
    static ZWebview* create();

    void loadSource(const std::string& source);
    bool loadResource(Mod* callingMod, const std::string& resource);
    bool run();
private:
    std::string source;
};

#endif
