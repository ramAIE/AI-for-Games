#include "WanderDecision.h"
#include "Agent.h"
#include <iostream>


WanderDecision::WanderDecision()
{
}

void WanderDecision::MakeDecision(Agent * agent, float deltaTime)
{
	std::cout << "wandering" << std::endl;
	agent->AddForce(Vector2(-10, -10));
}


WanderDecision::~WanderDecision()
{
}
