#ifndef __GRAPHICS_X11_H__
#define __GRAPHICS_X11_H__

#include <map>
#include <string>
#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <graphics_base.h>

const std::string ERR_PFX	= "Error: ";
const std::string WARN_PFX	= "Warning: ";

#define ERR(s)	std::cout << ERR_PFX << (s) << std::endl;
#define WARN(s) std::cout << WARN_PFX << (s) << std::endl;

#ifdef DEBUG_GRFX
#include <iostream>
#include <iomanip>

const std::string DBG_PFX	= "Debug: ";
const std::string HEX_PFX	= "0x";
const std::string SEP		= ", ";

#define HEX(n, w) HEX_PFX << std::hex << std::setw((w)) << std::setfill('0') << std::right << (n)
#define DEC(n, w) std::dec << std::setw((w)) << std::setfill(' ') << std::right << (n)
#define STR(s, w) std::setw((w)) << std::setfill(' ') << std::left << (s)
#define DBG(s)    std::cout << STR(DBG_PFX, 1) << STR((s), 1) << std::endl
#else
#define DBG(...)
#endif //DEBUG_GRFX

namespace graphics_ns_base {

namespace graphics_ns_x11 {

class graphics : graphics_base
{
private:
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

	void init_colors();
	void init_graphics();

public:
	graphics();
	graphics(const char*);
	graphics(int, int);
	graphics(int, int, const char*);
	~graphics();

	// implement pure virtuals
	inline const bounds_status is_in_bounds(dot) const;
	inline const bool is_valid_color(color_idx) const;
	inline const int get_num_colors() const {return __last_color__;};
	inline const unsigned long get_color_val(color_idx) const;
	inline const std::string get_color_name(color_idx) const;
	void draw_pixel(dot, color_idx) const;
	void draw_line(dot, dot, color_idx) const;
	void draw_rect(dot, dot, color_idx, bool) const;
	void draw_text(dot, std::string, color_idx) const;
	void refresh() const;

	inline const Display* get_display() const {return _display;};
	inline const bool is_bright_color(color_idx) const;
	void demo() const;
};

} // namespace graphics_ns_x11

} // namespace graphics_ns_base

#endif // __GRAPHICS_X11_H__