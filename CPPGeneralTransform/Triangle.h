/*
*
* Triangle object abstract class.
* Defualt Constructor generates a tirangle with random vertiecs
* Overloaded constructor generates a triangle with specific vertices
* Intersect and do nothing methods are overridden by subclasses,
* these return -1 to indicate misuse of abstract triangle object*
*
* Triangle vertices and vectors are stored as double arrays 
*
* Accessor and mutators are passed number for specifc edge
* ie) getEdge(1) returns EdgeVector 1
*
*/
#pragma once
#include <iostream>
#include "Ray.h"
#include "Config.h"

class Triangle
{
public:
	//Default constructor generates random triangle 
	Triangle();
	//This constructor allows for specific trianle contruction by passing vertex arrays
	Triangle(double* V1, double* V2, double*  V3);
	~Triangle();

	//Virtual intersect and dummy methods
	//Return -1 for class misuse
	virtual int intersect(Ray* ray) { return -1; };

	virtual int doNothing(Ray* ray) { return -1; };
	
	//printing of results
	virtual void printRes() {};

	// Mutator function
	void setEdge(int index);
	void setNorm();

	// Accessor funtions 

	//Passing in 1 returns edge 1 etc
	double* getEdge(int index);
	double* getNorm();
	//1 retrns first vertex etc
	double* getVertex(int index);

	//Debug printing
	void printTriangle()
	{
		std::cout << "Triangle: \n";
		std::printf("%f, %f, %f\n", m_v1[0], m_v1[1], m_v1[2]);
		std::printf("%f, %f, %f\n", m_v2[0], m_v2[1], m_v2[2]);
		std::printf("%f, %f, %f\n", m_v3[0], m_v3[1], m_v3[2]);
	}

	virtual void printInverse(){};

protected:
	//vertices
	double m_v1[3];
	double m_v2[3];
	double m_v3[3];

	//preprocessed information
	double m_e1[3];
	double m_e2[3];
	double m_n[3];

	/* Set world coordinates */
	const double xL = -PIC_WIDTH / 2;
	const double yT = PIC_HEIGHT / 2;

	/* Set pixel dimension */
	const double w = PIC_WIDTH / (float)ROW;
	const double h = PIC_HEIGHT / (float)COL;
};

