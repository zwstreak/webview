#include <Geode/Geode.hpp>
#include <include/renderer/WebviewRenderer.hpp>
#include <include/renderer/HTML/HTML.hpp>
#include <include/renderer/HTML/Containers.hpp>
#include <include/renderer/HTML/Button.hpp>
#include <include/Utils.hpp>

#define CREATE_EMPTY_ELEMENT(tag, content) { tag, content, {}, {} }
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

std::string extractTitle(std::vector<Element> head) {
	auto it = std::find_if(head.begin(), head.end(), [](const Element& element) {
		return element.tag == LXB_TAG_TITLE;
	});

	return (it == head.end()) ? "Untitled" : it->content;
}

// EVERYTHING is a mess omg
// btw one speck of dust will break the whole code
void WebviewRenderer::addTitlebar(std::vector<Element> head) {
	std::string title = extractTitle(head);
	auto bar = CCMenu::create();
	bar->setContentHeight(TITLEBAR_HEIGHT);

	auto name = CCLabelTTF::create(title.c_str(), "tinos.ttf"_spr, 10.0f);
	name->setColor({ 0, 0, 0 });
	name->setAnchorPoint({ 0.0f, 0.5f });
	name->setPosition({ 9.0f, bar->getContentHeight() / 2 });
	bar->addChild(name);

	auto button = html_transpile_button(CREATE_EMPTY_ELEMENT(LXB_TAG_BUTTON, "X"));
	button->m_bg->setVisible(false);
	bar->addChild(button);

	button->setPosition({ bar->getContentWidth() - 15.0f, bar->getContentHeight() / 2});
	button->m_scaleMultiplier = 1.2f;
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

void WebviewRenderer::renderHTMLChild(Element child) {
	CCNode* node = html_transpile_element(child);
	this->nodes->add({ child, node });
	this->scope->addChild(node);

	if (child.children.size() < 1) {
		return;
	}

	this->scope->enter(node);
	this->renderHTML(child.children);
	this->scope->leave();
}

void WebviewRenderer::renderHTML(std::vector<Element> body) {
	for (auto& child : body) {
		this->renderHTMLChild(child);
	}

	this->scope->updateLayout();
	this->webview->updateLayout();
}

// execute head tag scripts
// render HTML
// apply CSS styles
// execute body tag scripts
void WebviewRenderer::render(HTMLResult data) {
	this->addTitlebar(data.head);
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
	ptr->webview = target;

	return ptr;
}

// Note: WebviewRenderer won't be freed until it is closed, meaning this->nodes will exist
void WebviewRenderer::closeAndCleanup() {
	this->webview->removeFromParent();
	delete this->scope;
	delete this->nodes;
	delete this;
}