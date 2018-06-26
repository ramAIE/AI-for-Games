#pragma once
class Node;
class Edge
{
public:
	Edge();
	// Set and Get Node B
	Node* GetNodeB();
	void SetNodeB(Node* node);
	// Set and Get cost
	float GetCost();
	void SetCost(float cost);

	~Edge();
private:
	Node* nodeB;
	float cost;

};

