#include "Agent.h"
#include <Renderer2D.h>
#include <Texture.h>


Agent::Agent()
{
	m_texture = nullptr;
	m_pos = Vector2(0, 0);
}

Agent::Agent(aie::Texture * texture, Vector2 pos)
{
	m_texture = texture;
	m_pos = pos;
}

void Agent::update(float deltaTime)
{
}

void Agent::draw(aie::Renderer2D * renderer)
{
	renderer->drawSprite(m_texture, m_pos.m_x, m_pos.m_y);
}

Vector2 Agent::GetPosition()
{
	return m_pos;
}

void Agent::SetPosition(Vector2 pos)
{
	m_pos = pos;
}


Agent::~Agent()
{
	delete m_texture;
}
