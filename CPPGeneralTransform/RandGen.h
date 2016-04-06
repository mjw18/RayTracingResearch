/*
* 
* Static random generator returns random double between -1 and 1 
* on call to getRand() function
*
*/
#pragma once
#include <random>
#include <ctime>

class RandGen
{
public:
	RandGen() {};

	~RandGen() {};

	static double getRand()
	{
		static std::mt19937 randomEngine(time(nullptr));
		static std::uniform_real_distribution<double>randNum(-1.0f, 1.0f);
		return randNum(randomEngine);
	};
	
};

