#include "Flocking_DemoApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Agent.h"
#include "SteeringBehaviour.h"
#include "CohesionForce.h"
#include "SeparationForce.h"
#include "AlignmentForce.h"
#include "WanderForce.h"
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

	for (int i = 0; i < 100; ++i) {
		Vector3 boidPos = Vector3(rand() / (float)RAND_MAX * getWindowWidth(), rand() / (float)RAND_MAX * getWindowHeight(), 1);
		Agent* boid = new Agent(boidTexture, boidPos);
		m_AIboids.push_back(boid);
	}

	m_steeringBehaviour = new SteeringBehaviour();

	WanderForce* wander = new WanderForce();
	wander->SetDistance(50.0f);
	wander->SetRadius(5.0f);
	wander->SetWanderAngle(3.14f);

	//SeekForce* seek = new SeekForce();
	//seek->setTarget(aie::Input::getInstance(), Vector3(100, 200,1));

	CohesionForce* cohesion = new CohesionForce();
	cohesion->setBoids(m_AIboids);
	cohesion->setRadius(200.0f);

	SeparationForce* separation = new SeparationForce();
	separation->setBoids(m_AIboids);
	separation->setRadius(200.0f);

	AlignmentForce* alignment = new AlignmentForce();
	alignment->setBoids(m_AIboids);
	alignment->setRadius(200.0f);

	m_steeringBehaviour->addForce(wander, 1.0f);
	m_steeringBehaviour->addForce(cohesion, 1.0f);
	m_steeringBehaviour->addForce(alignment, 3.0f);
	m_steeringBehaviour->addForce(separation, 5.0f);

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