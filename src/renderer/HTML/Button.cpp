#include <include/renderer/HTML/Button.hpp>
#include <include/renderer/HTML/HTML.hpp>

CCNode* getChild(CCNode* parent, unsigned int at) {
	CCArray* children = parent->getChildren();
	CCObject* child = children->objectAtIndex(at);
	return dynamic_cast<CCNode*>(child);
}

CCNode* html_transpile_button(Element data) {
	auto sprite = ButtonSprite::create(data.content.c_str(), "bigFont.fnt", "background.png"_spr, 0.4f);
	sprite->removeChild(getChild(sprite, 0), true);
	
	auto label = CCLabelTTF::create(data.content.c_str(), "tinos.ttf"_spr, 16.0f);
	label->setColor({ 0, 0, 0 });
	label->setScale(0.7f);
	label->setPosition(sprite->getContentSize() / 2);
	sprite->addChild(label);

	auto bg = dynamic_cast<CCScale9Sprite*>(getChild(sprite, 0));
	if (bg == nullptr) {
		geode::log::debug("son?");
		return nullptr;
	}

	// yes that negative 0.1f matters
	bg->setColor({ 233, 233, 237 });
	sprite->setScaleY(0.35f);
	label->setScaleY(0.35f + (16.0f / 10));
	label->setScaleX(0.35f + (16.0f / 40) + (data.content.length())/160 - 0.1f);

	auto btn = CCMenuItemExt::createSpriteExtra(sprite, [](CCObject* sender) {});
	btn->m_scaleMultiplier = 1.0f;
	return btn;
}