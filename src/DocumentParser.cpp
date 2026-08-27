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

// MAIN //
std::unordered_map<std::string, std::string> getAttributes(lxb_dom_element_t* element) {
    lxb_dom_attr* attribute = lxb_dom_element_first_attribute(element);
    std::unordered_map<std::string, std::string> attributes;

    while (attribute != NULL) {
        size_t name_len;
        const lxb_char_t* name_lxb = lxb_dom_attr_qualified_name(attribute, &name_len);
        std::string name = stringFromLXBC(name_lxb, name_len);

        size_t value_len;
        const lxb_char_t* value_lxb = lxb_dom_attr_value(attribute, &value_len);
        std::string value = stringFromLXBC(value_lxb, value_len);

        attributes.insert({ name, value });
        attribute = lxb_dom_element_next_attribute(attribute);
    }

    return attributes;
}

// sorry the comments was me miserably failing at the attempt of prettifiying it (talking about // X //)
// well... on a second thought it kinda works
std::vector<Element> getElementsOfNode(lxb_dom_node_t* target) {
    lxb_dom_node_t* node = lxb_dom_node_first_child(target);
    std::vector<Element> elements = {};

    while (node != NULL) {
        if (node->type != LXB_DOM_NODE_TYPE_ELEMENT) {
            node = lxb_dom_node_next(node);
            continue;
        }

        lxb_dom_element_t* element = (lxb_dom_element_t*)node;
        
        // TAG //
        size_t tag_len;
        const lxb_char_t* tag_lxb = lxb_dom_element_qualified_name(element, &tag_len);
        std::string tag = stringFromLXBC(tag_lxb, tag_len);

        // CONTENT //
        size_t content_len;
        const lxb_char_t* content_lxb = lxb_dom_node_text_content(node, &content_len);
        std::string content = stringFromLXBC(content_lxb, content_len);

        // ATTRIBUTES //
        std::unordered_map<std::string, std::string> attributes = getAttributes(element);
        
        // CHILDREN //
        std::vector<Element> children = getElementsOfNode(node);

        elements.push_back({ 
            .tag = tag,
            .content = content,
            .attributes = attributes,
            .children = children
        });
        node = lxb_dom_node_next(node);
    }

    return elements;
}

// OTHER //
std::vector<Element> DocumentParser::getBodyChildren() {
    return getElementsOfNode(this->body);
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