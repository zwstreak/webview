#include <include/renderer/HTML/Text.hpp>

std::unordered_map<lxb_tag_id_t, uint8_t> textElements = {
	{ LXB_TAG_P, 16 },
	{ LXB_TAG_SPAN, 16 },
	{ LXB_TAG_H1, 32 },
	{ LXB_TAG_H2, 24 },
	{ LXB_TAG_H3, 18 },
	{ LXB_TAG_H4, 16 },
	{ LXB_TAG_H5, 14 },
	{ LXB_TAG_H6, 10 }
};

uint8_t getFontSize(Element element) {
	auto it = textElements.find(element.tag);
	if (it == textElements.end()) return 0;
	return it->second;
}

// im so smart
bool html_element_is_text(Element element) {
	return getFontSize(element) != 0;
}

// 4 hours of trying stuff out btw
// i couldn't make CCLabelBMFont work with font sizes, i tried everything
// and CCLabelTTF is so slow, but i guess you gotta do what you gotta do
CCNode* html_transpile_text(Element element) {
	auto label = CCLabelTTF::create(element.content.c_str(), "tinos.tff", getFontSize(element));
	return label;
}