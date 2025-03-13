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
private:
	typedef struct {
		std::string name;
		unsigned long val;
	} color_data_t;

	typedef std::map<color_idx, color_data_t> color_t;

	Display* _display {NULL};
	GC _gc {NULL};
	Visual* _visual {NULL};
	Window _window;
	Window _root;
	int _screen;
	Colormap _cmap;
	const int _width;
	const int _height;
	const color_idx _bg {black};
	const color_idx _fg {white};
	const char* _name;
	color_t* _colors {NULL};

	void init_graphics();
	void init_colors();
	bounds_status in_bounds(dot) const;

public:
	graphics();
	graphics(const char*);
	graphics(int, int);
	graphics(int, int, const char*);
	~graphics();

	const Display* get_display() const {return _display;};
	unsigned long get_color_val(color_idx) const;
	std::string get_color_name(color_idx) const;
	void draw_rect(dot, dot, color_idx) const;
	void draw_text(dot, std::string, color_idx) const;
	void demo() const;
	void refresh() const;
};

} // namespace graphics_ns_x11

} // namespace graphics_ns_base

#endif // __GRAPHICS_X11_H__