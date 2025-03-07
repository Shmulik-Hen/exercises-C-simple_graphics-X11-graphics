#include <stdexcept>
#include <iostream>
#include <X11/Xutil.h>
#include <graphics_x11.h>

namespace graphics_ns_base {

namespace graphics_ns_x11 {

#define RGB(r, g, b) ( \
						(uint64_t) ( \
							((uint8_t)(r)<<16) + \
							((uint8_t)(g)<<8 ) + \
							((uint8_t)(b)) \
						) \
					 )

const uint64_t RED   = RGB(255, 0, 0);
const uint64_t GREEN = RGB(0, 255, 0);
const uint64_t BLUE  = RGB(0, 0, 255);

const uint32_t DEFAULT_WIDTH  = 800;
const uint32_t DEFAULT_HEIGHT = 600;
const char* DEFAULT_NAME = "Display_X11";

graphics::graphics() : _width{DEFAULT_WIDTH},
		       _height{DEFAULT_HEIGHT},
		       _name{DEFAULT_NAME}
{
	std::cout << "constructor 1" << std::endl;
	try {
		start();
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
	std::cout << "constructor 2" << std::endl;
	try {
		start();
	}
	catch (const std::exception& e) {
		throw;
	}
};

graphics::graphics(uint32_t w, uint32_t h) :
	_width{w},
	_height{h},
	_name{DEFAULT_NAME}
{
	std::cout << "constructor 3" << std::endl;
	try {
		start();
	}
	catch (const std::exception& e) {
		throw;
	}
};

graphics::graphics(uint32_t w, uint32_t h, const char *s) :
	_width{w},
	_height{h},
	_name{s}
{
	std::cout << "constructor 4" << std::endl;
	try {
		start();
	}
	catch (const std::exception& e) {
		throw;
	}
};

graphics::~graphics() {
	std::cout << "destructor" << std::endl;

	if (_display) {
		XCloseDisplay(_display);
	}

	if (_gc) {
		XFreeGC(_display, _gc);
	}

	XDestroyWindow(_display, _window);
};

void graphics::start()
{
	int rc;

	_display = XOpenDisplay(NULL);
	if (!_display) {
		throw std::runtime_error("Unable to open the display");
	}

	_screen = DefaultScreen(_display);
	_root = RootWindow(_display, _screen);
	_fg = BlackPixel(_display, _screen);
	_bg = WhitePixel(_display, _screen);
	_window = XCreateSimpleWindow(_display, _root, 0, 0, _width, _height, 1, _fg, _bg);
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

	rc = XSetBackground(_display, _gc, _bg);
	if (!rc) {
		throw std::runtime_error("Unable to set background");
	}

	rc = XSetForeground(_display, _gc, _fg);
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

	_is_running = true;
};

bool graphics::get_event(XEvent& event)
{
	if (XPending(_display)) {
		XNextEvent(_display, &event);
		return true;
	}

	return false;
};

void graphics::handle_event(XEvent& event) {
	switch (event.type) {
	case Expose:
		if (event.xexpose.count == 0) {
			draw();
		}
		break;
	case KeyPress:
	case ButtonPress:
		_is_running = false;
		break;
	}
};

void graphics::draw() {
	XSetForeground(_display, _gc, GREEN);
	XFillRectangle(_display, _window, _gc, 1, 1, 50, 70);
	XSetForeground(_display, _gc, BLUE);
	XDrawLine(_display, _window, _gc, 100, 100, 200, 100);
	XSetForeground(_display, _gc, RED);
	for (int i = 300; i < 400; i++) {
		XDrawPoint(_display, _window, _gc, i, i);
	}
};

void graphics::run()
{
	XEvent event;

	while (_is_running) {
		if (get_event(event)) {
			handle_event(event);
		}
	}
};

} // namespace graphics_ns_x11

} // namespace graphics_ns_base
