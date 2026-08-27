#include <Geode/Geode.hpp>
#include <include/renderer/WebviewRenderer.hpp>
#include <include/renderer/HTML/HTML.hpp>

void WebviewRenderer::renderHTML(std::vector<Element> children) {
	for (auto& child : children) {
		html_render_element(this->scope->get(), child);
		if (child.children.size() < 1) {
			continue;
		}

		this->scope->enter();
		this->renderHTML(child.children);
		this->scope->leave();
		this->scope->addChild(this->scope->release());
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