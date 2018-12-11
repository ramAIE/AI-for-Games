#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <vector>

#define _AGENTSIZE 100
#define _OBSTACLESIZE 20

class Agent;
class SteeringBehaviour;
class Circle;

class Flocking_DemoApp : public aie::Application {
public:

	Flocking_DemoApp();
	virtual ~Flocking_DemoApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	// AI agents
	std::vector<Agent*> m_AIboids;
	// steering behaviours for AI
	SteeringBehaviour*	m_steeringBehaviour;

	// Obstacles on level
	std::vector<Circle> m_obstacles;
};