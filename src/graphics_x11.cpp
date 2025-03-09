#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <graphics_x11.h>

// namespace graphics_ns_base {

// namespace graphics_ns_x11 {

#define HEX(n, w) "0x" << std::hex << std::setw((w)) << std::setfill('0') << (n)

const int DEFAULT_WIDTH  = 800;
const int DEFAULT_HEIGHT = 600;
const char* DEFAULT_NAME = "Display_X11";

void graphics::init_graphics()
{
	int rc;

	_display = XOpenDisplay(NULL);
	if (!_display) {
		throw std::runtime_error("Unable to open the display");
	}

	_screen = DefaultScreen(_display);
	_visual = DefaultVisualOfScreen(ScreenOfDisplay(_display, _screen));
	_root = RootWindow(_display, _screen);
	_cmap = DefaultColormap(_display, _screen);

	_window = XCreateSimpleWindow(_display, _root, 0, 0, _width, _height, 1,
								  WhitePixel(_display, _screen),
								  BlackPixel(_display, _screen));
	if (!_window) {
		throw std::runtime_error("Unable to create window");
	}

	_gc = XCreateGC(_display, _window, 0, 0);
	if (!_gc) {
		throw std::runtime_error("Unable to create graphic context");
	}

	rc = XSetStandardProperties(_display, _window, _name, NULL, None, NULL, 0, NULL);
	if (!rc) {
		throw std::runtime_error("Unable to set properties");
	}

	rc = XSelectInput(_display, _window, KeyPressMask | ButtonPressMask | ExposureMask);
	if (!rc) {
		throw std::runtime_error("Unable to select input");
	}

	rc = XSetBackground(_display, _gc, BlackPixel(_display, _screen));
	if (!rc) {
		throw std::runtime_error("Unable to set background");
	}

	rc = XSetForeground(_display, _gc, WhitePixel(_display, _screen));
	if (!rc) {
		throw std::runtime_error("Unable to set forground");
	}

	rc = XClearWindow(_display, _window);
	if (!rc) {
		throw std::runtime_error("Unable to clear window");
	}

	rc = XMapRaised(_display, _window);
	if (!rc) {
		throw std::runtime_error("Unable to map window");
	}
};

graphics::graphics() :
				_width{DEFAULT_WIDTH},
		       _height{DEFAULT_HEIGHT},
		       _name{DEFAULT_NAME}
{
	try {
		init_graphics();
	}
	catch (const std::exception& e) {
		throw;
	}
};

graphics::graphics(const char* s) :
	_width{DEFAULT_WIDTH},
	_height{DEFAULT_HEIGHT},
	_name{s}
{
	try {
		init_graphics();
	}
	catch (const std::exception& e) {
		throw;
	}
};

graphics::graphics(int w, int h) :
	_width{w},
	_height{h},
	_name{DEFAULT_NAME}
{
	try {
		init_graphics();
	}
	catch (const std::exception& e) {
		throw;
	}
};

graphics::graphics(int w, int h, const char *s) :
	_width{w},
	_height{h},
	_name{s}
{
	try {
		init_graphics();
	}
	catch (const std::exception& e) {
		throw;
	}
};

graphics::~graphics()
{
	if (_display) {
		XCloseDisplay(_display);
	}

	if (_gc) {
		XFreeGC(_display, _gc);
	}

	XDestroyWindow(_display, _window);
};

void graphics::refresh()
{
};

void graphics::draw_something()
{

};

// } // namespace graphics_ns_x11

// } // namespace graphics_ns_base
