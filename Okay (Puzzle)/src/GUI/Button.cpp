#include "Button.h"

gui::Button::Button()
{
	button_state = gui::states::Idle;

	setColorIdle(sf::Color(120, 120, 120, 255));
	setColorTextIdle(sf::Color::Black);
	setColorHover(sf::Color(215, 215, 215, 255));
	setColorTextHover(sf::Color(120, 120, 120, 255));
	setColorPressed(sf::Color::Green);
	setColorTextPressed(sf::Color(0, 100, 10, 255));

	border_thickness = 0.0f;
	border_color = sf::Color::Black;
	button.setOutlineThickness(border_thickness);
	button.setOutlineColor(border_color);
}

gui::Button::Button(std::string string, sf::Font& font, sf::Vector2f position, sf::Vector2f size)
{

}

gui::Button::~Button()
{
	
}

void gui::Button::init(sf::RenderWindow& window)
{
	button.setOrigin(sf::Vector2f(button.getLocalBounds().width / 2.0f, button.getLocalBounds().height / 2.0f));
	text.setOrigin(sf::Vector2f(text.getLocalBounds().width / 2.0f + text.getLocalBounds().left, text.getLocalBounds().height / 2.0f + text.getLocalBounds().top));

	bool mouse_in_button = sf::Mouse::getPosition(window).x >= button.getPosition().x - button.getGlobalBounds().width / 2.0f
		&& sf::Mouse::getPosition(window).x <= button.getPosition().x + button.getGlobalBounds().width / 2.0f
		&& sf::Mouse::getPosition(window).y >= button.getPosition().y - button.getGlobalBounds().height / 2.0f
		&& sf::Mouse::getPosition(window).y <= button.getPosition().y + button.getGlobalBounds().height / 2.0f;

	if (mouse_in_button)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			button_state = states::Pressed;
		else
			button_state = states::Hover;
	}
	else
		button_state = states::Idle;

	switch (button_state)
	{
	case states::Idle:
		button.setFillColor(color_idle);
		text.setFillColor(text_color_idle);
		break;

	case states::Hover:
		button.setFillColor(color_hover);
		text.setFillColor(text_color_hover);
		break;

	case states::Pressed:
		button.setFillColor(color_pressed);
		text.setFillColor(text_color_pressed);
		break;

	}
}

void gui::Button::draw(sf::RenderWindow& window)
{
	window.draw(button);
	window.draw(text);
}

void gui::Button::update(sf::RenderWindow& window)
{
	bool mouse_in_button = sf::Mouse::getPosition(window).x >= button.getPosition().x - button.getGlobalBounds().width / 2.0f
		&& sf::Mouse::getPosition(window).x <= button.getPosition().x + button.getGlobalBounds().width / 2.0f
		&& sf::Mouse::getPosition(window).y >= button.getPosition().y - button.getGlobalBounds().height / 2.0f
		&& sf::Mouse::getPosition(window).y <= button.getPosition().y + button.getGlobalBounds().height / 2.0f;

	if (mouse_in_button)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			button_state = states::Pressed;
		else
			button_state = states::Hover;
	}
	else
	{
		button_state = states::Idle;
	}

	// Set button colors depending on its state
	switch (button_state)
	{
	case states::Idle:
		button.setFillColor(color_idle);
		text.setFillColor(text_color_idle);
		break;

	case states::Hover:
		button.setFillColor(color_hover);
		text.setFillColor(text_color_hover);
		break;

	case states::Pressed:
		button.setFillColor(color_pressed);
		text.setFillColor(text_color_pressed);
		break;

	}
}

void gui::Button::handleEvents(sf::RenderWindow& window, sf::Event& e)
{
	bool mouse_in_button = sf::Mouse::getPosition(window).x >= button.getPosition().x - button.getGlobalBounds().width / 2.0f
		&& sf::Mouse::getPosition(window).x <= button.getPosition().x + button.getGlobalBounds().width / 2.0f
		&& sf::Mouse::getPosition(window).y >= button.getPosition().y - button.getGlobalBounds().height / 2.0f
		&& sf::Mouse::getPosition(window).y <= button.getPosition().y + button.getGlobalBounds().height / 2.0f;

	if (e.type == sf::Event::MouseButtonPressed)
	{
		if (mouse_in_button)
		{
			// On clicked event
			if (on_click_function)
				on_click_function();
		}
	}
	else if (e.type == sf::Event::MouseButtonReleased)
	{
		if (mouse_in_button)
		{
			// On release event
		}
	}
}

void gui::Button::setOnClick(const std::function<void()>& function)
{
	on_click_function = function;
}

void gui::Button::setColorTextIdle(sf::Color color)
{
	text_color_idle = color;
}

void gui::Button::setColorTextHover(sf::Color color)
{
	text_color_hover = color;
}

void gui::Button::setColorTextPressed(sf::Color color)
{
	text_color_pressed = color;
}

void gui::Button::setColorIdle(sf::Color color)
{
	color_idle = color;
}

void gui::Button::setColorHover(sf::Color color)
{
	color_hover = color;
}

void gui::Button::setColorPressed(sf::Color color)
{
	color_pressed = color;
}

void gui::Button::setBorderColor(sf::Color color)
{
	border_color = color;
}

void gui::Button::setBorderThickness(float thickness)
{
	border_thickness = thickness;
}

void gui::Button::setPosition(sf::Vector2f position)
{
	button.setPosition(position);
	text.setPosition(sf::Vector2f(button.getPosition().x, button.getPosition().y));
}

void gui::Button::setSize(sf::Vector2f dimensions)
{
	button.setSize(dimensions);
	text.setPosition(sf::Vector2f(button.getPosition().x + button.getGlobalBounds().width / 2.0f, button.getPosition().y + button.getGlobalBounds().height / 2.0f));
}

void gui::Button::setTextSize(unsigned int size)
{
	text.setCharacterSize(size);
}

void gui::Button::setText(std::string string)
{
	text.setString(string);
}

void gui::Button::setFont(sf::Font& font)
{
	text.setFont(font);
}

sf::Vector2f gui::Button::getPosition()
{
	return button.getPosition();
}

sf::Vector2f gui::Button::getDimensions()
{
	return sf::Vector2f(button.getGlobalBounds().width, button.getGlobalBounds().height);
}

unsigned int gui::Button::getState()
{
	return button_state;
}