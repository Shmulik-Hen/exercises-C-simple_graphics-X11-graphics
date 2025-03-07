namespace graphics_ns_base {

class graphics_base {
private:
	virtual void start() = 0;
	virtual void draw() = 0;

public:
	virtual void run() = 0;
};

} // namespace graphics_ns_base
