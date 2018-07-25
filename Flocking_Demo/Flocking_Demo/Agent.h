#pragma once
#include <Vector2.h>
namespace aie
{
	class Renderer2D;
	class Texture;
}
class Agent
{
public:
	Agent();
	Agent(aie::Texture* texture, Vector2 pos);
	void update(float deltaTime);
	void draw(aie::Renderer2D* renderer);

	Vector2 GetPosition();
	void SetPosition(Vector2 pos);

	~Agent();

private:
	aie::Texture*	m_texture;
	Vector2			m_pos;

};

