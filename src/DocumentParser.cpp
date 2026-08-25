#include <include/DocumentParser.hpp>

// https://lexbor.com/documentation/#
DocumentParser* DocumentParser::parse(const std::string &content) {
    lxb_status_t status;
    const lxb_char_t* tag_name;
    lxb_html_document_t *document;

    static const lxb_char_t html[] = "<div>Works fine!</div>";
    size_t html_len = sizeof(html) - 1;

    document = lxb_html_document_create();
    if (document == NULL) {
        return nullptr;
    }

    status = lxb_html_document_parse(document, html, html_len);
    if (status != LXB_STATUS_OK) {
        return nullptr;
    }

    return new DocumentParser(document);
}

void DocumentParser::free() {
    lxb_html_document_destroy(document);
    delete this;
}

DocumentParser::DocumentParser(lxb_html_document_t* document) {
    this->document = document;
}
