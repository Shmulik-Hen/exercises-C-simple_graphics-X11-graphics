#include <stdexcept>
#include <iostream>
#include <graphics_x11.h>
#include <runner_x11.h>

// using namespace graphics_ns_base::graphics_ns_x11;
// using namespace runner_ns_base::runner_ns_x11;

int main()
{
	int rc;

	try {
		graphics g;
		runner r;
		// g.show_details();
		r.run(g);
	}
	catch (const std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
		return -1;
	}

	return 0;
}
