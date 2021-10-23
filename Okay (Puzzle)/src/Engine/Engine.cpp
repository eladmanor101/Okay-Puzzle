#include "Engine.h"

Engine::Engine()
{

}

Engine::~Engine()
{

}

void Engine::init()
{
	window.create(sf::VideoMode(800, 800), "Okay?", sf::Style::Close | sf::Style::Titlebar);
	resource_manager.loadResources();

	pushState(std::make_unique<MenuState>(*this));
	states.back()->init();
}

void Engine::run()
{
	while (window.isOpen() && !states.empty())
	{
		handleEvents();
		render();

		tryPop();
	}
}

void Engine::render()
{
	if (!states.empty())
		states.back()->render(window);
}

void Engine::handleEvents()
{
	sf::Event e;
	while (window.pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		}

		states.back()->handleEvents(e);

	}

	float delta_time = clock.restart().asSeconds();

	if (!states.empty())
		states.back()->update(delta_time);
}

void Engine::exit()
{
	states.clear();
	window.close();
}

void Engine::initState()
{
	states.back()->init();
}

void Engine::pushState(std::unique_ptr<State>&& state)
{
	states.push_back(std::move(state));
}

void Engine::popState()
{
	should_pop = true;
}

sf::RenderWindow& Engine::getWindow()
{
	return window;
}

ResourceManager& Engine::getResourceManager()
{
	return resource_manager;
}

SettingsManager& Engine::getSettingsManager()
{
	return settings_manager;
}

Random& Engine::getNumberGenerator()
{
	return number_generator;
}

void Engine::tryPop()
{
	if (should_pop && !states.empty())
	{
		should_pop = false;
		states.pop_back();
	}
}

/*
std::unique_ptr<State>& Engine::GetCurrentState()
{
	return states.back();
}
*/