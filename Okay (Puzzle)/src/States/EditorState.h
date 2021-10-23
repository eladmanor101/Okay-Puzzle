#pragma once

#include "../Engine/Engine.h"
#include "State.h"

class EditorState : public State
{
public:
	EditorState(Engine& engine);
	~EditorState();

	void init();
	void update(float delta_time);
	void render(sf::RenderWindow& window);
	void handleEvents(sf::Event& e);

private:
	
};