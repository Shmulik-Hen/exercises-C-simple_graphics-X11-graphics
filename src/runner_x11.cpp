#include <chrono>
#include <thread>
#include <runner_x11.h>
#include <graphics_x11.h>

// namespace runner_ns_base {

// namespace runner_ns_x11 {

bool runner::get_event(graphics& g, XEvent& event)
{
	if (XPending(g._display)) {
		XNextEvent(g._display, &event);
		return true;
	}

	return false;
};

void runner::handle_event(graphics& g, XEvent& event, bool &flag) {
	switch (event.type) {
	case Expose:
		if (event.xexpose.count == 0) {
			g.refresh();
		}
		break;
	case KeyPress:
	case ButtonPress:
		flag = false;
		break;
	}
};

void runner::run(graphics& g)
{
	XEvent event;

	while (_is_running) {
		if (get_event(g, event)) {
			handle_event(g, event, _is_running);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
};


// };

// } // namespace runner_ns_x11

// } // namespace runner_ns_base
