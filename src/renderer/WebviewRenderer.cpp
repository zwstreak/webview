#include <Geode/Geode.hpp>
#include <include/renderer/WebviewRenderer.hpp>
#include <include/renderer/HTML/HTML.hpp>

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
}

// execute head tag scripts
// render HTML
// apply CSS styles
// execute body tag scripts
void WebviewRenderer::render(HTMLResult data) {
	this->renderHTML(data.body);
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