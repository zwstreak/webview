#include <include/renderer/HTML/HTML.hpp>
#include <include/renderer/HTML/Text.hpp>
#include <include/renderer/HTML/Containers.hpp>

CCNode* html_render_element(Element element) {
	if (html_element_is_text(element)) {
		return html_render_text(element);
	}

	switch (element.tag) {
	case LXB_TAG_DIV:
		return html_render_container(element);
	}

	return nullptr;
}