#include <Geode/Geode.hpp>
#include <include/renderer/WebviewRenderer.hpp>
#include <include/renderer/HTML/HTML.hpp>
#include <include/renderer/HTML/Containers.hpp>

void WebviewRenderer::addBackground(CCNode* parent) {
	CCSprite* bg = CCSprite::create("background.png"_spr);
	bg->setColor({ 255, 255, 255 });
	bg->setContentSize(parent->getContentSize());
	bg->setAnchorPoint({ 0.0f, 0.0f });
	bg->setPosition({ 0.0f, 0.0f });
	bg->setTextureRect({ 0.0f, 0.0f, parent->getContentWidth(), parent->getContentHeight() });
	bg->setZOrder(-50);

	parent->addChild(bg);
}

void WebviewRenderer::renderHTML(std::vector<Element> children) {
	for (auto& child : children) {
		CCNode* node = html_transpile_element(child);
		this->scope->addChild(node);

		if (child.children.size() < 1) {
			continue;
		}

		this->scope->enter(node);
		this->renderHTML(child.children);
		this->scope->leave();
	}

	this->scope->updateLayout();
}

// execute head tag scripts
// render HTML
// apply CSS styles
// execute body tag scripts
void WebviewRenderer::render(HTMLResult data) {
	this->renderHTML(data.body);
	this->addBackground(this->scope->get());
}

// hehe fancy
WebviewRenderer* WebviewRenderer::create(ZWebview* target) {
	auto ptr = new WebviewRenderer();
	ptr->scope = new WebviewScope(target);
	return ptr;
}

void WebviewRenderer::free() {
	delete this->scope;
	delete this;
}