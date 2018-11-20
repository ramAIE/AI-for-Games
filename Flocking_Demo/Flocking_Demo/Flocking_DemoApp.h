#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <vector>

class Agent;
class SteeringBehaviour;
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

	std::vector<Agent*> m_AIboids;

	SteeringBehaviour*	m_steeringBehaviour;
};