#pragma once

#include <Vector2.h>
#include <vector>
namespace aie
{
	class Renderer2D;
	class Texture;
}
class IBehavior;
class Decision;

class circle
{
public:
	Vector2 p;
	float r;
};

class Agent
{
public:
	Agent();
	Agent(aie::Texture* texture, Vector2 position);
	void update(float deltaTime);
	void draw(aie::Renderer2D* renderer);
	void AddForce(Vector2 force);
	void AddBehavior(IBehavior* behavior);
	void AddDecision(Decision* decision);
	void CalcCircle();
	circle GetCircle();
	Vector2 GetCirclePos();
	float GetCircleRadius();
	~Agent();
	Vector2 position;
	Vector2 acceleration;
	Vector2 velocity;
	float rotation;

private:
	aie::Texture* texture;
	IBehavior* m_behavior;
	Decision* m_decision;
	circle m_circle;

};

