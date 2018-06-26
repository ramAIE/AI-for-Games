#pragma once
#include <Vector2.h>
#include <vector>

class Edge;
class Node
{
public:
	Node();
	void SetConnection(Edge* edge);
	std::vector<Edge*> GetConnections();
	Vector2 GetPosition();
	void SetPosition(Vector2 pos);
	~Node();

private:
	Vector2 position;
	std::vector<Edge*> connections;
};

