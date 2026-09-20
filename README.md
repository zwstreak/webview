# Webview
<div align="center">
	<img align="center" src="logo.png" alt="what da dawg doin" width="80" height="80">
	<p align="center">Adding webview support to Geometry Dash.</p>
</div>

# Table Of Contents
* [Dependencies](#dependencies)
* [Warnings](#warnings)
* [How to use](#how-to-use)
* [API Usage](#api-usage)
* [Supported APIs](#supported-apis)
* [Questions & Answers](#questions-answers)

# Dependencies
- Lexbor (HTML, CSS Parser)
- QuickJS (JavaScript Interpreter)

These are automatically installed thanks to the `FetchContent` function (on `CMakeLists.txt`)

# Warnings
* This is not the kind of Webview you'd expect, It instead shows content by converting all HTML tags into Cocos2D objects (CCMenu* etc.), And converting CSS (Stylesheets) into Cocos2D functions (duhhhh).
* This does not (*currently*) support all the HTML tags because its too much just let me rest bro
* There **MIGHT** be some bugs in the code and.. umm memory leaks hell yeah

# How to use
Create a new geode project (duh) then edit the mod.json file:
```json
...
"dependencies": {
	...,
	{
		"id": "zwstreak.webview",
		"version": ">=0.0.1",
		"importance": "required"
	}
}
```

After that you can include the API like this:
```c++
#include <Webview.hpp>
```

# API Usage
### Loading an HTML string (not recommended)
```c++
ZWebview* webview = ZWebview::create();
webview->loadSource("<html><body><div>Hello World!</div></body></html>");
webview->run();
this->addChild(webview);
```

### Loading an HTML resource (big thumbs up)
```c++
ZWebview webview = ZWebview::create();
webview->loadResource("index.html");
webview->run();
this->addChild(webview);
```

# Supported APIs
Read more at [Supported APIs](supported_apis.md) file.

# Questions & Answers
1. What does Z mean and why is it the prefix of classes?<br/>
**->** Z means "zwstreak" which is the creator of this mod, I have decided to make it a prefix
   so that it holds all the APIs I make for Geometry Dash.

2. Why is the logo so bad?<br/>
**->** bro wdym that logo is absolutely magnificent

3. Is it free?<br/>
**->** YES, it is and will always be free. (duh)