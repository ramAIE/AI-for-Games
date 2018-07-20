#include "KeyboardController.h"
#include <Input.h>
#include "Agent.h"

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
	agent->rotation = -mouseX * deltaTime;
}


KeyboardController::~KeyboardController()
{
}
