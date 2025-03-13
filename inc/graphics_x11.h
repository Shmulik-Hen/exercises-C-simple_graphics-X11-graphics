#ifndef __GRAPHICS_X11_H__
#define __GRAPHICS_X11_H__

#include <map>
#include <string>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <graphics_base.h>

namespace graphics_ns_base {

namespace graphics_ns_x11 {

#ifdef DEBUG_MODE
const std::string HEX_PFX	= "0x";
const std::string SEP		= ", ";
const std::string RECT_PFX	= "rect: ";
const std::string TEXT_PFX	= "text: ";

#define HEX(n, w) HEX_PFX << std::hex << std::setw((w)) << std::setfill('0') << std::right << (n)
#define DEC(n, w) std::dec << std::setw((w)) << std::setfill(' ') << std::right << (n)
#define STR(s, w) std::setw((w)) << std::setfill(' ') << std::left << (s)
#define DBG(s)    std::cout << STR((s), 1) << std::endl
#else
#define DBG(...)
#endif //DEBUG_MODE

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

	typedef struct {
		int x;
		int y;
	} dot;

private:

	Display* _display {NULL};
	GC _gc {NULL};
	Visual* _visual {NULL};
	Window _window;
	Window _root;
	int _screen;
	Colormap _cmap;
	const int _width;
	const int _height;
	color_idx_e _bg {black};
	color_idx_e _fg {white};
	const char* _name;

	void init_graphics();
	void init_colors();
	int in_bounds(dot) const;

	typedef struct {
		std::string name;
		unsigned long val;
	} color_data_t;

	typedef std::map<color_idx_e, color_data_t> color_t;
	color_t* _colors;

public:

	graphics();
	graphics(const char*);
	graphics(int, int);
	graphics(int, int, const char*);
	~graphics();

	unsigned long get_color_val(color_idx_e) const;
	std::string get_color_name(color_idx_e) const;
	void draw_rect(dot, dot, color_idx_e) const;
	void draw_text(dot, std::string, color_idx_e) const;
	void draw_something() const;
	void refresh() const;
	const Display* get_display() const {return _display;};
};

} // namespace graphics_ns_x11

} // namespace graphics_ns_base

#endif // __GRAPHICS_X11_H__