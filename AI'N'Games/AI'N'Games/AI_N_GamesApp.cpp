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

AI_N_GamesApp::AI_N_GamesApp() {

}

AI_N_GamesApp::~AI_N_GamesApp() {

}

bool AI_N_GamesApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);
	// initializing the graph
	m_graph = new Graph();

	Agent* ship = new Agent(new aie::Texture("../bin/textures/ship.png"), Vector2(100.0f, 100.0f));
	Agent* aiAgent = new Agent(new aie::Texture("../bin/textures/car.png"), Vector2(600.0f, 600.0f));
	ship->AddBehavior(new KeyboardController(aie::Input::getInstance()));

	BooleanDecision* rootNode = new BooleanDecision();
	BooleanDecision* withinAttackRange = new BooleanDecision();
	SeekDecision* seekDecision = new SeekDecision(ship);
	WanderDecision* wanderDecision = new WanderDecision();

	rootNode->CheckWithinRange(aiAgent, ship, 500.0f);
	rootNode->trueDecision = seekDecision;
	rootNode->falseDecision = wanderDecision;

	//withinAttackRange->CheckWithinRange(aiAgent, ship, 50.0f);
	//withinAttackRange->trueDecision = attackDecision;
	//withinAttackRange->falseDecision = seekDecision;

	aiAgent->AddBehavior(rootNode);

	m_agents.push_back(ship);
	m_agents.push_back(aiAgent);

	// adding nodes to the graph
	for (int i = 0; i < 5; ++i)
	{
		Node* node = new Node();
		m_graph->AddNode(node);
	}
	// setting the position of each nodes
	m_graph->GetNodes()[0]->SetPosition(Vector2(100, 200));
	m_graph->GetNodes()[1]->SetPosition(Vector2(100, 500));
	m_graph->GetNodes()[2]->SetPosition(Vector2(200, 300));
	m_graph->GetNodes()[3]->SetPosition(Vector2(400, 500));
	m_graph->GetNodes()[4]->SetPosition(Vector2(400, 200));
	
	// connecting the nodes
	m_graph->ConnectNode(m_graph->GetNodes()[0], m_graph->GetNodes()[1]);
	m_graph->ConnectNode(m_graph->GetNodes()[1], m_graph->GetNodes()[3]);
	m_graph->ConnectNode(m_graph->GetNodes()[3], m_graph->GetNodes()[4]);
	m_graph->ConnectNode(m_graph->GetNodes()[1], m_graph->GetNodes()[2]);

	Node* startNode = m_graph->GetNodes()[0];
	Node* endNode = m_graph->GetNodes()[4];

	std::vector<Node*> nodes = m_graph->DFS(startNode, endNode);

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

	m_graph->draw(m_2dRenderer);
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}