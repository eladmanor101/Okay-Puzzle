#include "Projectile.h"

Projectile::Projectile(sf::Vector2f position, sf::Vector2f velocity)
	: position(position), velocity(velocity)
{
	projectile_shape.setRadius(RADIUS);
	projectile_shape.setOrigin(projectile_shape.getLocalBounds().width / 2.0f, projectile_shape.getLocalBounds().height / 2.0f);
	projectile_shape.setPosition(position);
	projectile_shape.setFillColor(sf::Color::Black);
	projectile_shape.setFillColor(sf::Color(64, 68, 68));
}

Projectile::~Projectile()
{

}

const float Projectile::TRAIL_SPAWN_DELAY = 0.025f;

void Projectile::update(float delta_time)
{
	position.x += velocity.x * delta_time * SPEED;
	position.y += velocity.y * delta_time * SPEED;

	projectile_shape.setPosition(position);

	if (velocity.x != 0 && velocity.y != 0)
	{
		trail_time += delta_time;
		if (trail_time >= TRAIL_SPAWN_DELAY)
		{
			trail_time = 0.0f;
			trail.push_back(Trail(position));
		}

		for (std::vector<Trail>::iterator it = trail.begin(); it != trail.end();)
		{
			it->transparency -= 300.0f * delta_time;

			sf::Color trail_color = it->trail_shape.getFillColor();
			it->trail_shape.setFillColor(sf::Color(trail_color.r, trail_color.g, trail_color.b, it->transparency));
			
			if (it->trail_shape.getFillColor().a <= 0)
			{
				it = trail.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}

void Projectile::draw(sf::RenderWindow& window)
{
	for (Trail& trail_point : trail)
	{
		window.draw(trail_point.trail_shape);
	}

	window.draw(projectile_shape);
}

bool Projectile::isColliding(sf::Vector2f start, sf::Vector2f end)
{
	sf::Vector2f border_vector(end.x - start.x, end.y - start.y);
	sf::Vector2f circle_vector(position.x - start.x, position.y - start.y);

	float dot_product = math::dot(circle_vector, math::normalize(border_vector));
	sf::Vector2f point_on_line;
	if (dot_product <= 0)
	{
		point_on_line = start;
	}
	else if (dot_product >= math::length(border_vector))
	{
		point_on_line = end;
	}
	else
	{
		sf::Vector2f point_length = math::normalize(border_vector) * dot_product;
		point_on_line = sf::Vector2f(point_length.x + start.x, point_length.y + start.y);
	}

	float x = position.x - point_on_line.x;
	float y = position.y - point_on_line.y;
	return x * x + y * y <= RADIUS * RADIUS;
}