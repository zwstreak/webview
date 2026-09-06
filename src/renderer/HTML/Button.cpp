#include <include/renderer/HTML/Button.hpp>
#include <include/renderer/HTML/HTML.hpp>
#include <include/Utils.hpp>

// WebviewButton //
WebviewButton* WebviewButton::create(ButtonSprite* sprite) {
	auto ptr = new WebviewButton();
	if (ptr && ptr->init(sprite)) {
		ptr->autorelease();
		return ptr;
	}

	delete ptr;
	return nullptr;
}

bool WebviewButton::init(ButtonSprite* sprite) {
	if (!CCMenuItemSpriteExtra::initWithNormalSprite(sprite, nullptr, nullptr, nullptr, nullptr)) {
		return false;
	}

	auto bg = dynamic_cast<CCScale9Sprite*>(this->getChildByIDRecursive("button-bg"));
	if (bg == nullptr) {
		return false;
	}

	this->m_bg = bg;
	this->addActivateCallback([this](CCObject* sender) {
		this->onActivate(sender);
	});

	return true;
}

void WebviewButton::onActivate(CCObject* sender) {
	this->m_bg->setColor({ 213, 213, 216 });
	this->scheduleActivateEnd();
}

void WebviewButton::activateEnd(float dt) {
	this->m_bg->setColor({ 233, 233, 237 });
}

void WebviewButton::scheduleActivateEnd() {
	this->scheduleOnce(schedule_selector(WebviewButton::activateEnd), 0.05f);
}

// TRANSPILER //
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

	bg->setID("button-bg");
	bg->setColor({ 233, 233, 237 });

	auto btn = WebviewButton::create(sprite);
	btn->m_scaleMultiplier = 1.0f;

	return btn;
}