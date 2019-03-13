#include "Edge.h"
#include "Node.h"


Edge::Edge() : nodeB(nullptr), cost(0) {}


Node * Edge::GetNodeB()
{
	return nodeB;
}

void Edge::SetNodeB(Node * node)
{
	nodeB = node;
}

float Edge::GetCost()
{
	return cost;
}

void Edge::SetCost(float cost)
{
	this->cost = cost;
}


Edge::~Edge()
{
}
