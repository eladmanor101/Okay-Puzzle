#pragma once

#include <iostream>
#include <functional>
#include "SFML/Graphics.hpp"

namespace gui
{
	namespace states
	{
		enum ButtonState
		{
			Idle,
			Hover,
			Pressed
		};
	}

	class Button
	{
	public:
		Button();
		Button(std::string string, sf::Font& font, sf::Vector2f position, sf::Vector2f size);
		~Button();

		void init(sf::RenderWindow& window);
		void draw(sf::RenderWindow& window);
		void update(sf::RenderWindow& window);
		void handleEvents(sf::RenderWindow& window, sf::Event& e);

		void setOnClick(const std::function<void()>& function);

		void setColorTextIdle(sf::Color color);
		void setColorTextHover(sf::Color color);
		void setColorTextPressed(sf::Color color);
		void setColorIdle(sf::Color color);
		void setColorHover(sf::Color color);
		void setColorPressed(sf::Color color);

		void setBorderColor(sf::Color color);
		void setBorderThickness(float thickness);

		void setPosition(sf::Vector2f position);
		void setSize(sf::Vector2f dimensions);

		void setTextSize(unsigned int size);
		void setText(std::string string);
		void setFont(sf::Font& font);

		sf::Vector2f getPosition();
		sf::Vector2f getDimensions();
		unsigned int getState();

	private:
		std::function<void()> on_click_function;

		sf::Color color_idle;
		sf::Color color_hover;
		sf::Color color_pressed;
		sf::Color text_color_idle;
		sf::Color text_color_hover;
		sf::Color text_color_pressed;

		sf::Color border_color;
		float border_thickness;

		sf::RectangleShape button;
		unsigned int button_state;

		sf::Text text;
	};
}