#include <include/renderer/HTML/Text.hpp>
#include <include/renderer/HTML/Containers.hpp>
#include <include/Utils.hpp>

std::unordered_map<lxb_tag_id_t, uint8_t> textElements = {
	{ LXB_TAG_P, 16 },
	{ LXB_TAG_H1, 32 },
	{ LXB_TAG_H2, 24 },
	{ LXB_TAG_H3, 18 },
	{ LXB_TAG_H4, 16 },
	{ LXB_TAG_H5, 14 },
	{ LXB_TAG_H6, 10 }
};

uint8_t getFontSize(lxb_tag_id_t id) {
	auto it = textElements.find(id);
	if (it == textElements.end()) return 0;
	return it->second;
}

// im so smart
bool html_element_is_text(lxb_tag_id_t id) {
	return getFontSize(id) != 0;
}

CCNode* html_transpile_text(DOMNode element) {
	CCMenu* wrapper = CCMenu::create();
	return wrapper;
}

void html_post_process_text(Node* node) {
	CCMenu* wrapper = static_cast<CCMenu*>(node->cocos);
	CCLabelTTF* label = static_cast<CCLabelTTF*>(getChild(wrapper, 0));
	label->setFontSize(getFontSize(node->tag) - 4.0f);
	wrapper->setContentSize(label->getContentSize());
	label->setPosition({ wrapper->getContentWidth() / 2, wrapper->getContentHeight() / 2 });
}

CCNode* html_create_text_node(DOMNode node) {
	CCLabelTTF* label = CCLabelTTF::create(node.content.c_str(), "tinos.ttf"_spr, 16.0f);
	label->setColor({ 0, 0, 0 });
	return label;
}