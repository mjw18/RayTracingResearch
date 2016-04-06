/*
* Triangle Subclass which implements M&T's intersection method
*/
#pragma once
#include "Triangle.h"
#include "Ray.h"

class MTTriangle : public Triangle
{
public:
	/*
	* The constructor takes a pointer to a triangle and
	* copies its vertices into a new subclassed triangle.
	* This is allows for the same triangle to be reused in each intersection test.
	*/
	MTTriangle(Triangle* triangle);
	~MTTriangle();

	/*
	* This is the Moller and Trumbore triangle intersection method
	*/
	virtual int intersect(Ray* ray) override;

	/*
	* Dummy method to account for overhead and method calls
	*/
	virtual int doNothing(Ray* ray) override;

	/*
	* Debug printing of intersection tet results
	*/
	virtual void printRes(){ std::printf("t: %f, u: %f, v: %f \n", t, u, v); }

	double u, v, t;
};

