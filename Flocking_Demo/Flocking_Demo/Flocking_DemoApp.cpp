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
#include "AvoidanceForce.h"
#include "SeekForce.h"
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

	// Adding AI agents to the game
	for (int i = 0; i < _AGENTSIZE; ++i) {
		Vector3 boidPos = Vector3(rand() / (float)RAND_MAX * getWindowWidth(), rand() / (float)RAND_MAX * getWindowHeight(), 1);
		Agent* boid = new Agent(boidTexture, boidPos);
		m_AIboids.push_back(boid);
	}


	m_steeringBehaviour = new SteeringBehaviour();

	/** Initialize all the steering forces required for the AI agents **/
	// Wander Force
	WanderForce* wander = new WanderForce();
	wander->SetDistance(50.0f);
	wander->SetRadius(5.0f);
	wander->SetWanderAngle(3.14f);

	/** Uncomment the below code to enable SEEK FORCE **/
	// Seek Force
	SeekForce* seek = new SeekForce();
	seek->setTarget(aie::Input::getInstance(), Vector3(100, 200,1));

	// Cohesion Force
	CohesionForce* cohesion = new CohesionForce();
	cohesion->setBoids(m_AIboids);
	cohesion->setRadius(100.0f);
	// Separation Force
	SeparationForce* separation = new SeparationForce();
	separation->setBoids(m_AIboids);
	separation->setRadius(100.0f);
	// Alignment Force
	AlignmentForce* alignment = new AlignmentForce();
	alignment->setBoids(m_AIboids);
	alignment->setRadius(100.0f);
	// Obstacle Avoidance Force
	AvoidanceForce* avoidance = new AvoidanceForce();
	// Adding obstacles to the game
	for (int i = 0; i < _OBSTACLESIZE; ++i) {
		Vector3 obstaclePos = Vector3(rand() / (float)RAND_MAX * getWindowWidth(), rand() / (float)RAND_MAX * getWindowHeight(), 1);
		Circle obstacle;
		obstacle.SetPosition(obstaclePos);
		obstacle.SetRadius(20.0f);
		m_obstacles.push_back(obstacle);
		avoidance->AddCircleObstacle(obstacle);
	}
	/*******************************************************************/

	// Add all the steering forces to the agent with weight
	m_steeringBehaviour->addForce(seek, 1.0f);
	m_steeringBehaviour->addForce(cohesion, 2.0f);
	m_steeringBehaviour->addForce(alignment, 2.0f);
	m_steeringBehaviour->addForce(separation, 3.5f);
	m_steeringBehaviour->addForce(avoidance, 10.0f);

	// add the behaviour to all the AI agents
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

	/***** draw your stuff here! *****/
	// draw obstacles
	for (auto o : m_obstacles) {
		m_2dRenderer->drawCircle(o.GetPosition().m_x, o.GetPosition().m_y, o.GetRadius());
	}

	// draw AI agents
	for (auto b : m_AIboids) {
		b->draw(m_2dRenderer);
	}
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);
	/*********************************/

	// done drawing sprites
	m_2dRenderer->end();
}