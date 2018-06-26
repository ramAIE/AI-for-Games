#pragma once
#include "Edge.h"
#include "Node.h"

namespace aie
{
	class Renderer2D;
}

class Graph
{
public:
	Graph();
	void AddNode(Node* node);
	void ConnectNode(Node* a, Node* b);
	void draw(aie::Renderer2D* renderer);
	std::vector<Node*> GetNodes();
	// depth first Search
	std::vector<Node*> DFS(Node* startNode, Node* endNode);
	// Djikstra PathFinding Algorithm
	std::vector<Node*> DjikstraSearch(Node* startNode, Node* endNode);

	~Graph();
private:
	std::vector<Node*> nodes;
};

