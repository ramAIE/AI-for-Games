#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <vector>

class Graph;
class Agent;

class AI_N_GamesApp : public aie::Application {
public:

	AI_N_GamesApp();
	virtual ~AI_N_GamesApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void SetGraph();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	Graph*				m_graph;
	std::vector<Agent*> m_agents;

};