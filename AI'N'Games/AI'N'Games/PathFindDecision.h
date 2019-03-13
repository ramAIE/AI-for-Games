#pragma once
#include "Decision.h"
#include <vector>

class Node;

class PathFindDecision : public Decision
{
public:
	PathFindDecision();
	PathFindDecision(std::vector<Node*> target);
	virtual void MakeDecision(Agent* agent, float deltaTime);
	~PathFindDecision();
private:
	std::vector<Node*> m_target;
	Node* m_nextNode;
};

