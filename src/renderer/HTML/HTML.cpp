#include <include/renderer/HTML/HTML.hpp>
#include <include/renderer/HTML/Text.hpp>
#include <include/renderer/HTML/Containers.hpp>
#include <include/renderer/HTML/Button.hpp>

// TODO: reference DOMNode instead of creating a copy everytime
CCNode* html_transpile_element(DOMNode element) {
	if (html_element_is_text(element.tag)) {
		return html_transpile_text(element);
	}

	if (html_element_is_container(element)) {
		return html_transpile_container(element);
	}

	switch (element.tag) {
	case LXB_TAG_BUTTON:
		return html_transpile_button(element);
	}

	return nullptr;
}

void html_post_process(Node* node) {
	if (html_element_is_text(node->tag)) {
		return html_post_process_text(node);
	}

	switch (node->tag) {
	case LXB_TAG_BUTTON:
		return html_post_process_button(node);
	}

	geode::log::debug("postprocess event does not exist for element with tag name '{}'", node->tagName);
}