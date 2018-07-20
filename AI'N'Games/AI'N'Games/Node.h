#pragma once
#include <Vector2.h>
#include <vector>

class Edge;
class Node
{
public:
	Node();
	// connect nodes
	void SetConnection(Node * a, Node * b, float cost);
	std::vector<Edge*> GetConnections();
	// position of the node
	Vector2 GetPosition();
	void SetPosition(Vector2 pos);
	// check if the node has been visited
	void Visited(bool isVisited);
	bool CheckVisited();
	// Get the parent of the node
	void SetParent(Node* parent);
	Node* GetParent();
	// GScore for the Node
	void SetGScore(float score);
	float GetGScore();
	// F-Score for the node
	void SetFScore(float score);
	float GetFScore();

	static bool CompareGScore(Node * a, Node * b);
	static bool CompareFScore(Node * a, Node * b);

	bool highlighted;

	~Node();

private:
	std::vector<Edge*> connections;
	Vector2 position;
	Node* parent;
	bool visited;
	float gScore;
	float fScore;
};

