#ifndef __RUNNER_X11_H__
#define __RUNNER_X11_H__

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <graphics_x11.h>

namespace runner_ns_x11 {

using namespace graphics_ns_base::graphics_ns_x11;

class runner //: runner_base
{
private:
	const graphics* _g {NULL};
	bool _is_running {false};

	bool get_event(XEvent&) const;
	bool handle_event(XEvent&) const;

public:
	runner(graphics&);
	void run();
};

} // namespace runner_ns_x11

#endif // __RUNNER_X11_H__