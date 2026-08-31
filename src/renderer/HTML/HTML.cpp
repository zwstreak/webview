#include <include/renderer/HTML/HTML.hpp>
#include <include/renderer/HTML/Text.hpp>
#include <include/renderer/HTML/Containers.hpp>
#include <include/renderer/HTML/Button.hpp>

CCNode* html_transpile_element(Element element) {
	if (html_element_is_text(element)) {
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