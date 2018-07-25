#include "KeyboardController.h"
#include <Input.h>
#include "Agent.h"
#include <iostream>

KeyboardController::KeyboardController()
{
}

KeyboardController::KeyboardController(aie::Input * input)
{
	this->input = input;
}

void KeyboardController::update(Agent * agent, float deltaTime)
{
	int mouseX = input->getMouseX();
	int mouseY = input->getMouseY();

	if (input->isKeyDown(aie::INPUT_KEY_W))
	{
		agent->AddForce(Vector2(0.0f, 100.0f));
	}
	if (input->isKeyDown(aie::INPUT_KEY_S))
	{
		agent->AddForce(Vector2(0.0f, -100.0f));
	}
	if (input->isKeyDown(aie::INPUT_KEY_A))
	{
		agent->AddForce(Vector2(-100.0f, 0.0f));
	}
	if (input->isKeyDown(aie::INPUT_KEY_D))
	{
		agent->AddForce(Vector2(100.0f, 0.0f));
	}
	// mouse position 
	Vector2 mousePos = Vector2(mouseX, mouseY);
	// direction the agent is facing
	Vector2 facing = Vector2(cosf(agent->rotation), sinf(agent->rotation));
	// length vector in current direction
	Vector2 current = facing - agent->position;
	current.normalise();
	// length vector in target direction
	Vector2 target = agent->position - mousePos;
	target.normalise();
	// find the angle by finding the dot product
	float angle = current.dot(target);
	agent->rotation = acosf(angle);
	std::cout << agent->rotation << std::endl;
}


KeyboardController::~KeyboardController()
{
}
