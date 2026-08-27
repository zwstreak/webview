#ifndef WEBVIEW_HTML_HPP
#define WEBVIEW_HTML_HPP
#include <lexbor/html/interfaces/element.h>
#include <lexbor/html/parser.h>
#include <vector>
#include <unordered_map>
#include <string>

struct Element {
    std::string tag;
    std::string content;
    std::unordered_map<std::string, std::string> attributes;
    std::vector<Element> children;
};

class HTMLParser {
public:
    /**
     * @warning can return nullptr if any errors happen while parsing.
     */
    static HTMLParser* parse(const std::string& content);
    std::vector<Element> getBodyChildren();
    void free();
private:
    lxb_html_document_t* document;
    lxb_dom_node_t* body;
    HTMLParser(lxb_html_document_t* document, lxb_dom_node_t* body);
};

#endif
