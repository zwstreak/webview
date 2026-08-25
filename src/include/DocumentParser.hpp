#ifndef WEBVIEW_HTML_HPP
#define WEBVIEW_HTML_HPP
#include <lexbor/html/interfaces/element.h>
#include <lexbor/html/parser.h>
#include <string>

class DocumentParser {
public:
    /**
     * @warning can return nullptr if any errors happen while parsing.
     */
    static DocumentParser* parse(const std::string& content);
    void free();
private:
    lxb_html_document_t* document;
    DocumentParser(lxb_html_document_t* document);
};

#endif
