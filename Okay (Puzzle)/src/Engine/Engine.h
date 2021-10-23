#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>

#include "../Managers/ResourceManager.h"
#include "../Managers/SettingsManager.h"

#include "../States/State.h"
#include "../States/MenuState.h"

#include "../Utilities/Random.h"

class Engine
{
public:
	Engine();
	~Engine();

	void init();
	void run();

	void exit();

	void initState();
	void pushState(std::unique_ptr<State>&& state);
	void popState();

	sf::RenderWindow& getWindow();
	ResourceManager& getResourceManager();
	SettingsManager& getSettingsManager();
	Random& getNumberGenerator();

private:
	void render();
	void handleEvents();

	void tryPop();
	//State& GetCurrentState();

	sf::RenderWindow window;
	ResourceManager resource_manager;
	SettingsManager settings_manager;
	Random number_generator;
	std::vector<std::unique_ptr<State>> states;
	sf::Clock clock;

	bool should_pop = false;
};