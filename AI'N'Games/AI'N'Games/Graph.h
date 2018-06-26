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
	~Graph();
private:
	std::vector<Node*> nodes;
};

