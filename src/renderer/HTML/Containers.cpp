#include <include/renderer/HTML/Containers.hpp>

std::vector<lxb_tag_id_t> containerElements = {
    LXB_TAG_DIV,
    LXB_TAG_SECTION,
    LXB_TAG_ARTICLE,
    LXB_TAG_MAIN,
    LXB_TAG_HEADER,
    LXB_TAG_ASIDE,
    LXB_TAG_NAV,
    LXB_TAG_SPAN // oops
};

AxisLayout* html_container_get_default_layout() {
    // THANK GOD for the geode developer tools
    auto layout = ColumnLayout::create()
        ->setAxisAlignment(AxisAlignment::End)
        ->setCrossAxisAlignment(AxisAlignment::Start)
        ->setCrossAxisLineAlignment(AxisAlignment::Start)
        ->setAxisReverse(true)
        ->setGap(5.0f);

    return layout;
}

void html_container_set_layout_default(CCNode* node, bool webview, float offset) {
    auto layout = html_container_get_default_layout();
    if (webview) {
        layout->setPadding({ 6.0f, 9.0f + offset, 0.0f, 0.0f });
        node->setLayout(layout);
        return;
    }

    layout->setAutoGrowAxis(1);
    node->setLayout(layout);
}

bool html_element_is_container(DOMNode data) {
    return std::find(containerElements.begin(), containerElements.end(), data.tag) != containerElements.end();
}

// yup thats it
CCNode* html_transpile_container(DOMNode data) {
    return CCMenu::create();
}