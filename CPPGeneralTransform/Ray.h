/*
* 
* Ray object that holds x and y components of interecting ray.
* Default constructor generates ray with random components
* Overloaded constructor generates ray with specific components
*
*/
#pragma once
#include <iostream>
#include "RandGen.h"
#include "Config.h"

class Ray
{
public:
	//Default constructor generates a random ray
	Ray()
	{
		x = (PIC_WIDTH * RandGen::getRand());
		y = (PIC_HEIGHT * RandGen::getRand());
	}
	//Generate specific ray
	Ray(double X, double Y)
	{
		x = X;
		y = Y;
	}

	//Debug printing
	void printRay()
	{
		std::cout << "Ray: " << std::endl;
		std::printf("%f, %f \n", x, y);
	}

	double x, y;

};

