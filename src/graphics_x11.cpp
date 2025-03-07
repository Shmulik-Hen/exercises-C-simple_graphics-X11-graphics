#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <X11/Xutil.h>
#include <graphics_x11.h>

namespace graphics_ns_base {

namespace graphics_ns_x11 {

const uint32_t DEFAULT_WIDTH  = 800;
const uint32_t DEFAULT_HEIGHT = 600;
const char* DEFAULT_NAME = "Display_X11";
#define HEX(n, w) " 0x" << std::hex << std::setw((w)) << std::setfill('0') << (n)

graphics::graphics() : _width{DEFAULT_WIDTH},
		       _height{DEFAULT_HEIGHT},
		       _name{DEFAULT_NAME}
{
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
	try {
		start();
	}
	catch (const std::exception& e) {
		throw;
	}
};

graphics::~graphics() {
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
	_window = XCreateSimpleWindow(_display, _root, 0, 0, _width, _height, 1, colors::dark_grey, colors::black);
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

	rc = XSetBackground(_display, _gc, colors::black);
	if (!rc) {
		throw std::runtime_error("Unable to set background");
	}

	rc = XSetForeground(_display, _gc, colors::dark_grey);
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
	int x = 1, y = 1;

	XSetForeground(_display, _gc, colors::white);
	XFillRectangle(_display, _window, _gc, x, y, x+50, y+50);
	x += 50;

	XSetForeground(_display, _gc, colors::grey);
	XFillRectangle(_display, _window, _gc, x, y, x+50, y+50);
	x += 50;

	XSetForeground(_display, _gc, colors::dark_grey);
	XFillRectangle(_display, _window, _gc, x, y, x+50, y+50);
	x += 50;

	XSetForeground(_display, _gc, colors::black);
	XFillRectangle(_display, _window, _gc, x, y, x+50, y+50);
	x = 1;
	y += 50;

	XSetForeground(_display, _gc, colors::bright_red);
	XFillRectangle(_display, _window, _gc, x, y, x+50, y+50);
	x += 50;

	XSetForeground(_display, _gc, colors::red);
	XFillRectangle(_display, _window, _gc, x, y, x+50, y+50);
	x += 50;

	XSetForeground(_display, _gc, colors::dark_red);
	XFillRectangle(_display, _window, _gc, x, y, x+50, y+50);
	x += 50;

	XSetForeground(_display, _gc, colors::black);
	XFillRectangle(_display, _window, _gc, x, y, x+50, y+50);
	x = 1;
	y += 50;

	XSetForeground(_display, _gc, colors::bright_green);
	XFillRectangle(_display, _window, _gc, x, y, x+50, y+50);
	x += 50;

	XSetForeground(_display, _gc, colors::green);
	XFillRectangle(_display, _window, _gc, x, y, x+50, y+50);
	x += 50;

	XSetForeground(_display, _gc, colors::dark_green);
	XFillRectangle(_display, _window, _gc, x, y, x+50, y+50);
	x += 50;

	XSetForeground(_display, _gc, colors::black);
	XFillRectangle(_display, _window, _gc, x, y, x+50, y+50);
	x = 1;
	y += 50;

	XSetForeground(_display, _gc, colors::bright_blue);
	XFillRectangle(_display, _window, _gc, x, y, x+50, y+50);
	x += 50;

	XSetForeground(_display, _gc, colors::blue);
	XFillRectangle(_display, _window, _gc, x, y, x+50, y+50);
	x += 50;

	XSetForeground(_display, _gc, colors::dark_blue);
	XFillRectangle(_display, _window, _gc, x, y, x+50, y+50);
	x += 50;

	XSetForeground(_display, _gc, colors::black);
	XFillRectangle(_display, _window, _gc, x, y, x+50, y+50);
	XFillRectangle(_display, _window, _gc, x, y, x+50, y+50);
	x = 1;
	y += 50;

	XFillRectangle(_display, _window, _gc, x, y, x+50, y+50);
	x += 50;

	XFillRectangle(_display, _window, _gc, x, y, x+50, y+50);
	x += 50;

	XFillRectangle(_display, _window, _gc, x, y, x+50, y+50);
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
