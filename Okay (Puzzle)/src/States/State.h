#pragma once

#include "SFML/Graphics.hpp"
#include <stack>

#include "../Managers/ResourceManager.h"

class Engine;

class State
{
public:
	State(Engine& state_data);
	virtual ~State();

	virtual void init() = 0;
	virtual void update(float delta_time) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
	virtual void handleEvents(sf::Event& e) = 0;

protected:
	Engine* engine;
};