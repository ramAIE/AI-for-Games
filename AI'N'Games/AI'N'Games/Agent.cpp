#include "Agent.h"
#include <Renderer2D.h>
#include <Texture.h>
#include "IBehavior.h"
#include "Decision.h"
Agent::Agent()
{
	texture = nullptr;
	position = Vector2(0, 0);
	acceleration = Vector2(0, 0);
	velocity = Vector2(0, 0);
	m_behavior = nullptr;
	m_decision = nullptr;
	m_circle.p = Vector2(0, 0);
	m_circle.r = 0.0f;
}

Agent::Agent(aie::Texture* texture, Vector2 position)
{
	this->texture = texture;
	this->position = position;
	acceleration = Vector2(0, 0);
	velocity = Vector2(0, 0);
	m_behavior = nullptr;
	m_decision = nullptr;
	m_circle.p = Vector2(0, 0);
	m_circle.r = 0.0f;
}

void Agent::update(float deltaTime)
{
	CalcCircle();
	AddForce(velocity * -0.2f);
	velocity = velocity + acceleration * deltaTime;
	position = position + velocity * deltaTime;
	acceleration = Vector2(0, 0);

	if(m_behavior != nullptr)
		m_behavior->update(this, deltaTime);

	if (m_decision != nullptr)
	{
		m_decision->update(this, deltaTime);
	}
}

void Agent::draw(aie::Renderer2D * renderer)
{
	renderer->drawCircle(m_circle.p.m_x, m_circle.p.m_y, m_circle.r);
	renderer->drawSprite(texture, position.m_x, position.m_y, 0, 0, rotation);
	renderer->drawLine(position.m_x, position.m_y, velocity.m_x, velocity.m_y);
}

void Agent::AddForce(Vector2 force)
{
	acceleration = acceleration + force;
}

void Agent::AddBehavior(IBehavior * behavior)
{
	m_behavior = behavior;
}

void Agent::AddDecision(Decision * decision)
{
	m_decision = decision;
}

void Agent::CalcCircle()
{
	int w = texture->getWidth();
	int h = texture->getHeight();

	Vector2 v[4] = { Vector2(-(w / 2), -(h / 2)),
						Vector2(-(w / 2), (h / 2)),
						Vector2((w / 2), (h / 2)),
						Vector2((w / 2), -(h / 2)) };

	Vector2 min = Vector2(FLT_MAX, FLT_MAX);
	Vector2 max = Vector2(FLT_MIN, FLT_MIN);

	for (int i = 0; i < 4; ++i)
	{
		v[i] = position + v[i];
		if (v[i].m_x < min.m_x)
			min.m_x = v[i].m_x;
		if (v[i].m_y < min.m_y)
			min.m_y = v[i].m_y;

		if (v[i].m_x > min.m_x)
			max.m_x = v[i].m_x;
		if (v[i].m_y > min.m_y)
			max.m_y = v[i].m_y;
	}
	m_circle.p = (min + max) * 0.5f;
	Vector2 dist = max - m_circle.p;
	m_circle.r = dist.magnitude();
}

circle Agent::GetCircle()
{
	return m_circle;
}

Vector2 Agent::GetCirclePos()
{
	return m_circle.p;
}

float Agent::GetCircleRadius()
{
	return m_circle.r;
}


Agent::~Agent()
{
	if (texture != nullptr)
	{
		delete texture;
		texture = nullptr;
	}

	if (m_behavior != nullptr)
	{
		delete m_behavior;
		m_behavior = nullptr;
	}

	if (m_decision != nullptr)
	{
		delete m_decision;
		m_decision = nullptr;
	}
}
