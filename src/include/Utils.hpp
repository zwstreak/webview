#ifndef WEBVIEW_UTILS_HPP
#define WEBVIEW_UTILS_HPP
#include <include/parsers/HTMLParser.hpp>
#include <include/renderer/WebviewRenderer.hpp>
#include <functional>
#include <Geode/Geode.hpp>
using namespace geode::prelude;

CCNode* getChild(CCNode* parent, unsigned int at);
std::vector<std::string> getClassList(Attributes attributes);
bool hasClassName(std::string find, std::vector<std::string> classList);
std::string getAttribute(std::string key, Attributes attributes);
std::string stringFromLXBC(const lxb_char_t* c, size_t len);
bool isWhitespace(std::string data);
void updateParent(CCNode* target, CCNode* newParent);
std::string trim(std::string data);
void sleep(double delayMs, std::function<void()> func);
std::optional<Node*> getMatchFromIDs(std::vector<NodeID> ids, WebviewNodes* nodes, std::function<bool(Node*)> filter);

#endif