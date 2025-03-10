#include <chrono>
#include <thread>
#include <iostream>
#include <runner_x11.h>

namespace runner_ns_x11 {

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
	switch (event.type) {
	case Expose:
		std::cout << "Got expose event" << std::endl;
		if (event.xexpose.count == 0) {
			_g->draw_something();
		}
		return true;
	case KeyPress:
		std::cout << "Got key press event" << std::endl;
		return false;
	case ButtonPress:
		std::cout << "Got button press event" << std::endl;
		return false;
	default:
		std::cout << "Got unsupported event" << std::endl;
		return false;
	}
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
