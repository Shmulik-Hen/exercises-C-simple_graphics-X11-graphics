#ifndef __GRAPHICS_BASE_H__
#define __GRAPHICS_BASE_H__

namespace graphics_ns_base {

class graphics_base
{
private:
	virtual void init_graphics() = 0;

public:
	typedef enum
	{
		black = 0,
		white,
		grey,
		dark_grey,

		bright_red,
		red,
		dark_red,

		bright_orange,
		orange,
		dark_orange,

		bright_yellow,
		yellow,
		dark_yellow,

		bright_green,
		green,
		dark_green,

		bright_blue,
		blue,
		dark_blue,

		bright_purple,
		purple,
		dark_purple,

		__last_color__ // "private"
	} color_idx;

	typedef enum
	{
		BOUNDS_OK   	= 0x00000000,
		BOUNDS_X_OUT    = 0x00000001,
		BOUNDS_Y_OUT    = 0x00000002,
		BOUNDS_BOTH_OUT	= (BOUNDS_X_OUT | BOUNDS_Y_OUT)
	} bounds_status;

	typedef struct {
		int x;
		int y;
	} dot;

	virtual bounds_status in_bounds(dot) const = 0;
	virtual void refresh() const = 0;
};

} // namespace graphics_ns_base

#endif // __GRAPHICS_BASE_H__
