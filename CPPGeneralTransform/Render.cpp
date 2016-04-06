#include "Render.h"

#include <iostream>
#include <random>
#include "LinearAlgebra.h"

Render::Render()
{
}


Render::~Render()
{
	for (size_t i = 0; i < triangleVector.size(); i++)
	{
		delete triangleVector[i];
	}

	for (size_t i = 0; i < rayVector.size(); i++)
	{
		delete rayVector[i];
	}

}

void Render::init(int numTriangles, int numRays)
{
	triangleVector.resize(numTriangles);
	rayVector.resize(numRays);
}

//Fill the vectors
void Render::generateTriangles()
{
	for (size_t i = 0; i < triangleVector.size(); i++)
	{
		triangleVector[i] = new Triangle();
	}
}

void Render::generateRays()
{
	for (size_t i = 0; i < rayVector.size(); i++)
	{
		rayVector[i] = new Ray();
	}
}

double Render::trace(std::vector<Triangle*>& triangleVector, std::vector<Ray*>& rayVector)
{
	m_count = 0;

	//Start CPU timing
	begin = clock();
	//Loop through vectors
	for (size_t i = 0; i < triangleVector.size(); i++)
	{
		//Loop through triangles
		for (size_t j = 0; j < rayVector.size(); j++)
		{
			if (triangleVector[i]->intersect(rayVector[j]) == 1)
			{
				m_count += 1;
			}
		}
	}
	//Get end CPU timing and calculate run time
	end = clock();
	double intersectTime = ((double)(end - begin)) / CLOCKS_PER_SEC;

	//Get time of overhead
	begin = clock();
	//Loop through vectors
	for (size_t i = 0; i < triangleVector.size(); i++)
	{		
		//Loop through triangles
		for (size_t j = 0; j < rayVector.size(); j++)
		{
			triangleVector[i]->doNothing(rayVector[j]);
		}
	}
	end = clock();
	double overheadTime = ((double)(end - begin)) / CLOCKS_PER_SEC;

	//Calculate actual time of intersect calculation
	return m_time = intersectTime - overheadTime;
}

void Render::intersectSimultaneous(std::vector<Triangle*>& genTriangleVector, std::vector<Triangle*>& barTriangleVector, std::vector<Ray*>& rayVector)
{
	for (size_t i = 0; i < genTriangleVector.size(); i++)
	{
		//Loop through triangles
		for (size_t j = 0; j < rayVector.size(); j++)
		{
			if (genTriangleVector[i]->intersect(rayVector[j]) != barTriangleVector[i]->intersect(rayVector[j]))
			{
				printf("\n***DIFFERING RESULTS***\n");
				printf("\n***GEN RESULTS***\n");
				genTriangleVector[i]->printRes();
				printf("\n***BAR RESULTS***\n");
				barTriangleVector[i]->printRes();
				printf("\n***SUSPECT TRIANGLE***\n");
				genTriangleVector[i]->printTriangle();
				printf("\n***SUSPECT RAY***\n");
				std::printf("\nX: %f, Y: %f\n", rayVector[j]->x, rayVector[j]->y);
			}
		}
	}
}

void Render::printResults(float time, int count)
{
	std::printf(" Computation Time: %f, Hits: %d\n", m_time, m_count);
}