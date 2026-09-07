#ifndef WEBVIEW_UTILS_HPP
#define WEBVIEW_UTILS_HPP

#include <include/parsers/HTMLParser.hpp>
#include <Geode/Geode.hpp>
using namespace geode::prelude;

CCNode* getChild(CCNode* parent, unsigned int at);
std::vector<std::string> getClassList(Attributes attributes);
std::string getAttribute(std::string key, Attributes attributes);
std::string stringFromLXBC(const lxb_char_t* c, size_t len);

#endif