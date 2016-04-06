/*
* The intersectSimultaneous function runs the intersection of each triangle and compares the results
* in order to check for intersections that do not agree between the two methods. This is for debugging
* and can be turned on with the INTERSECT_MISS option in the main method
*/
#pragma once
#include <iostream>
#include <ctime>
#include "Render.h"
#include "Triangle.h"
#include "GenTransTriangle.h"
#include "MTTriangle.h"

int main()
{
	//Define number of rays and triangles to be tested
	const int numTriangles = 0;
	const int numRays = 100;

	Render renderer;

	renderer.init(numTriangles, numRays);

	std::vector<Triangle*> GTTriangleVector;
	std::vector<Triangle*> MTTriangleVector;

	renderer.generateRays();
	renderer.generateTriangles();

	//Add specific triangles to renderer's container
	double one[3] = { 1, 2.2, 3 };
	double two[3] = { 5.3, 5, 6 };
	double three[3] = { -8, 7, 9.6 };
	renderer.triangleVector.push_back(new Triangle(one, two, three));

	//Add specific rays to renderer's container
	renderer.rayVector.push_back(new Ray(-9.792719, -19.453305));

	//Fill subclass triangle containers
	for (size_t i = 0; i < renderer.triangleVector.size(); i++)
	{
		GTTriangleVector.push_back(new GenTransTriangle(renderer.triangleVector[i]));
		MTTriangleVector.push_back(new MTTriangle(renderer.triangleVector[i]));
	}

	//Run intersetion calculations for our new method
	std::cout << "GeneralTransform Time:" << std::endl;
	renderer.trace(GTTriangleVector, renderer.rayVector);
	renderer.printResults(renderer.m_time, renderer.m_count);

	//Run intersection calculation for Moller and Trumbore's Barycentric Coordinate calculation
	std::cout << "Barycentric Time:" << std::endl;
	renderer.trace(MTTriangleVector, renderer.rayVector);
	renderer.printResults(renderer.m_time, renderer.m_count);

	// Prints out data for triangle ray intersectins that don't between each intersection
	// Does not run by default, used for debugging
#ifdef INTERSECT_MISS

	renderer.intersectSimultaneous(GTTriangleVector, MTTriangleVector, renderer.rayVector);

#endif

	//Keeps results in terminal
	int a;
	std::cin >> a;

	return 0;
}
