#pragma once

#include <vector>

#include "SFML/Graphics.hpp"

#include "../Utilities/Math.h"

class Projectile
{
public:
	Projectile(sf::Vector2f position, sf::Vector2f velocity = sf::Vector2f(0, 0));
	~Projectile();

	void update(float delta_time);
	void draw(sf::RenderWindow& window);

	bool isColliding(sf::Vector2f start, sf::Vector2f end);

	void setVelocity(sf::Vector2f velocity) { this->velocity = velocity; }
	void setColor(sf::Color color) { this->projectile_shape.setFillColor(color); }

	sf::Vector2f getPosition() { return position; }
	sf::Vector2f getVelocity() { return velocity; }
	int getRadius() { return RADIUS; }

private:
	static const int SPEED = 500;
	static const int RADIUS = 7;
	static const float TRAIL_SPAWN_DELAY;

	sf::Vector2f position;
	sf::Vector2f velocity;

	sf::CircleShape projectile_shape;

	struct Trail
	{
		sf::CircleShape trail_shape;
		float transparency;

		Trail(sf::Vector2f position)
		{
			trail_shape.setRadius(RADIUS / 3.0f);
			trail_shape.setOrigin(trail_shape.getLocalBounds().width / 2.0f, trail_shape.getLocalBounds().height / 2.0f);
			trail_shape.setPosition(position);
			trail_shape.setFillColor(sf::Color::Black);
			trail_shape.setFillColor(sf::Color(64, 68, 68));

			transparency = 255;
		}
	};

	std::vector<Trail> trail;
	float trail_time;
};