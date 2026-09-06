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

bool WebviewButton::initMembers(ButtonSprite* sprite) {
	CCScale9Sprite* bg = dynamic_cast<CCScale9Sprite*>(getChild(sprite, 0));
	CCLabelTTF* label = dynamic_cast<CCLabelTTF*>(getChild(sprite, 1));
	if (bg == nullptr || label == nullptr) {
		geode::log::warn("The background or the label of the button was not found.");
		return false;
	}

	this->m_bg = bg;
	this->m_label = label;
	return true;
}

bool WebviewButton::init(ButtonSprite* sprite) {
	if (!CCMenuItemSpriteExtra::initWithNormalSprite(sprite, nullptr, nullptr, nullptr, nullptr)) {
		return false;
	}

	if (!this->initMembers(sprite)) {
		return false;
	}

	this->m_bgColor = { 233, 233, 237 };
	this->m_bgClickColor = { 213, 213, 217 };
	this->m_bgHoverColor = { 223, 223, 227 };
	this->m_scaleMultiplier = 1.0f;
	this->m_isHovering = false;
	this->scheduleUpdate();

	this->setContentHeight(this->m_bg->getContentHeight() - 25.0f);
	this->m_bg->setColor(this->m_bgColor);

	return true;
}

void WebviewButton::selected() {
	CCMenuItemSpriteExtra::selected();
	this->m_bg->setColor(this->m_bgClickColor);
}

void WebviewButton::unselected() {
	CCMenuItemSpriteExtra::unselected();
	this->m_bg->setColor(this->m_bgHoverColor);
}

void WebviewButton::mouseEnter() {
	m_isHovering = true;
	this->m_bg->setColor(this->m_bgHoverColor);
}

void WebviewButton::mouseLeave() {
	m_isHovering = false;
	this->m_bg->setColor(this->m_bgColor);
}

void WebviewButton::update(float dt) {
	CCMenuItemSpriteExtra::update(dt);

	CCPoint worldPos = cocos::getMousePos();
	CCPoint localPos = this->convertToNodeSpace(worldPos);
	CCRect localRect = { 0, 0, this->getContentSize().width, this->getContentSize().height };

	bool inside = localRect.containsPoint(localPos);
	if (inside && !m_isHovering) return this->mouseEnter();
	if (inside || !m_isHovering) return;

	this->mouseLeave();
}

// TRANSPILER //
WebviewButton* html_transpile_button(Element data) {
	auto sprite = ButtonSprite::create(data.content.c_str(), "bigFont.fnt", "background.png"_spr, 0.4f);
	sprite->removeChild(getChild(sprite, 0), true);
	
	auto label = CCLabelTTF::create(data.content.c_str(), "tinos.ttf"_spr, 16.0f);
	label->setColor({ 0, 0, 0 });
	label->setScale(0.7f);
	label->setPosition(sprite->getContentSize() / 2);
	sprite->addChild(label);

	sprite->setScaleY(0.35f);
	label->setScaleY(0.35f + (16.0f / 10));
	label->setScaleX(0.35f + (16.0f / 40) + (data.content.length()) / 160 - 0.1f);

	return WebviewButton::create(sprite);
}