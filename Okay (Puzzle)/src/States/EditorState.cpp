#include "EditorState.h"

EditorState::EditorState(Engine& engine) : State(engine)
{

}

EditorState::~EditorState()
{

}

void EditorState::init()
{

}

void EditorState::update(float delta_time)
{

}

void EditorState::render(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);



	window.display();
}

void EditorState::handleEvents(sf::Event& e)
{
	if (e.type == sf::Event::KeyPressed)
	{
		engine->popState();
	}
}