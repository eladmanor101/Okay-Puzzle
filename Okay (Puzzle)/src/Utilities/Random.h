#pragma once

#include <random>

class Random
{
public:
	Random();
	~Random();

	int rand(int min, int max);

private:
	std::random_device rdev;
	std::mt19937 mt{ rdev() };
};