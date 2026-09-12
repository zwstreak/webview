#include <include/renderer/HTML/Button.hpp>
#include <include/renderer/HTML/Text.hpp>
#include <include/renderer/HTML/HTML.hpp>
#include <include/Utils.hpp>

#define CREATE_EMPTY_ELEMENT(tag, content) { DOM_ELEMENT, tag, content, {}, {} }

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
	if (bg == nullptr) {
		geode::log::warn("The background or the label of the button was not found.");
		return false;
	}

	this->m_bg = bg;
	this->m_sprite = sprite;
	return true;
}

bool WebviewButton::init(ButtonSprite* sprite) {
	if (!CCMenuItemSpriteExtra::initWithNormalSprite(sprite, nullptr, nullptr, nullptr, nullptr)) {
		return false;
	}

	if (!this->initMembers(sprite)) {
		return false;
	}

	this->m_scaleMultiplier = 1.0f;
	this->m_bgColor = { 233, 233, 237 };
	this->m_bgClickColor = { 213, 213, 217 };
	this->m_bgHoverColor = { 223, 223, 227 };
	this->m_isHovering = false;
	this->m_label = nullptr;
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
WebviewButton* html_transpile_button(DOMNode data) {
	auto sprite = ButtonSprite::create("", "bigFont.fnt", "background.png"_spr, 0.4f);
	sprite->removeChild(getChild(sprite, 0), true);
	sprite->setScaleY(0.35f);
	return WebviewButton::create(sprite);
}

// TODO: support <button><p>Hello world</p></button>
void html_post_process_button(Node* node) {
	WebviewButton* button = static_cast<WebviewButton*>(node->cocos);
	CCLabelTTF* label = dynamic_cast<CCLabelTTF*>(button->getChildren()->lastObject());
	if (label == nullptr) {
		geode::log::debug("found a button element does not have a text node.");
		return;
	}

	CCSize size = { label->getContentWidth() + 10, label->getContentHeight() };
	updateParent(label, button->m_sprite);

	button->m_bg->setContentSize(size);
	button->m_sprite->setContentSize(size);
	button->m_bg->setAnchorPoint({ 0.0f, 0.0f });
	button->m_bg->setPosition({ 0.0f, 0.0f });
	button->m_sprite->setPosition({ 0.0f, 0.0f });
	button->setPosition({ 0.0f, 0.0f });

	label->setPosition(button->m_sprite->getContentSize() / 2);
	button->updateSprite();
	button->m_label = label;
}

// did you know that i wrote cocos->addChild(cocos)
// crazy what no sleep does to you
WebviewButton* create_button(std::string content) {
	DOMNode node = CREATE_EMPTY_ELEMENT(LXB_TAG_BUTTON, content);
	WebviewButton* cocos = html_transpile_button(node);
	CCLabelTTF* label = html_create_text_node(node);
	cocos->addChild(label);

	Node* tmp = new Node(node, cocos);
	html_post_process_button(tmp);
	delete tmp;

	return cocos;
}