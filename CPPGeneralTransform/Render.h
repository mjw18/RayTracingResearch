/*
* 
* The Render object is responsible for initiailizing container of generic triangles
* which will be copied to make identical sets of triangles for the new method and for M&T's
*
* This object is also responsible for running the intersection tests and for timing and counting the results
*
* The intersectSimultaneous function runs the intersection of each triangle and compares the results 
* in order to check for intersections that do not agree between the two methods. This is for debugging
* and can be turned on with the INTERSECT_MISS option in the main method
*
*/

#pragma once
#include <vector>
#include <ctime>

#include "Triangle.h"
#include "Ray.h"

class Render
{
public:
	Render();
	~Render();

	//Resize member vectors
	void init(int numTriangles, int numRays);

	//Fill the member vectors with randomly generated objects
	void generateTriangles();
	void generateRays();

	//Return time for intersection and increment hit count
	double trace(std::vector<Triangle*>& triangleVector, std::vector<Ray*>& rayVector);

	//Used for debugging
	//prints out results, (triangle and ray) when one hits and one doesn't
	void intersectSimultaneous(std::vector<Triangle*>& genTriangleVector, std::vector<Triangle*>& barTriangleVector, std::vector<Ray*>& rayVector);

	//Result Printing
	void printResults(float time, int count);

	//Containers for template triangle and rays
	std::vector<Triangle*> triangleVector;
	std::vector<Ray*> rayVector;

	//Data
	clock_t begin, end;;
	double m_time = 0;

	int m_count = 0;

};
