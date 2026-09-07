#include <include/js/JSEngine.hpp>
#include <quickjs.h>

void JSEngine::execute(std::string script) {

}

JSEngine::JSEngine(WebviewNodes* nodes) {
	this->nodes = nodes;
}