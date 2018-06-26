#include "Graph.h"


Graph::Graph()
{
}

void Graph::AddNode(Node * node)
{
	nodes.push_back(node);
}

void Graph::ConnectNode(Node * a, Node * b)
{
	Edge* edge = new Edge();
	edge->SetNodeA(a);
	edge->SetNodeB(b);
}

void Graph::draw(aie::Renderer2D * renderer)
{

}


Graph::~Graph()
{
	for (auto node : nodes)
		delete node;
}
