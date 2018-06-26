#pragma once
class Node;
class Edge
{
public:
	Edge();
	Node* GetNodeA();
	Node* GetNodeB();
	void SetNodeA(Node* node);
	void SetNodeB(Node* node);
	~Edge();
private:
	Node* nodeA;
	Node* nodeB;

};

