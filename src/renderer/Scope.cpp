#include <include/renderer/Scope.hpp>
#include <Geode/Geode.hpp>

// CCMenu stuff //
void WebviewScope::addChild(CCNode* node) {
	this->scopes.back()->addChild(node);
}

// MAIN FUNCTIONALITY //
void WebviewScope::enter() {
	if (this->scopes.size() > 100) {
		geode::log::warn("woah there what are you trying to load??");
		return;
	}

	this->scopes.push_back(CCMenu::create());
}

void WebviewScope::leave() {
	if (this->scopes.size() <= 1) {
		return;
	}

	this->released = this->scopes.back();
	this->scopes.pop_back();
}

// yeah this is obv safe trust me
CCMenu* WebviewScope::release() {
	CCMenu* copy = this->released;
	this->released = nullptr;
	return copy;
}

WebviewScope::WebviewScope(CCMenu* parent) {
	this->scopes = { parent };
	this->released = nullptr;
}