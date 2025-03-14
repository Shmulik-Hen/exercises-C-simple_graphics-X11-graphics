#include <chrono>
#include <thread>
#include <iostream>
#include <runner_x11.h>

namespace runner_ns_x11 {

using namespace graphics_ns_base;
using namespace graphics_ns_base::graphics_ns_x11;

#define KEY_ESCAPE     9
#define KEY_SPACEBAR  65
#define KEY_UP       111
#define KEY_RIGHT    114
#define KEY_DOWN     116
#define KEY_LEFT     113

bool runner::get_event(XEvent& event) const
{
	if (XPending((Display*)_g->get_display())) {
		XNextEvent((Display*)_g->get_display(), &event);
		return true;
	}

	return false;
};

bool runner::handle_event(XEvent& event) const
{
	bool ret = true;

	switch (event.type) {
	case Expose:
		DBG("Got expose event");
		if (event.xexpose.count == 0) {
			draw();
		}
		break;
	case KeyPress:
		DBG("Got key press event");

		switch (event.xkey.keycode) {
		case KEY_SPACEBAR:
			DBG("Got space key");
			_g->refresh();
			break;
		case KEY_ESCAPE:
			DBG("Got escape key");
			ret = false;
		}
		break;
	case ButtonPress:
		DBG("Got button press event");
		break;
	default:
		DBG("Got unsupported event");
		ret = false;
		break;
	}

	return ret;
};

void runner::draw() const
{
	int width = _g->get_width() / 10;
	int height = _g->get_height() / 10;
	graphics_base::point tl{_x, _y};
	graphics_base::size sz{width, height};

	_g->demo();
	_g->draw_rect(tl, sz, graphics_base::bright_red, false);
};

runner::runner(graphics& g) :
	_g{&g},
	_is_running{true}
{
};

void runner::run()
{
	XEvent event;

	while (_is_running) {
		if (get_event(event)) {
			_is_running = handle_event(event);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
};

} // namespace runner_ns_x11
