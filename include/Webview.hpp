#ifndef WEBVIEW_API_HPP
#define WEBVIEW_API_HPP
#include <Geode/Geode.hpp>
#include <Geode/cocos/menu_nodes/CCMenu.h>
using namespace geode::prelude;

#ifdef WEBVIEW_DEBUG_MODE
    #define WEBVIEW_API
#elifdef GEODE_IS_WINDOWS
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

    void fromSource(const std::string& source);
    bool fromResource(const std::string& resource);
    bool run();
private:
    std::string source;
};

#endif
