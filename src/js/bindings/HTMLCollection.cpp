#include <include/js/bindings/HTMLCollection.hpp>
#include <include/js/Directives.hpp>

#define GET_COLLECTION() GET_OPAQUE(collection, holder, CollectionHolder*)

// length //
JSValue get_length(JS_PARAMS) {
	CollectionHolder* holder = GET_COLLECTION();
	return JS_NewInt64(ctx, holder->data.size());
}

void HTMLCollection_finalizer(JSRuntime* rt, JSValue val) {
	CollectionHolder* holder = static_cast<CollectionHolder*>(JS_GetOpaque(val, JSEngine::collection_id));
	if (holder == nullptr) return;
	delete holder;
}

JSValue JS_NewHTMLCollection(JSContext* ctx, std::vector<NodeID> nodes) {
	std::vector<NodeID> sanitized = {};
	for (auto& id : nodes) {
		Node* data = JSEngine::get()->nodes->get(id);
		if (data == nullptr || data->type != DOM_ELEMENT) continue;
		sanitized.push_back(id);
	}

	CollectionHolder* holder = new CollectionHolder(sanitized);
	JSValue collection = CREATE_OBJ_CLASS(collection, holder);
	CREATE_PROPERTY_R(collection, length);

	return collection;
}