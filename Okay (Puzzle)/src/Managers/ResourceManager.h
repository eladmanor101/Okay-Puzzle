#pragma once

#include "SFML/Graphics.hpp"
#include <unordered_map>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void loadResources();

	sf::Texture& getTexture(const std::string& name);
	sf::Font& getFont(const std::string& name);

private:
	sf::Texture default_texture;
	sf::Font default_font;

	std::unordered_map<std::string, sf::Texture> textures;
	std::unordered_map<std::string, sf::Font> fonts;
};