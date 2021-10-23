#pragma once

#include <iostream>

#include "../Engine/Engine.h"
#include "State.h"
#include "PlayingState.h"
#include "EditorState.h"

#include "../GUI/Button.h"

class MenuState : public State
{
public:
	MenuState(Engine& engine);
	~MenuState();

	void init();
	void update(float delta_time);
	void render(sf::RenderWindow& window);
	void handleEvents(sf::Event& e);

private:
	gui::Button play_button;
	gui::Button editor_button;
	gui::Button quit_button;
};