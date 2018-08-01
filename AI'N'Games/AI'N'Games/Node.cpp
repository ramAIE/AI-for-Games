#include "Node.h"
#include "Edge.h"


Node::Node()
{
	parent = nullptr;
	visited = false;
	position = Vector2(0, 0);
}

void Node::SetConnection(Node * a, Node * b, float cost)
{
	Edge* edge = new Edge();
	edge->SetNodeB(b);
	edge->SetCost(cost);
	a->connections.push_back(edge);
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

void Node::Visited(bool isVisited)
{
	visited = isVisited;
}

bool Node::CheckVisited()
{
	return visited;
}

void Node::SetParent(Node * parent)
{
	this->parent = parent;
}

Node * Node::GetParent()
{
	return parent;
}

void Node::SetGScore(float score)
{
	gScore = score;
}

float Node::GetGScore()
{
	return gScore;
}

void Node::SetFScore(float score)
{
	fScore = score;
}

float Node::GetFScore()
{
	return fScore;
}

bool Node::CompareGScore(Node * a, Node * b)
{
	return a->gScore < b->gScore;
}

bool Node::CompareFScore(Node * a, Node * b)
{
	return a->fScore < b->fScore;
}


Node::~Node()
{
	for (auto& edge : connections)
		delete edge;
	
	//delete parent;
}
