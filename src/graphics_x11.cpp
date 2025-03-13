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

#define MAXC 0xFF
#define MIDC 0x7F
#define LOWC 0x3F
#define MINC 0x00

const int DEFAULT_WIDTH  = 800;
const int DEFAULT_HEIGHT = 600;
const char* DEFAULT_NAME = "Graphics_X11";

using namespace graphics_ns_base;

void graphics::init_colors()
{
	_colors = new color_t {
		{black,			{"black",			RGB(MINC, MINC, MINC)}},
		{white,			{"white",			RGB(MAXC, MAXC, MAXC)}},
		{grey,			{"grey",			RGB(MIDC, MIDC, MIDC)}},
		{dark_grey,		{"dark_grey",		RGB(LOWC, LOWC, LOWC)}},

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
								  get_color_val(_fg), get_color_val(_bg));
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
};

graphics_base::bounds_status graphics::in_bounds(dot p) const
{
	int rc = BOUNDS_OK;

	if (p.x < 0 || p.x >= _width)
		rc |= BOUNDS_X_OUT;

	if (p.y < 0 || p.y >= _height)
		rc |= BOUNDS_Y_OUT;

	return (graphics_base::bounds_status)rc;
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

	if (_colors) {
		delete _colors;
	}
};

void graphics::refresh() const
{
	XEvent ev;
	Window root;
	unsigned int border_width, depth;

	XGetGeometry(_display, _window, &root,
				 &ev.xexpose.x, &ev.xexpose.y,
				 (unsigned int*)&ev.xexpose.width,
				 (unsigned int*)&ev.xexpose.height,
				 &border_width, &depth);

	ev.xexpose.type = Expose;
	ev.xexpose.display = _display;
	ev.xexpose.window = _window;
	ev.xexpose.count = 0;

	XClearWindow(_display, _window);
	XSendEvent(_display, _window, false, ExposureMask, &ev);
};

unsigned long graphics::get_color_val(color_idx i) const
{
	return _colors->find(i)->second.val;
};

std::string graphics::get_color_name(color_idx i) const
{
	return _colors->find(i)->second.name;
};

void graphics::draw_rect(dot tl, dot br, color_idx i) const
{
#ifdef DEBUG_MODE
	std::string s = get_color_name(i) + SEP;
	int len = std::max((int)s.length(), 15);

	std::cout << RECT_PFX
		<< DEC(i, 2) << SEP << STR(s, len)
		<< DEC(tl.x, 4) << SEP << DEC(tl.y, 4) << SEP
		<< DEC(br.x, 4) << SEP << DEC(br.y, 4) << SEP
		<< HEX(get_color_val(i), 8) << std::endl;
#endif //DEBUG_MODE

	if (in_bounds(tl) != BOUNDS_OK || in_bounds(br) != BOUNDS_OK) {
		DBG("Out of bounds");
		return;
	}

	XSetForeground(_display, _gc, get_color_val(i));
	XFillRectangle(_display, _window, _gc, tl.x, tl.y, br.x, br.y);
};

void graphics::draw_text(dot p, std::string s, color_idx i) const
{
#ifdef DEBUG_MODE
	std::string s2 = get_color_name(i) + SEP;
	int len = std::max((int)s2.length(), 15);

	std::cout << TEXT_PFX
		<< DEC(i, 2) << SEP << STR(s2, len)
		<< DEC(p.x, 4) << SEP << DEC(p.y, 4) << SEP
		<< HEX(get_color_val(i), 8) << std::endl;
#endif //DEBUG_MODE

	if (in_bounds(p) != BOUNDS_OK) {
		DBG("Out of bounds");
		return;
	}

	XTextItem txt{(char*)s.c_str(), (int)s.length(), 1, None};
	XSetForeground(_display, _gc, get_color_val(i));
	XDrawText(_display, _window, _gc, p.x, p.y, &txt, 1);
};

void graphics::demo() const
{
	color_t::iterator it;
	int x = 0, y = 0, gap = 50, rc;
	dot tl, br, p;

	for (it = _colors->begin(); it != _colors->end(); x+=gap, it++) {
		std::string s = std::to_string(it->first);
		color_idx c = white;

		if (it->first == white || it->first == bright_yellow)
			c = black;

		tl = {x, y};
		br = {x+gap, y+gap};
		rc = in_bounds(br);
		if (it->first && ((it->first%10) == 0)) {
			rc = BOUNDS_X_OUT;
		}

		switch (rc)
		{
		case BOUNDS_OK:
			DBG("BOUNDS_OK");
			p = {x + 10, y + 10};
			draw_rect(tl, br, it->first);
			draw_text(p, s, c);
			break;
		case BOUNDS_X_OUT:
			DBG("BOUNDS_X_OUT");
			// blank to the end of the row - why? what's wrong with X11?
			p = {_width-1, y+gap};
			draw_rect(tl, p, _bg);

			// start in a new row
			y += gap;
			x = 0;
			tl = {x, y};
			br = {x+gap, y+gap};
			p = {x + 10, y + 10};
			draw_rect(tl, br, it->first);
			draw_text(p, s, c);
			break;
		case BOUNDS_Y_OUT:
			DBG("BOUNDS_Y_OUT");
			return;
		case BOUNDS_BOTH_OUT:
			DBG("BOUNDS_BOTH_OUT");
			return;
		default:
			DBG("BOUNDS_BOTH_OUT");
			return;
		}
	}

	// blank from next square to the end of the row - again, why?
	tl = {x, y};
	br = {_width-1, y+gap};
	draw_rect(tl, br, _bg);

	// blank from next row to the bottom
	y += gap;
	x = 0;
	tl = {x, y};
	br = {_width-1, _height-1};
	draw_rect(tl, br, _bg);
};

} // namespace graphics_ns_x11

} // namespace graphics_ns_base
