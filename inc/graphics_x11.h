#ifndef __GRAPHICS_X11_H__
#define __GRAPHICS_X11_H__

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <graphics_base.h>
#include <runner_x11.h>

//namespace graphics_ns_base {

//namespace graphics_ns_x11 {

#define CMASK 0x00FFFFFF
#define MAXC  0xFF
#define MIDC  0x7F
#define LOWC  0x3F
#define MINC  0x00

#define R(x) (((x) & MAXC) << 16)
#define G(x) (((x) & MAXC) << 8)
#define B(x) ((x) & MAXC)
#define RGB(r, g, b) ((R(r) + G(g) + B(b)) & CMASK)

class runner;

class graphics : graphics_base
{
private:
	Display *_display {NULL};
	GC _gc {NULL};
	Visual *_visual {NULL};
	Window _window;
	Window _root;
	int _screen;
	Colormap _cmap;
	const int _width;
	const int _height;
	const char *_name;

	void init_graphics();

public:
	graphics();
	graphics(const char*);
	graphics(int, int);
	graphics(int, int, const char*);
	~graphics();
	void draw_something();
	void refresh();
	friend bool runner::get_event(graphics&, XEvent&);
	friend void runner::handle_event(graphics&, XEvent&, bool&);
};

//} // namespace graphics_ns_x11

//} // namespace graphics_ns_base

#endif // __GRAPHICS_X11_H__