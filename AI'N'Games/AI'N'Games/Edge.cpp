#include "Edge.h"
#include "Node.h"


Edge::Edge() : nodeA(nullptr), nodeB(nullptr) {}

Node * Edge::GetNodeA()
{
	return nodeA;
}

Node * Edge::GetNodeB()
{
	return nodeB;
}

void Edge::SetNodeA(Node * node)
{
	nodeA = node;
}

void Edge::SetNodeB(Node * node)
{
	nodeB = node;
}


Edge::~Edge()
{
	delete nodeA;
	delete nodeB;
}
