#include <include/renderer/HTML/Containers.hpp>

AxisLayout* html_container_get_default_layout() {
    // THANK GOD for the geode developer tools
    auto layout = ColumnLayout::create()
        ->setAxisAlignment(AxisAlignment::End)
        ->setCrossAxisAlignment(AxisAlignment::Start)
        ->setCrossAxisLineAlignment(AxisAlignment::Start)
        ->setAxisReverse(true)
        ->setGap(10.0f);

    return layout;
}

// yup thats it
CCNode* html_transpile_container(Element data) {
    return CCMenu::create();
}