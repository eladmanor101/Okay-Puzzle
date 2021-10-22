#pragma once

#include <iostream>
#include <vector>

#include "../Engine/Engine.h"
#include "State.h"

#include "../Objects/Projectile.h"

class PlayingState : public State
{
public:
	PlayingState(Engine& engine);
	~PlayingState();

	void init();
	void update(float delta_time);
	void render(sf::RenderWindow& window);
	void handleEvents(sf::Event& e);

private:
	void handleCollision(sf::Vector2f p1, sf::Vector2f p2);

	std::unique_ptr<Projectile> projectile;
	std::vector<sf::ConvexShape> shapes;

	struct AnimatedShape
	{
		static const float ANIMATION_DURATION;

		sf::ConvexShape shape;
		float elapsed_animation_time;

		AnimatedShape(sf::ConvexShape shape) : shape(shape)
		{
			this->shape.setOutlineThickness(0.5f);
			this->shape.setOutlineColor(sf::Color::Black);

			elapsed_animation_time = 0.0f;
		}
	};
	std::vector<AnimatedShape> animated_shapes;

	bool is_aiming = false;
};