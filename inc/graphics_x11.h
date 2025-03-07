#include <stdint.h>
#include <X11/Xlib.h>
#include <graphics_base.h>

namespace graphics_ns_base {

namespace graphics_ns_x11 {

class graphics : graphics_base
{
private:
	Display *_display {NULL};
	Window _window;
	Window _root;
	GC _gc;
	uint32_t _screen;
	uint64_t _bg;
	uint64_t _fg;
	const uint32_t _width;
	const uint32_t _height;
	const char* _name;
	bool _is_running {false};

	void start();
	bool get_event(XEvent &event);
	void handle_event(XEvent &event);
	void draw();

public:
	graphics();
	graphics(const char*);
	graphics(uint32_t, uint32_t);
	graphics(uint32_t, uint32_t, const char*);
	~graphics();
	void run();
};

} // namespace graphics_ns_x11

} // namespace graphics_ns_base
