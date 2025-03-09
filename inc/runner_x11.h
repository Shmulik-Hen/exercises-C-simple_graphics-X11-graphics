#ifndef __RUNNER_X11_H__
#define __RUNNER_X11_H__

#include <X11/Xlib.h>
#include <X11/Xutil.h>
// #include <runner_base.h>
//#include <graphics_x11.h>

// namespace runner_ns_base {

// namespace runner_ns_x11 {

class graphics;

class runner //: runner_base
{
private:
	bool _is_running {true};
	XEvent _event;

public:
	runner() {};
	~runner() {};
	void run(graphics&);
	bool get_event(graphics&, XEvent&);
	void handle_event(graphics&, XEvent&, bool&);
};

// } // namespace runner_ns_x11

// } // namespace runner_ns_base

#endif // __RUNNER_X11_H__