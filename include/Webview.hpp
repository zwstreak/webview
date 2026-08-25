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

// inspired by $modify
// this is so cursed lol
#define $class(name, data) namespace zwk { struct name data; }

$class(Webview, {
    /**
     * Create a new webview from an HTML source code.
     */
    static WEBVIEW_API CCMenu* create(const std::string& source);
    /*
     * Read contents of a resource and create a webview from it.
     * @warning can return `nullptr` if the resource does not exist.
     */
    static WEBVIEW_API CCMenu* createFromResource(const std::string& resource);
});

#endif
