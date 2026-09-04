#include <include/Utils.hpp>

CCNode* getChild(CCNode* parent, unsigned int at) {
	CCArray* children = parent->getChildren();
	CCObject* child = children->objectAtIndex(at);
	return dynamic_cast<CCNode*>(child);
}