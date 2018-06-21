#pragma once
#include "IBehavior.h"
namespace aie {
	class Input;
}
class Agent;
class KeyboardController : public IBehavior
{
public:
	KeyboardController();
	KeyboardController(aie::Input* input);
	virtual void update(Agent* agent, float deltaTime);
	~KeyboardController();
private:
	aie::Input* input;
};

