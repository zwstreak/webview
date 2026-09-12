#include <Geode/Geode.hpp>
#include <include/renderer/WebviewRenderer.hpp>
#include <include/renderer/HTML/HTML.hpp>
#include <include/renderer/HTML/Containers.hpp>
#include <include/renderer/HTML/Button.hpp>
#include <include/renderer/HTML/Text.hpp>
#include <include/Utils.hpp>

#define TITLEBAR_HEIGHT 14

void addBackground(CCNode* parent, float yPos, ccColor3B color = {255,255,255}) {
	CCSprite* bg = CCSprite::create("background.png"_spr);
	bg->setColor(color);
	bg->setContentSize(parent->getContentSize());
	bg->setAnchorPoint({ 0.0f, 0.0f });
	bg->setPosition({ 0.0f, yPos });
	bg->setTextureRect({ 0.0f, 0.0f, parent->getContentWidth(), parent->getContentHeight() });
	bg->setZOrder(-50);
	parent->addChild(bg);
}

std::string extractTitle(std::vector<DOMNode> head) {
	auto it = std::find_if(head.begin(), head.end(), [](const DOMNode& element) {
		return element.tag == LXB_TAG_TITLE;
	});

	return (it == head.end()) ? "Untitled" : it->content;
}

// EVERYTHING is a mess omg
// btw one speck of dust will break the whole code
void WebviewRenderer::addTitlebar(std::vector<DOMNode> head) {
	std::string title = extractTitle(head);
	auto bar = CCMenu::create();
	bar->setContentHeight(TITLEBAR_HEIGHT);

	auto name = CCLabelTTF::create(title.c_str(), "tinos.ttf"_spr, 10.0f);
	name->setColor({ 0, 0, 0 });
	name->setAnchorPoint({ 0.0f, 0.5f });
	name->setPosition({ 9.0f, bar->getContentHeight() / 2 });
	bar->addChild(name);

	// using gd close button sprite instead because the HTML button is squished for no reason at all
	// don't you just love it when your code has a bug that cannot be traced
	auto sprite = ButtonSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
	auto button = CCMenuItemExt::createSpriteExtra(sprite, [](CCObject* sender) {});
	bar->addChild(button);

	button->m_scaleMultiplier = 1.1f;
	button->m_baseScale = 0.3f;
	button->setScale(0.3f);
	button->setPosition({ bar->getContentWidth() - 15.0f, bar->getContentHeight() / 2 });
	button->addActivateCallback([this](CCObject* sender) {
		this->closeAndCleanup();
	});

	auto layout = ColumnLayout::create()
		->setAxisAlignment(AxisAlignment::Start)
		->setCrossAxisAlignment(AxisAlignment::Start)
		->setCrossAxisLineAlignment(AxisAlignment::Start)
		->setGap(-TITLEBAR_HEIGHT);

	this->webview->setLayout(layout);
	this->webview->addChild(bar);
	addBackground(bar, 0.0f, { 240, 240, 240 });
}

void WebviewRenderer::renderHTMLChild(DOMNode child, Node* parent) {
	if (child.type == DOM_TEXT) {
		this->scope->addChild(html_create_text_node(child));
		return;
	}

	if (child.tag == LXB_TAG_SCRIPT) {
		this->executeScript(child);
		return;
	}

	CCNode* node = html_transpile_element(child);
	if (node == nullptr) {
		geode::log::error("Node with the tag id '{}' cannot be rendered because it is not implemented.", child.tag);
		return;
	}

	Node* rendered = this->nodes->add(child, node);
	if (parent != nullptr) {
		parent->childrenNodes.push_back(rendered);
	}

	this->scope->addChild(node);
	if (child.children.size() < 1) {
		return;
	}

	this->scope->enter(node);
	this->renderHTML(child.children, rendered);
	this->scope->leave();
	html_post_process(rendered);
}

void WebviewRenderer::renderHTML(std::vector<DOMNode> body, Node* parent) {
	for (auto& child : body) {
		this->renderHTMLChild(child, parent);
	}
	
	this->scope->updateLayout();
	this->webview->updateLayout();
}

void WebviewRenderer::executeScript(DOMNode script) {
	if (!Mod::get()->getSettingValue<bool>("js-execution")) {
		geode::log::debug("skipping script tag because js execution was disabled.");
		return;
	}

	if (script.attributes.contains("src")) {
		geode::log::error("scripts with \"src\" attribute are currently unsupported.");
		return;
	}

	if (script.content.empty()) return;
	this->js->execute(script.content);
}

void WebviewRenderer::executeJS(std::vector<DOMNode> data) {
	for (auto& child : data) {
		if (child.tag != LXB_TAG_SCRIPT) continue;
		this->executeScript(child);
	}
}

// execute head tag scripts
// render HTML
// apply CSS styles
// execute body tag scripts
void WebviewRenderer::render(HTMLResult data) {
	this->addTitlebar(data.head);
	this->executeJS(data.head);
	this->renderHTML(data.body);
}

// hehe fancy
WebviewRenderer* WebviewRenderer::create(ZWebview* target) {
	// UI //
	auto container = CCMenu::create();
	container->setContentSize(target->getContentSize());
	container->setPosition({ 0.0f, 0.0f });
	addBackground(container, -TITLEBAR_HEIGHT);
	target->addChild(container);

	auto content = CCMenu::create();
	content->setAnchorPoint({ 0.0f, 0.0f });
	content->setPosition({ 0.0f, 0.0f });
	html_container_set_layout_default(content, true, TITLEBAR_HEIGHT);
	container->addChild(content);

	// CONSTRUCTOR //
	auto ptr = new WebviewRenderer();
	ptr->scope = new WebviewScope(content);
	ptr->nodes = new WebviewNodes();
	ptr->js = new JSEngine(ptr->nodes);
	ptr->webview = target;

	return ptr;
}

// Note: WebviewRenderer won't be freed until it is closed, meaning this->nodes will exist
void WebviewRenderer::closeAndCleanup() {
	this->webview->removeFromParent();
	this->js->free();
	this->nodes->free();
	delete this->scope;
	delete this;
}