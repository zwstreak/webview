#include <include/renderer/Scope.hpp>
#include <include/renderer/HTML/Containers.hpp>
#include <Geode/Geode.hpp>

// CCNode stuff //
void WebviewScope::addChild(CCNode* node) {
	this->scopes.back()->addChild(node);
}

void WebviewScope::updateLayout() {
	this->scopes.back()->updateLayout(false);
}

// MAIN FUNCTIONALITY //
void WebviewScope::enter(CCNode* node) {
	if (this->scopes.size() > 50) {
		geode::log::warn("woah there what are you trying to load?? 50+ bomboclat children btw");
		return;
	}

	html_container_set_layout_default(node);
	this->scopes.push_back(node);
}

void WebviewScope::leave() {
	if (this->scopes.size() <= 1) {
		return;
	}

	this->updateLayout();
	this->scopes.pop_back();
}

WebviewScope::WebviewScope(ZWebview* parent) {
	html_container_set_layout_default(parent, true);
	this->scopes = { parent };
}