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
	std::unique_ptr<Projectile> projectile;
	std::vector<sf::ConvexShape> shapes;

	bool is_aiming = false;
};