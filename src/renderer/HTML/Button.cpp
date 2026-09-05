#include <include/renderer/HTML/Button.hpp>
#include <include/renderer/HTML/HTML.hpp>
#include <include/Utils.hpp>

// this class was all because of bg->scheduleOnce btw
class ButtonActions : public CCNode {
public:
	static ButtonActions* create();
	void setBackground(CCObject* sender);
	void onActivate();
	void scheduleActivateEnd();
private:
	void activateEnd();
	// oo the m_ prefix looks nice
	CCScale9Sprite* m_bg;
};

ButtonActions* ButtonActions::create() {
	auto ptr = new ButtonActions();
	if (ptr) {
		ptr->autorelease();
		return ptr;
	}

	delete ptr;
	return nullptr;
}

void ButtonActions::setBackground(CCObject* sender) {
	auto ext = dynamic_cast<CCMenuItemSpriteExtra*>(sender);
	if (ext == nullptr) {
		geode::log::debug("okay you have to be kidding");
		return;
	}

	auto bg = dynamic_cast<CCScale9Sprite*>(ext->getChildByIDRecursive("button-bg"));
	if (bg == nullptr) {
		geode::log::debug("nice");
		return;
	}

	this->m_bg = bg;
	this->m_bg->addChild(this);
}

void ButtonActions::onActivate() {
	this->m_bg->setColor({ 213, 213, 216 });
}

void ButtonActions::activateEnd() {
	this->m_bg->setColor({ 233, 233, 237 });
	this->removeFromParent();
}

void ButtonActions::scheduleActivateEnd() {
	this->scheduleOnce(schedule_selector(ButtonActions::activateEnd), 0.08f);
}

// there HAS to be a better way to do this
void activateCB(CCObject* sender) {
	auto actions = ButtonActions::create();
	actions->setBackground(sender);
	actions->onActivate();
	actions->scheduleActivateEnd();
}

CCMenuItemSpriteExtra* html_transpile_button(Element data) {
	auto sprite = ButtonSprite::create(data.content.c_str(), "bigFont.fnt", "background.png"_spr, 0.4f);
	sprite->removeChild(getChild(sprite, 0), true);
	
	auto label = CCLabelTTF::create(data.content.c_str(), "tinos.ttf"_spr, 16.0f);
	label->setID("button-label");
	label->setColor({ 0, 0, 0 });
	label->setScale(0.7f);
	label->setPosition(sprite->getContentSize() / 2);
	sprite->addChild(label);

	sprite->setScaleY(0.35f);
	label->setScaleY(0.35f + (16.0f / 10));
	label->setScaleX(0.35f + (16.0f / 40) + (data.content.length()) / 160 - 0.1f);

	auto bg = dynamic_cast<CCScale9Sprite*>(getChild(sprite, 0));
	if (bg == nullptr) {
		geode::log::warn("The background of a button was not found.");
		return nullptr;
	}

	bg->setColor({ 233, 233, 237 });
	bg->setID("button-bg");

	auto btn = CCMenuItemExt::createSpriteExtra(sprite, activateCB);
	btn->m_scaleMultiplier = 1.0f;

	return btn;
}