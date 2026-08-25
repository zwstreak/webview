#include "lexbor/dom/interface.h"
#include "lexbor/dom/interfaces/node.h"
#include <include/DocumentParser.hpp>

// https://lexbor.com/documentation/#
DocumentParser* DocumentParser::parse(const std::string &content) {
    lxb_html_document_t* document = lxb_html_document_create();
    if (document == NULL) {
        lxb_html_document_destroy(document);
        return nullptr;
    }

    const lxb_char_t* html = reinterpret_cast<const lxb_char_t*>(content.c_str());
    lxb_status_t status = lxb_html_document_parse(document, html, content.size());
    if (status != LXB_STATUS_OK) {
        lxb_html_document_destroy(document);
        return nullptr;
    }

    lxb_dom_node_t* body = lxb_dom_interface_node(lxb_html_document_body_element(document));
    if (body == NULL) {
        lxb_html_document_destroy(document);
        return nullptr;
    }

    return new DocumentParser(document, body);
}

// UTILS //
std::string stringFromLXBC(const lxb_char_t* c, size_t len) {
    if (c == NULL || len == 0) return "";
    return std::string(reinterpret_cast<const char*>(c), len);
}

// OTHER //
std::vector<Element> DocumentParser::getElements() {
    lxb_dom_node_t* node = lxb_dom_node_first_child(this->body);
    std::vector<Element> elements = {};

    while (node != NULL) {
        if (node->type != LXB_DOM_NODE_TYPE_ELEMENT) {
            node = lxb_dom_node_next(node);
            continue;
        }

        size_t len;
        const lxb_char_t* name = lxb_dom_node_name(node, &len);
        std::string tag = stringFromLXBC(name, len);
        elements.push_back({ .tag = tag });
        node = lxb_dom_node_next(node);
    }

    return elements;
}

// FREE //
void DocumentParser::free() {
    lxb_html_document_destroy(document);
    delete this;
}

// CONSTRUCTOR //
DocumentParser::DocumentParser(lxb_html_document_t* document, lxb_dom_node_t* body) {
    this->document = document;
    this->body = body;
}
