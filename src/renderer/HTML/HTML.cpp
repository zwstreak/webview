#include <include/renderer/HTML/HTML.hpp>
#include <include/renderer/HTML/Text.hpp>

void html_render_element(CCMenu* parent, Element element) {
	switch (element.tag) {
	case LXB_TAG_P:
	case LXB_TAG_H1:
	case LXB_TAG_H2:
	case LXB_TAG_H3:
	case LXB_TAG_H4:
	case LXB_TAG_H5:
	case LXB_TAG_H6:
	case LXB_TAG_SPAN:
		return html_render_text(parent, element);
	}
}