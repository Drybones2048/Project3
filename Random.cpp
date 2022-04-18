#include "Random.h"
#include <ctime>

std::mt19937 Random::random(time(0)); //redeclare because the variable is static with a random seed being generated 

int Random::Int(int min, int max) { //generates a random integer
	
	std::uniform_int_distribution<int> dist(min, max);

	return dist(random); //returns the random value 
}
float Random::Float(float min, float max) { //generates a random float

	std::uniform_real_distribution<float> dist(min, max);

	return dist(random); //returns the random value
}