#include <include/js/JSEngine.hpp>

#define ATOM_RW_FLAGS (JS_PROP_HAS_GET | JS_PROP_HAS_SET | JS_PROP_WRITABLE)
#define ATOM_R_FLAGS (JS_PROP_HAS_GET)

#define CREATE_OBJ_CLASS(obj, opaque) \
	JS_NewObjectClass(ctx, JSEngine::obj##_id); \
	JS_SetOpaque(obj, JSOpaque_new(opaque, engine))

#define CREATE_PROPERTY_RW(obj, prop) \
	JSAtom atom_##prop = JS_NewAtom(ctx, #prop); \
	JSValue getter_##prop = JS_NewCFunction(ctx, get_##prop, "get " #prop, 1); \
	JSValue setter_##prop = JS_NewCFunction(ctx, set_innerHTML, "set " #prop, 1); \
	JS_DefineProperty(ctx, obj, atom_##prop, JS_UNDEFINED, getter_##prop, setter_##prop, ATOM_RW_FLAGS); \
	JS_FreeAtom(ctx, atom_##prop)

#define CREATE_PROPERTY_R(obj, prop) \
	JSAtom atom_##prop = JS_NewAtom(ctx, #prop); \
	JSValue getter_##prop = JS_NewCFunction(ctx, get_##prop, "get " #prop, 1); \
	JS_DefineProperty(ctx, obj, atom_##prop, JS_UNDEFINED, getter_##prop, JS_UNDEFINED, ATOM_R_FLAGS); \
	JS_FreeAtom(ctx, atom_##prop)

#define CREATE_FUNCTION(obj, name, ptr) \
	JS_SetPropertyStr(ctx, obj, #name, JS_NewCFunction(ctx, ptr, #name, 1));

#define GET_ENGINE(obj, name) nullptr; \
	JSOpaque* _opaque = static_cast<JSOpaque*>(JS_GetOpaque(this_val, JSEngine::obj##_id)); \
	name = _opaque->engine

#define GET_OPAQUE(obj, name, type) nullptr; \
	JSOpaque* _opaque = static_cast<JSOpaque*>(JS_GetOpaque(this_val, JSEngine::obj##_id)); \
	if (_opaque == nullptr) { return JS_ThrowTypeError(ctx, "could not get the JS opaque object."); } \
	JSEngine* engine = _opaque->engine; \
	name = static_cast<type>(_opaque->data);

/*
#define GET_OPAQUE(obj, name, cast) static_cast<cast>(JS_GetOpaque(this_val, JSEngine::obj##_id)); \
	if (name == nullptr) { return JS_ThrowTypeError(ctx, "expected a '" #name "' object"); } \
	JSEngine* engine = GET_ENGINE()
	*/