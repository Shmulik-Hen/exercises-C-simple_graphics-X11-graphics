#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <graphics_x11.h>

namespace graphics_ns_base {

namespace graphics_ns_x11 {

#define GMASK 0x00FFFFFF
#define CMASK 0xFF

#define R(x) (((x) & CMASK) << 16)
#define G(x) (((x) & CMASK) << 8)
#define B(x) ((x) & CMASK)
#define RGB(r, g, b) ((R(r) + G(g) + B(b)) & GMASK)

#define MAXC  0xFF
#define MIDC  0x7F
#define LOWC  0x3F
#define MINC  0x00

#define HEX(n, w) "0x" << std::hex << std::setw((w)) << std::setfill('0') << std::right << (n)
#define DEC(n, w) std::dec << std::setw((w)) << std::setfill(' ') << std::right << (n)
#define STR(s, w) std::setw((w)) << std::left << (s)

const int DEFAULT_WIDTH  = 800;
const int DEFAULT_HEIGHT = 600;
const char* DEFAULT_NAME = "Display_X11";

void graphics::init_colors()
{
	_colors = new color_t {
		{white,			{"white",			RGB(MAXC, MAXC, MAXC)}},
		{grey,			{"grey",			RGB(MIDC, MIDC, MIDC)}},
		{dark_grey,		{"dark_grey",		RGB(LOWC, LOWC, LOWC)}},
		{black,			{"black",			RGB(MINC, MINC, MINC)}},

		{bright_red,	{"bright_red",		RGB(MAXC, MINC, MINC)}},
		{red,			{"red",				RGB(MIDC, MINC, MINC)}},
		{dark_red,		{"dark_red",		RGB(LOWC, MINC, MINC)}},

		{bright_orange,	{"bright_orange",	RGB(MAXC, LOWC, MINC)}},
		{orange,		{"orange",			RGB(MIDC, LOWC, MINC)}},
		{dark_orange,	{"dark_orange",		RGB(LOWC, LOWC, MINC)}},

		{bright_yellow,	{"bright_yellow",	RGB(MAXC, MAXC, MINC)}},
		{yellow,		{"yellow",			RGB(MIDC, MIDC, MINC)}},
		{dark_yellow,	{"dark_yellow",		RGB(LOWC, LOWC, MINC)}},

		{bright_green,	{"bright_green",	RGB(MINC, MAXC, MINC)}},
		{green,			{"green",			RGB(MINC, MIDC, MINC)}},
		{dark_green,	{"dark_green",		RGB(MINC, LOWC, MINC)}},

		{bright_blue,	{"bright_blue",		RGB(MINC, MINC, MAXC)}},
		{blue,			{"blue",			RGB(MINC, MINC, MIDC)}},
		{dark_blue,		{"dark_blue",		RGB(MINC, MINC, LOWC)}},

		{bright_purple,	{"bright_purple",	RGB(MAXC, MINC, MAXC)}},
		{purple,		{"purple",			RGB(MIDC, MINC, MIDC)}},
		{dark_purple,	{"dark_purple",		RGB(LOWC, MINC, LOWC)}},
	};
};

void graphics::init_graphics()
{
	int rc;

	init_colors();

	_display = XOpenDisplay(NULL);
	if (!_display) {
		throw std::runtime_error("Unable to open the display");
	}

	_screen = DefaultScreen(_display);
	_visual = DefaultVisualOfScreen(ScreenOfDisplay(_display, _screen));
	_root = RootWindow(_display, _screen);
	_cmap = DefaultColormap(_display, _screen);

	_window = XCreateSimpleWindow(_display, _root, 0, 0, _width, _height, 1,
								  get_color_val(white),
								  get_color_val(black));
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

	rc = XSetBackground(_display, _gc, get_color_val(black));
	if (!rc) {
		throw std::runtime_error("Unable to set background");
	}

	rc = XSetForeground(_display, _gc, get_color_val(white));
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

void graphics::refresh() const
{
};

unsigned long graphics::get_color_val(color_idx_e i) const
{
	color_t::iterator it = _colors->find(i);
	return it->second.val;
};

std::string graphics::get_color_name(color_idx_e i) const
{
	color_t::iterator it = _colors->find(i);
	return it->second.name;
};

void graphics::draw_rect(int x, int y, int w, int h, color_idx_e i) const
{
	std::cout << STR("Drawing a rectangle from: ", 1)
		<< DEC(x, 3) << DEC(y, 3)
		<< STR(" to: ", 1) << DEC(x+w, 3) << DEC(y+h, 3)
		<< STR(" color index: ", 1) << DEC(i, 3)
		<< STR(" color name: ", 1) << STR(get_color_name(i), 20)
		<< STR(" color val: ", 1) << HEX(get_color_val(i), 8) << std::endl;
	XSetForeground(_display, _gc, get_color_val(i));
	XFillRectangle(_display, _window, _gc, x, y, w, h);
};

void graphics::draw_something() const
{
	color_t::iterator it;
	int x = 0, y = 0;

	for (it = _colors->begin(); it != _colors->end(); x+=20, it++) {
		draw_rect(x, y, 20, 20, it->first);
	}
};

} // namespace graphics_ns_x11

} // namespace graphics_ns_base
