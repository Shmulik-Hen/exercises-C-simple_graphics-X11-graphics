#include <chrono>
#include <thread>
#include <iostream>
#include <runner_x11.h>

namespace runner_ns_x11 {

#define KEY_ESCAPE     9
#define KEY_SPACEBAR  65

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
			_g->demo();
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

runner::runner(graphics& g) :
	_g {&g},
	_is_running {true}
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
