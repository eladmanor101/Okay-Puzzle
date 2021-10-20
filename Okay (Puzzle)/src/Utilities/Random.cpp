#include "Random.h"

Random::Random()
{

}

Random::~Random()
{

}

int Random::rand(int min, int max)
{
	std::uniform_int_distribution<int> udist(min, max);

	return udist(mt);
}