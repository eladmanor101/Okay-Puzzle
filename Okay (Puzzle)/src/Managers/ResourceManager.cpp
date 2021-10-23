#include "ResourceManager.h"

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

void ResourceManager::loadResources()
{
	fonts["PressStart2P"].loadFromFile("../Okay (Puzzle)/res/Fonts/PressStart2P.ttf");
}

sf::Texture& ResourceManager::getTexture(const std::string& name)
{
	std::unordered_map<std::string, sf::Texture>::iterator texture_itr = textures.find(name);

	if (texture_itr != textures.end())
	{
		return texture_itr->second;
	}

	return default_texture;
}

sf::Font& ResourceManager::getFont(const std::string& name)
{
	std::unordered_map<std::string, sf::Font>::iterator font_itr = fonts.find(name);
	
	if (font_itr != fonts.end())
	{
		return font_itr->second;
	}

	return default_font;
}