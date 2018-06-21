#pragma once

#include <Vector2.h>
#include <vector>
namespace aie
{
	class Renderer2D;
	class Texture;
}
class IBehavior;
class Agent
{
public:
	Agent();
	Agent(aie::Texture* texture, Vector2 position);
	void update(float deltaTime);
	void draw(aie::Renderer2D* renderer);
	void AddForce(Vector2 force);
	void AddBehavior(IBehavior* behavior);
	~Agent();
	Vector2 position;
	Vector2 acceleration;
	Vector2 velocity;

private:
	aie::Texture* texture;
	std::vector<IBehavior*> m_behaviors;
};

