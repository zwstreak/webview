#include <include/js/bindings/HTMLCollection.hpp>
#include <include/js/bindings/Element.hpp>
#include <include/js/Directives.hpp>
#include <include/js/JSUtils.hpp>

// TODO: HTMLCollection is currently static, while it is supposed to be live bruh
#define GET_COLLECTION() GET_OPAQUE(collection, holder, CollectionHolder*)

// length //
JSValue get_length(JS_PARAMS) {
	CollectionHolder* holder = GET_COLLECTION();
	return JS_NewInt64(ctx, holder->data.size());
}

// item //
JSValue fn_item(JS_PARAMS) {
	if (argc < 1) {
		return JS_ThrowTypeError(ctx, "expected \"index\" argument.");
	}

	int64_t index = 0;
	if (JS_ToInt64(ctx, &index, argv[0]) < 0) {
		return JS_ThrowTypeError(ctx, "index argument must be a valid number.");
	}

	CollectionHolder* holder = GET_COLLECTION();
	if (index < 0 || index >= holder->data.size()) {
		return JS_NULL;
	}

	Node* node = engine->nodes->get(holder->data[index]);
	// TODO: cache NodeID -> Element instead of creating a new one everytime
	// meaning JS_NewElementFromNode has to accept the NodeID instead of the Node* itself
	return JS_NewElementFromNode(ctx, node);
}

JSValue fn_namedItem(JS_PARAMS) {
	if (argc < 1) {
		return JS_ThrowTypeError(ctx, "expected \"key\" argument.");
	}

	CollectionHolder* holder = GET_COLLECTION();
	std::string key = getJSString(ctx, argv[0]);
	std::optional<Node*> match = getMatchFromIDs(holder->data, engine->nodes, [key](Node* node) {
		return node->id == key || node->attributes["name"] == key;
	});

	if (match == std::nullopt) {
		return JS_NULL;
	}

	return JS_NewElementFromNode(ctx, match.value());
}

void HTMLCollection_finalizer(JSRuntime* rt, JSValue val) {
	CollectionHolder* holder = static_cast<CollectionHolder*>(JS_GetOpaque(val, JSEngine::collection_id));
	if (holder == nullptr) return;
	delete holder;
}

// TODO: support indexing on HTMLCollection (obj[0])
JSValue JS_NewHTMLCollection(JSContext* ctx, std::vector<NodeID> nodes) {
	std::vector<NodeID> sanitized = {};
	for (auto& id : nodes) {
		Node* data = JSEngine::get()->nodes->get(id);
		if (data == nullptr || data->type != DOM_ELEMENT) continue;
		sanitized.push_back(id);
	}

	CollectionHolder* holder = new CollectionHolder(sanitized);
	JSValue collection = CREATE_OBJ_CLASS(collection, holder);
	CREATE_FUNCTION(collection, item, fn_item);
	CREATE_FUNCTION(collection, namedItem, fn_namedItem);
	CREATE_PROPERTY_R(collection, length);

	return collection;
}