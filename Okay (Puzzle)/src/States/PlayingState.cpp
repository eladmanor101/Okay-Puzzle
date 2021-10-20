#include "PlayingState.h"

PlayingState::PlayingState(Engine& engine) : State(engine)
{

}

PlayingState::~PlayingState()
{

}

void PlayingState::init()
{
	sf::ConvexShape test_shape;
	test_shape.setPointCount(5);

	test_shape.setPoint(0, sf::Vector2f(0, 0));
	test_shape.setPoint(1, sf::Vector2f(150, 10));
	test_shape.setPoint(2, sf::Vector2f(120, 90));
	test_shape.setPoint(3, sf::Vector2f(30, 100));
	test_shape.setPoint(4, sf::Vector2f(0, 50));

	shapes.push_back(test_shape);
}

void PlayingState::update(float delta_time)
{
	if (projectile)
	{
		projectile->update(delta_time);

		if (projectile->getPosition().x - projectile->getRadius() / 2.0f <= 0
			|| projectile->getPosition().y - projectile->getRadius() / 2.0f <= 0
			|| projectile->getPosition().x + projectile->getRadius() / 2.0f >= engine->getWindow().getSize().x
			|| projectile->getPosition().y + projectile->getRadius() / 2.0f >= engine->getWindow().getSize().y)
		{
			//projectile = nullptr;
		}
	}
}

void PlayingState::render(sf::RenderWindow& window)
{
	window.clear(sf::Color(232, 228, 236));

	if (projectile)
	{
		projectile->draw(window);
	}

	if (is_aiming)
	{
		for (int i = 1; i <= 10; i++)
		{
			sf::CircleShape point(projectile->getRadius() / 6.0f);
			point.setOrigin(point.getLocalBounds().width / 2.0f, point.getLocalBounds().height / 2.0f);
			point.setFillColor(sf::Color::Black);
			point.setPosition(((sf::Vector2f)sf::Mouse::getPosition(window) - projectile->getPosition()) / 10.0f * (float)i + projectile->getPosition());

			window.draw(point);
		}
	}

	window.display();
}

void PlayingState::handleEvents(sf::Event& e)
{
	switch (e.type)
	{
	case sf::Event::MouseButtonPressed:
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			projectile = std::make_unique<Projectile>(sf::Vector2f(e.mouseButton.x, e.mouseButton.y));
			is_aiming = true;
		}
		break;

	case sf::Event::MouseButtonReleased:
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			is_aiming = false;
			sf::Vector2f direction = sf::Vector2f(e.mouseButton.x, e.mouseButton.y) - projectile->getPosition();
			projectile->setVelocity(1 / (sqrtf(direction.x * direction.x + direction.y * direction.y)) * direction);
		}

		break;
	}
}