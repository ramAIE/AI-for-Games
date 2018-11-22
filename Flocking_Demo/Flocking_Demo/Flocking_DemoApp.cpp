#include "Flocking_DemoApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Agent.h"
#include "SteeringBehaviour.h"
#include "CohesionForce.h"
#include <random>

Flocking_DemoApp::Flocking_DemoApp() {

}

Flocking_DemoApp::~Flocking_DemoApp() {

}

bool Flocking_DemoApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	aie::Texture* boidTexture = new aie::Texture("../bin/textures/boid.png");

	for (int i = 0; i < 20; ++i) {
		Vector3 boidPos = Vector3(rand() / (float)RAND_MAX * getWindowWidth(), rand() / (float)RAND_MAX * getWindowHeight(), 1);
		Agent* boid = new Agent(boidTexture, boidPos);
		m_AIboids.push_back(boid);
	}

	m_steeringBehaviour = new SteeringBehaviour();
	CohesionForce* cohesion = new CohesionForce();
	cohesion->setBoids(m_AIboids);
	cohesion->setRadius(1000.0f);
	m_steeringBehaviour->addForce(cohesion);

	for (auto b : m_AIboids) {
		b->addBehaviour(m_steeringBehaviour);
	}

	return true;
}

void Flocking_DemoApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void Flocking_DemoApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	for (auto b : m_AIboids)
		b->update(deltaTime);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Flocking_DemoApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	for (auto b : m_AIboids) {
		b->draw(m_2dRenderer);
	}
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}