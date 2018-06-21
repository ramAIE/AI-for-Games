#include "AI_N_GamesApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Agent.h"
#include <Vector2.h>
#include "KeyboardController.h"

AI_N_GamesApp::AI_N_GamesApp() {

}

AI_N_GamesApp::~AI_N_GamesApp() {

}

bool AI_N_GamesApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	Agent* ship = new Agent(new aie::Texture("../bin/textures/ship.png"), Vector2(100.0f, 100.0f));
	ship->AddBehavior(new KeyboardController(aie::Input::getInstance()));

	m_agents.push_back(ship);

	return true;
}

void AI_N_GamesApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void AI_N_GamesApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	for (auto agent : m_agents)
		agent->update(deltaTime);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void AI_N_GamesApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	for (auto agent : m_agents)
		agent->draw(m_2dRenderer);
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}