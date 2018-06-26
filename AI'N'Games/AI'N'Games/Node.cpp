#include "Node.h"
#include "Edge.h"


Node::Node()
{
	position = Vector2(0, 0);
}

void Node::SetConnection(Edge * edge)
{
	connections.push_back(edge);
}

std::vector<Edge*> Node::GetConnections()
{
	return connections;
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
