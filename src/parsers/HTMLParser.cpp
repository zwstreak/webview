#include <include/parsers/HTMLParser.hpp>
#include <lexbor/dom/interfaces/node.h>
#include <include/Utils.hpp>

// https://lexbor.com/documentation
HTMLParser* HTMLParser::parse(const std::string &content) {
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

    lxb_dom_node_t* head = (lxb_dom_node_t*)(document->head);
    lxb_dom_node_t* body = (lxb_dom_node_t*)(document->body);
    if (head == NULL || body == NULL) {
        lxb_html_document_destroy(document);
        return nullptr;
    }

    return new HTMLParser(document, head, body);
}

// MAIN - CSS Extraction //
Stylesheet extractLinkCSS(DOMNode element) {
    auto rel_it = element.attributes.find("rel");
    auto href_it = element.attributes.find("href");
    if (rel_it == element.attributes.end() || href_it == element.attributes.end()) {
        return { true, "" };
    }

    if (rel_it->second != "stylesheet") {
        return { true, "" };
    }

    return { true, href_it->second };
}

std::vector<Stylesheet> extractStylesheets(std::vector<DOMNode> head) {
    std::vector<Stylesheet> stylesheets;
    for (auto& child : head) {
        if (child.tag != LXB_TAG_LINK && child.tag != LXB_TAG_STYLE) {
            continue;
        }

        Stylesheet stylesheet = (child.tag == LXB_TAG_LINK)
            ? extractLinkCSS(child)
            : Stylesheet({ false, child.content });

        if (stylesheet.content.empty()) {
            continue;
        }

        stylesheets.push_back(stylesheet);
    }

    return stylesheets;
}

// MAIN - Children Extraction //
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

void parseText(lxb_dom_node_t* node, std::vector<DOMNode>& nodes) {
    size_t content_len;
    const lxb_char_t* content_lxb = lxb_dom_node_text_content(node, &content_len);
    std::string content = stringFromLXBC(content_lxb, content_len);

    if (isWhitespace(content)) {
        return;
    }

    nodes.push_back({
        .type = DOM_TEXT,
        .tag = LXB_TAG__TEXT,
        .content = content,
        .attributes = {},
        .children = {}
    });
}

std::vector<DOMNode> getChildrenOfNode(lxb_dom_node_t* target) {
    lxb_dom_node_t* node = lxb_dom_node_first_child(target);
    std::vector<DOMNode> nodes = {};

    while (node != NULL) {
        if (node->type == LXB_DOM_NODE_TYPE_TEXT) {
            parseText(node, nodes);
            node = lxb_dom_node_next(node);
            continue;
        }

        if (node->type != LXB_DOM_NODE_TYPE_ELEMENT) {
            node = lxb_dom_node_next(node);
            continue;
        }

        lxb_dom_element_t* element = (lxb_dom_element_t*)node;

        // TAG //
        lxb_tag_id_t tag_id = lxb_dom_element_tag_id(element);
        if (tag_id >= LXB_TAG__LAST_ENTRY) {
            node = lxb_dom_node_next(node);
            continue;
        }
        
        // CONTENT //
        size_t content_len;
        const lxb_char_t* content_lxb = lxb_dom_node_text_content(node, &content_len);
        std::string content = stringFromLXBC(content_lxb, content_len);

        // ATTRIBUTES //
        std::unordered_map<std::string, std::string> attributes = getAttributes(element);
        
        // CHILDREN //
        std::vector<DOMNode> children = getChildrenOfNode(node);

        nodes.push_back({
            .type = DOM_ELEMENT,
            .tag = tag_id,
            .content = content,
            .attributes = attributes,
            .children = children
        });
        node = lxb_dom_node_next(node);
    }

    return nodes;
}

// OTHER (MAIN) //
HTMLResult HTMLParser::getResult() {
    std::vector<DOMNode> head_children = getChildrenOfNode(this->head);
    HTMLResult result = {
        .body = getChildrenOfNode(this->body),
        .head = head_children,
        .stylesheets = extractStylesheets(head_children)
    };

    this->free();
    return result;
}

// FREE //
void HTMLParser::free() {
    lxb_html_document_destroy(document);
    delete this;
}

// CONSTRUCTOR //
HTMLParser::HTMLParser(lxb_html_document_t* document, lxb_dom_node_t* head, lxb_dom_node_t* body) {
    this->document = document;
    this->head = head;
    this->body = body;
}