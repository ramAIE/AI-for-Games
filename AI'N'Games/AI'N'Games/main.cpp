#include "AI_N_GamesApp.h"

int main() {
	
	// allocation
	auto app = new AI_N_GamesApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}