#include "AI_N_GamesApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Agent.h"
#include <Vector2.h>
#include "KeyboardController.h"
#include "Graph.h"
#include "BooleanDecision.h"
#include "SeekDecision.h"
#include "WanderDecision.h"
#include "ObstacleAvoidance.h"

AI_N_GamesApp::AI_N_GamesApp() {

}

AI_N_GamesApp::~AI_N_GamesApp() {

}

bool AI_N_GamesApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	// setting up the graphs
	m_graph = new Graph();
	SetGraph();

	// pathfinding using A*
	Node* startNode = m_graph->GetNodes()[1];
	Node* endNode = m_graph->GetNodes()[70];

	std::vector<Node*> path = m_graph->DjikstraSearch(startNode, endNode);

	for (auto node : path)
	{
		node->highlighted = true;
	}

	Agent* ship = new Agent(new aie::Texture("../bin/textures/ship.png"), Vector2(100.0f, 100.0f));
	Agent* aiAgent = new Agent(new aie::Texture("../bin/textures/car.png"), Vector2(600.0f, 600.0f));
	ship->AddBehavior(new KeyboardController(aie::Input::getInstance()));

	BooleanDecision* rootNode = new BooleanDecision(ship, 200.0f);
	//BooleanDecision* withinAttackRange = new BooleanDecision();
	//SeekDecision* seekDecision = new SeekDecision(ship);
	WanderDecision* wanderDecision = new WanderDecision();
	ObstacleAvoidance* obstacleAvoidDecision = new ObstacleAvoidance(ship, 50.0f);

	rootNode->trueDecision = obstacleAvoidDecision;
	rootNode->falseDecision = wanderDecision;

	//withinAttackRange->CheckWithinRange(aiAgent, ship, 50.0f);
	//withinAttackRange->trueDecision = attackDecision;
	//withinAttackRange->falseDecision = seekDecision;

	aiAgent->AddDecision(rootNode);

	m_agents.push_back(ship);
	m_agents.push_back(aiAgent);


	return true;
}

void AI_N_GamesApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	delete m_graph;
	for (auto agent : m_agents)
		delete agent;
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

	// draw the graph
	m_graph->draw(m_2dRenderer);
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}

void AI_N_GamesApp::SetGraph()
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			// create a new node
			Node* node = new Node();
			// set the position of the node
			node->SetPosition(Vector2(i * 32, j * 32));
			// add the node to the graph
			m_graph->AddNode(node);
		}
	}

	for (auto a : m_graph->GetNodes())
	{
		for (auto b : m_graph->GetNodes())
		{
			if (a == b)
				continue;
			// distance between two nodes
			Vector2 dist = b->GetPosition() - a->GetPosition();
			// find the length
			float length = dist.magnitude();
			// checking if the length is within the range
			if (length <= 40.0f)
				// connect nodes
				m_graph->ConnectNode(a, b, length);
		}
	}
}
