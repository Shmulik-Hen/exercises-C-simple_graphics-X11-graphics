#include <stdint.h>
#include <X11/Xlib.h>
#include <graphics_base.h>

namespace graphics_ns_base {

namespace graphics_ns_x11 {

#define CMASK 0x00FFFFFF
#define MAXC  0xFF
#define MIDC  0x7F
#define LOWC  0x3F
#define MINC  0x00

#define R(x) (((x) & MAXC) << 16)
#define G(x) (((x) & MAXC) << 8)
#define B(x) ((x) & MAXC)
#define RGB(r, g, b) ((R(r) + G(g) + B(b)) & CMASK)

class graphics : graphics_base
{
private:
	Display *_display {NULL};
	Window _window;
	Window _root;
	GC _gc;
	uint32_t _screen;
	const uint32_t _width;
	const uint32_t _height;
	const char* _name;
	bool _is_running {false};

	void start();
	bool get_event(XEvent &event);
	void handle_event(XEvent &event);
	void draw();

public:

	enum colors
	{
		black		= RGB(MINC, MINC, MINC),
		white		= RGB(MAXC, MAXC, MAXC),
		grey		= RGB(MIDC, MIDC, MIDC),
		dark_grey	= RGB(LOWC, LOWC, LOWC),

		bright_red	= RGB(MAXC, MINC, MINC),
		red			= RGB(MIDC, MINC, MINC),
		dark_red	= RGB(LOWC, MINC, MINC),

		bright_green = RGB(MINC, MAXC, MINC),
		green		 = RGB(MINC, MIDC, MINC),
		dark_green	 = RGB(MINC, LOWC, MINC),

		bright_blue	 = RGB(MINC, MINC, MAXC),
		blue		 = RGB(MINC, MINC, MIDC),
		dark_blue	 = RGB(MINC, MINC, LOWC),
	};

	graphics();
	graphics(const char*);
	graphics(uint32_t, uint32_t);
	graphics(uint32_t, uint32_t, const char*);
	~graphics();
	void run();
};

} // namespace graphics_ns_x11

} // namespace graphics_ns_base
