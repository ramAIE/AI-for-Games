#pragma once
#include "Decision.h"
#include <list>
class Node;
class PathFindDecision : public Decision
{
public:
	PathFindDecision();
	PathFindDecision(std::list<Node*> target);
	virtual void MakeDecision(Agent* agent, float deltaTime);
	~PathFindDecision();
private:
	std::list<Node*> target;
};

