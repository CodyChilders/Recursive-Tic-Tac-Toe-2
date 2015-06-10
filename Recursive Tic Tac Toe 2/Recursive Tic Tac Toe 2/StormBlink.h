/*************************************************
* This entire class was taken from the SFML      *
* example code and slightly modified by me       *
*************************************************/

#ifndef STORMBLINK_HPP
#define STORMBLINK_HPP

#include "GlobalVariables.h"
#define STORM "../Shaders/storm.vert"
#define BLINK "../Shaders/blink.frag"
#define NumberOfStars 100

#include "Effect.h"

class StormBlink : public Effect
{
public:

	StormBlink() :
		Effect("storm + blink")
	{
	}

	bool onLoad()
	{
		// Create the points
		m_points.setPrimitiveType(sf::Points);
		for (int i = 0; i < NumberOfStars; ++i)
		{
			//float x = static_cast<float>(std::rand() % 800);
			//float y = static_cast<float>(std::rand() % 600);
			//sf::Uint8 r = std::rand() % 255;
			//sf::Uint8 g = std::rand() % 255;
			//sf::Uint8 b = std::rand() % 255;
			float x = static_cast<float>(std::rand() % w);
			float y = static_cast<float>(std::rand() % h);
			int r = 255, g = 255, b = 255;
			m_points.append(sf::Vertex(sf::Vector2f(x, y), sf::Color(r, g, b)));
		}

		// Load the shader
		if (!m_shader.loadFromFile(STORM, BLINK))
			return false;

		return true;
	}

	void onUpdate(float time, float x, float y)
	{
		float radius = 200 + std::cos(time) * 150;
		m_shader.setParameter("storm_position", x * 800, y * 600);
		m_shader.setParameter("storm_inner_radius", radius / 3);
		m_shader.setParameter("storm_total_radius", radius);
		m_shader.setParameter("blink_alpha", 0.5f + std::cos(time * 3) * 0.25f);
	}

	void onDraw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.shader = &m_shader;
		target.draw(m_points, states);
	}

private:

	sf::VertexArray m_points;
	sf::Shader m_shader;
};

#endif
