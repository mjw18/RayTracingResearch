/*
*
* This is the triangle subclass for the new intersection method
* which inherits from the abstract triangle class.
*
*
*/
#pragma once
#include "Triangle.h"
#include "Ray.h"

class GenTransTriangle : public Triangle
{
public:
	/*
	* The constructor takes a pointer to a triangle and 
	* copies its vertices into a new subclassed triangle.
	* This is allows for the same triangle to be reused in each intersection test.
	*/
	GenTransTriangle(Triangle* triangle);
	~GenTransTriangle();

	/*
	* This is the new triangle intersection method
	*/
	virtual int intersect(Ray* ray) override;

	/*
	* Dummy method to account for overhead and method calls
	*/
	virtual int doNothing(Ray* ray) override;

	/*
	* Calculate the inverse transform t be used in intersection test.
	* Typially, one would only store the essential components of the transform 
	* and use these for the intersection.
	*/
	int generalTransform();

	/*
	* This is debug printing
	*/
	virtual void printRes(){ std::printf("t: %f, xg: %f, yg: %f \n", tg, xg, yg); }	

	virtual void printInverse()
	{
		printf("\ninverse\n");
		printf("%f %f %f %f\n", m_inverse[0], m_inverse[1], m_inverse[2], m_inverse[3]);
		printf("%f %f %f %f\n", m_inverse[4], m_inverse[5], m_inverse[6], m_inverse[7]);
		printf("%f %f %f %f\n", m_inverse[8], m_inverse[9], m_inverse[10], m_inverse[11]);
	}

	//Data
	double xg, yg, tg;

	double m_inverse[16];
};

