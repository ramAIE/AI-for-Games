#include "Edge.h"
#include "Node.h"


Edge::Edge() : nodeB(nullptr), cost(0) {}


Node * Edge::GetNodeB()
{
	return nodeB;
}

void Edge::SetNodeB(Node * node)
{
	//node = new Node();
	nodeB = node;
}

float Edge::GetCost()
{
	return 0.0f;
}

void Edge::SetCost(float cost)
{
}


Edge::~Edge()
{
}
