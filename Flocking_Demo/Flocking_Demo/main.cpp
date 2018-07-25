#include "Flocking_DemoApp.h"

int main() {
	
	// allocation
	auto app = new Flocking_DemoApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}