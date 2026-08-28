#include <include/renderer/HTML/HTML.hpp>
#include <include/renderer/HTML/Text.hpp>

void html_render_element(CCMenu* parent, Element element) {
	if (html_element_is_text(element)) {
		return html_render_text(parent, element);
	}

	switch (element.tag) {
		// TODO: add div
	}
}