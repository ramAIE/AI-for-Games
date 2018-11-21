//** should apply linear motion later
#pragma once
#include <Matrix3.h>
#include <vector>

namespace aie
{
	class Renderer2D;
	class Texture;
}

class Behaviour;

class Agent
{
public:
	Agent();
	Agent(aie::Texture* texture, Vector3 pos);

	void update(float deltaTime);
	void draw(aie::Renderer2D* renderer);

	void UpdateGlobalTransform();
	Matrix3 GetLocalTransform();
	Matrix3 GetGlobalTransform();

	// change the position and rotation of the agent
	void SetPosition(Vector3 position);
	void SetRotate(float radians);

	// Move and Turn the agent
	void translate(Vector3 position);
	void rotate(float radians);

	void addBehaviour(Behaviour * behaviour);

	void AddForce(Vector3 force);

	bool RotateHeadingtoFacePosition(Vector3 target);

	~Agent();

private:
	aie::Texture* m_texture;
	// world transform
	Matrix3	m_global;
	// agent's local transform
	Matrix3 m_local;
	// AI behaviours
	std::vector<Behaviour*> m_behaviours;

	Vector3 m_acceleration;
	
	Vector3 m_velocity;

	float m_maxVelocity;
};

