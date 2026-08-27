#include <include/renderer/HTML/Text.hpp>

void html_render_text(CCMenu* parent, Element element) {
	auto label = CCLabelBMFont::create(element.content.c_str(), "bigFont.fnt");
	parent->addChild(label);
}