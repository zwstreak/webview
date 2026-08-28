#include <include/renderer/HTML/HTML.hpp>
#include <include/renderer/HTML/Text.hpp>
#include <include/renderer/HTML/Containers.hpp>

CCNode* html_transpile_element(Element element) {
	if (html_element_is_text(element)) {
		return html_transpile_text(element);
	}

	switch (element.tag) {
	case LXB_TAG_DIV:
		return html_transpile_container(element);
	}

	return nullptr;
}