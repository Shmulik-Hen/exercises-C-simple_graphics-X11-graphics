#include <chrono>
#include <thread>
#include <stdexcept>
#include <iostream>
#include <graphics_x11.h>

using namespace graphics_ns_base::graphics_ns_x11;

int main()
{
	int rc;

	try {
		graphics g;
		g.run();
	}
	catch (const std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
		return -1;
	}

	return 0;
}
