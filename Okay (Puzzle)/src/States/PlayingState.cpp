#include "PlayingState.h"

PlayingState::PlayingState(Engine& engine) : State(engine)
{

}

PlayingState::~PlayingState()
{

}

const float PlayingState::AnimatedShape::ANIMATION_DURATION = 1.0f;

void PlayingState::init()
{
	int WIDTH = engine->getWindow().getSize().x, HEIGHT = engine->getWindow().getSize().y;

	sf::ConvexShape t1;
	t1.setPointCount(3);

	t1.setPoint(0, sf::Vector2f(WIDTH / 3, HEIGHT / 3));
	t1.setPoint(1, sf::Vector2f(WIDTH / 3 + 50, HEIGHT / 3));
	t1.setPoint(2, sf::Vector2f(WIDTH / 3, HEIGHT / 3 + 50));

	shapes.push_back(t1);
}

void PlayingState::update(float delta_time)
{
	if (projectile)
	{
		// Collisions
		for (std::vector<sf::ConvexShape>::iterator it = shapes.begin(); it != shapes.end();)
		{
			bool is_colliding = false;
			sf::Vector2f p1, p2;

			for (int i = 0; i < it->getPointCount(); i++)
			{
				p1 = it->getPoint(i);
				p2 = it->getPoint((i + 1) % it->getPointCount());

				if (projectile->isColliding(p1, p2))
				{
					is_colliding = true;
					break;
				}
			}

			if (is_colliding)
			{
				handleCollision(p1, p2);
				animated_shapes.push_back(AnimatedShape(*it));
				it = shapes.erase(it);
			}
			else
			{
				++it;
			}
		}

		// Projectile
		projectile->update(delta_time);

		/*
		if (projectile->getPosition().x - projectile->getRadius() / 2.0f <= 0
			|| projectile->getPosition().y - projectile->getRadius() / 2.0f <= 0
			|| projectile->getPosition().x + projectile->getRadius() / 2.0f >= engine->getWindow().getSize().x
			|| projectile->getPosition().y + projectile->getRadius() / 2.0f >= engine->getWindow().getSize().y)
		{
			projectile = nullptr;
		}
		*/

		// Shape Animation
		for (std::vector<AnimatedShape>::iterator it = animated_shapes.begin(); it != animated_shapes.end();)
		{
			float scale = 1 - powf(1 - it->elapsed_animation_time / it->ANIMATION_DURATION, 3);
			sf::Color fill_color = it->shape.getFillColor();
			sf::Color outline_color = it->shape.getOutlineColor();

			std::cout << scale << std::endl;
			it->shape.setScale(sf::Vector2f(1 + 0.5f * scale, 1 + 0.5f * scale));
			it->shape.setFillColor(sf::Color(fill_color.r, fill_color.g, fill_color.b, 255 * (1 - scale)));
			it->shape.setOutlineColor(sf::Color(outline_color.r, outline_color.g, outline_color.b, 255 * (1 - scale)));
			it->elapsed_animation_time += delta_time;
			
			if (it->elapsed_animation_time >= it->ANIMATION_DURATION)
			{
				it = animated_shapes.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}

void PlayingState::render(sf::RenderWindow& window)
{
	window.clear(sf::Color(232, 228, 236));

	for (sf::ConvexShape& shape : shapes)
	{
		window.draw(shape);
	}

	for (AnimatedShape& animated_shape : animated_shapes)
	{
		window.draw(animated_shape.shape);
	}

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

void PlayingState::handleCollision(sf::Vector2f p1, sf::Vector2f p2)
{
	sf::Vector2f velocity = projectile->getVelocity();
	sf::Vector2f surface_vector(p1.x - p2.x, p1.y - p2.y);
	sf::Vector2f surface_normal = normalize(sf::Vector2f(-surface_vector.y, surface_vector.x));

	if (dot(surface_normal, p1 - projectile->getPosition()) < 0)
	{
		surface_normal = -surface_normal;
	}

	projectile->setVelocity(velocity - 2 * dot(projectile->getVelocity(), surface_normal) * surface_normal);
}