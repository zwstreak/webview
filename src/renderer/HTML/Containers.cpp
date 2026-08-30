#include <include/renderer/HTML/Containers.hpp>

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

void html_container_set_layout_default(CCNode* node, bool webview) {
    auto layout = html_container_get_default_layout();
    if (webview) {
        layout->setPadding({ 6.0f, 9.0f, 0.0f, 0.0f });
        node->setLayout(layout);
        return;
    }

    layout->setAutoGrowAxis(1);
    node->setLayout(layout);
}

// yup thats it
CCNode* html_transpile_container(Element data) {
    return CCMenu::create();
}