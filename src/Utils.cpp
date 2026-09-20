#include <include/Utils.hpp>
#include <arc/time/Sleep.hpp>
#include <ranges>

CCNode* getChild(CCNode* parent, unsigned int at) {
	CCArray* children = parent->getChildren();
	CCObject* child = children->objectAtIndex(at);
	return dynamic_cast<CCNode*>(child);
}

std::vector<std::string> getClassList(Attributes attributes) {
	std::string className = getAttribute("class", attributes);
	std::stringstream ss(className);
	std::string item;
	std::vector<std::string> list;
	while (std::getline(ss, item, ' ')) {
		list.push_back(item);
	}

	return list;
}

bool hasClassName(std::string find, std::vector<std::string> classList) {
	return std::find(classList.begin(), classList.end(), find) != classList.end();
}

std::string getAttribute(std::string key, Attributes attributes) {
	auto it = attributes.find(key);
	if (it == attributes.end()) {
		return "";
	}

	return it->second;
}

std::string stringFromLXBC(const lxb_char_t* c, size_t len) {
	if (c == NULL || len == 0) return "";
	return std::string(reinterpret_cast<const char*>(c), len);
}

bool isWhitespace(std::string data) {
	return std::ranges::all_of(data, [](char c) {
		return std::isspace(c);
	});
}

void updateParent(CCNode* target, CCNode* newParent) {
	target->retain();
	target->removeFromParent();
	newParent->addChild(target);
	target->release();
}

std::string trim(std::string data) {
	std::string_view view(data);
	view.remove_prefix(std::min(view.find_first_not_of(" \t\r\v\n"), view.size()));
	view.remove_suffix(std::min(view.size() - view.find_last_not_of(" \t\r\v\n") - 1, view.size()));
	return std::string(view);
}

void sleep(double delayMs, std::function<void()> func) {
	async::spawn(arc::sleepFor(asp::Duration::fromMillis(delayMs)), [func]() {
		func();
	});
}

std::optional<Node*> getMatchFromIDs(std::vector<NodeID> ids, WebviewNodes* nodes, std::function<bool(Node*)> filter) {
	auto match = ids
		| std::views::filter([filter, nodes](const NodeID& id) { return filter(nodes->get(id)); }) 
		| std::views::take(1);

	if (!match.empty()) return nodes->get(match.front());
	return std::nullopt;
}