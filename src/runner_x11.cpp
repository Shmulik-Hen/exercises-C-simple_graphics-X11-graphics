#include <chrono>
#include <thread>
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
		if (event.xexpose.count == 0) {
			_g->refresh();
		}
		break;
	case KeyPress:
	case ButtonPress:
		return false;
	}

	return true;
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
