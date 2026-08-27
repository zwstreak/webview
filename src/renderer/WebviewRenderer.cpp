#include <Geode/Geode.hpp>
#include <include/renderer/WebviewRenderer.hpp>

void WebviewRenderer::render(std::vector<Element> children) {
	for (auto& child : children) {
		switch (child.tag) {
		case LXB_TAG_P:
			auto label = CCLabelBMFont::create(child.content.c_str(), "bigFont.fnt");
			this->scope->addChild(label);
			break;
		}

		if (child.children.size() < 1) {
			continue;
		}

		this->scope->enter();
		this->render(child.children);
		this->scope->leave();
		this->scope->addChild(this->scope->release());
	}
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