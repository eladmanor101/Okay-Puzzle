#include "MenuState.h"

MenuState::MenuState(Engine& engine) : State(engine)
{

}

MenuState::~MenuState()
{

}

void MenuState::init()
{
	play_button.setSize(sf::Vector2f(300.0f, 150.0f));
	play_button.setFont(engine->getResourceManager().getFont("PressStart2P"));
	play_button.setText("PLAY");
	play_button.setTextSize(50);
	play_button.setPosition(sf::Vector2f(engine->getWindow().getSize().x / 2.0f, engine->getWindow().getSize().y / 4.0f * 1.0f));
	play_button.setColorIdle(sf::Color::Black);
	play_button.setColorTextIdle(sf::Color::White);
	play_button.setColorHover(sf::Color::Black);
	play_button.setColorTextHover(sf::Color::Red);
	play_button.setColorPressed(sf::Color::Black);
	play_button.setColorTextPressed(sf::Color(0, 0, 130, 255));
	play_button.init(engine->getWindow());

	play_button.setOnClick([this]()
		{
			engine->pushState(std::make_unique<PlayingState>(*engine));
			engine->initState();
		});

	editor_button.setSize(sf::Vector2f(300.0f, 150.0f));
	editor_button.setFont(engine->getResourceManager().getFont("PressStart2P"));
	editor_button.setText("SETTINGS");
	editor_button.setTextSize(50);
	editor_button.setPosition(sf::Vector2f(engine->getWindow().getSize().x / 2.0f, engine->getWindow().getSize().y / 4.0f * 2.0f));
	editor_button.setColorIdle(sf::Color::Black);
	editor_button.setColorTextIdle(sf::Color::White);
	editor_button.setColorHover(sf::Color::Black);
	editor_button.setColorTextHover(sf::Color::Red);
	editor_button.setColorPressed(sf::Color::Black);
	editor_button.setColorTextPressed(sf::Color(0, 0, 130, 255));
	editor_button.init(engine->getWindow());

	editor_button.setOnClick([this]()
		{
			engine->pushState(std::make_unique<EditorState>(*engine));
			engine->initState();
		});

	quit_button.setSize(sf::Vector2f(300.0f, 150.0f));
	quit_button.setFont(engine->getResourceManager().getFont("PressStart2P"));
	quit_button.setText("QUIT");
	quit_button.setTextSize(50);
	quit_button.setPosition(sf::Vector2f(engine->getWindow().getSize().x / 2.0f, engine->getWindow().getSize().y / 4.0f * 3.0f));
	quit_button.setColorIdle(sf::Color::Black);
	quit_button.setColorTextIdle(sf::Color::White);
	quit_button.setColorHover(sf::Color::Black);
	quit_button.setColorTextHover(sf::Color::Red);
	quit_button.setColorPressed(sf::Color::Black);
	quit_button.setColorTextPressed(sf::Color(0, 0, 130, 255));
	quit_button.init(engine->getWindow());

	quit_button.setOnClick([this]()
		{
			engine->exit();
		});
}

void MenuState::update(float delta_time)
{
	play_button.update(engine->getWindow());
	editor_button.update(engine->getWindow());
	quit_button.update(engine->getWindow());
}

void MenuState::render(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);

	play_button.draw(engine->getWindow());
	editor_button.draw(engine->getWindow());
	quit_button.draw(engine->getWindow());

	window.display();
}

void MenuState::handleEvents(sf::Event& e)
{
	play_button.handleEvents(engine->getWindow(), e);
	editor_button.handleEvents(engine->getWindow(), e);
	quit_button.handleEvents(engine->getWindow(), e);
}