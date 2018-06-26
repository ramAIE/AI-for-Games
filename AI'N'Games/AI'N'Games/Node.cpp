#include "Node.h"
#include "Edge.h"


Node::Node()
{
	position = Vector2(0, 0);
}

void Node::SetConnection(Node * node, Edge * edge)
{
	node->connections.push_back(edge);
}

Vector2 Node::GetPosition()
{
	return position;
}

void Node::SetPosition(Vector2 pos)
{
	this->position = pos;
}


Node::~Node()
{
	for (auto edge : connections)
		delete edge;
}
