#ifndef __GRAPHICS_X11_H__
#define __GRAPHICS_X11_H__

#include <map>
#include <string>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <graphics_base.h>

namespace graphics_ns_base {

namespace graphics_ns_x11 {

class graphics : graphics_base
{
public:

	typedef enum
	{
		white = 0,
		grey,
		dark_grey,
		black,

		bright_red,
		red,
		dark_red,

		bright_orange,
		orange,
		dark_orange,

		bright_yellow,
		yellow,
		dark_yellow,

		bright_green,
		green,
		dark_green,

		bright_blue,
		blue,
		dark_blue,

		bright_purple,
		purple,
		dark_purple,
	} color_idx_e;

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
	void init_colors();

	typedef struct {
		std::string name;
		unsigned long val;
	} color_data_t;

	typedef std::map<color_idx_e, color_data_t> color_t;
	color_t *_colors;

public:

	graphics();
	graphics(const char*);
	graphics(int, int);
	graphics(int, int, const char*);
	~graphics();

	unsigned long get_color_val(color_idx_e) const;
	std::string get_color_name(color_idx_e) const;
	void draw_rect(int, int, int, int, color_idx_e) const;
	void draw_something() const;
	void refresh() const;
	const Display* get_display() const {return _display;};
};

} // namespace graphics_ns_x11

} // namespace graphics_ns_base

#endif // __GRAPHICS_X11_H__