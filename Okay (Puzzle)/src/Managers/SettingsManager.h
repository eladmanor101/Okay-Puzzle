#pragma once

#include "SFML/Graphics.hpp"

class SettingsManager
{
public:
	SettingsManager();
	~SettingsManager();

private:
	friend class SettingsState;

};