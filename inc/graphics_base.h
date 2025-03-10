#ifndef __GRAPHICS_BASE_H__
#define __GRAPHICS_BASE_H__

namespace graphics_ns_base {

class graphics_base {
private:

	virtual void init_graphics() = 0;

public:

	virtual void refresh() const = 0;
};

} // namespace graphics_ns_base

#endif // __GRAPHICS_BASE_H__
