#include "Triangle.h"
#include "RandGen.h"
#include "LinearAlgebra.h"

Triangle::Triangle()
{
	// Triangle generator
	m_v1[0] = (PIC_WIDTH * RandGen::getRand()) - (PIC_WIDTH * RandGen::getRand());
	m_v1[1] = (PIC_HEIGHT * RandGen::getRand()) - (PIC_HEIGHT *  RandGen::getRand());
	m_v1[2] = (z * RandGen::getRand()) - (10 * RandGen::getRand());

	m_v2[0] = (PIC_WIDTH * RandGen::getRand()) - (PIC_WIDTH *  RandGen::getRand());
	m_v2[1] = (PIC_HEIGHT * RandGen::getRand()) - (PIC_HEIGHT * RandGen::getRand());
	m_v2[2] = (z * RandGen::getRand()) - (10 * RandGen::getRand());

	m_v3[0] = (PIC_WIDTH * RandGen::getRand()) - (PIC_WIDTH * RandGen::getRand());
	m_v3[1] = (PIC_HEIGHT * RandGen::getRand()) - (PIC_HEIGHT * RandGen::getRand());
	m_v3[2] = (z * RandGen::getRand()) - (10 * RandGen::getRand());
}

//Specific Triangle constructor
Triangle::Triangle(double* V1, double* V2, double* V3)
{
	m_v1[0] = V1[0];
	m_v1[1] = V1[1];
	m_v1[2] = V1[2];

	m_v2[0] = V2[0];
	m_v2[1] = V2[1];
	m_v2[2] = V2[2];

	m_v3[0] = V3[0];
	m_v3[1] = V3[1];
	m_v3[2] = V3[2];

}

Triangle::~Triangle()
{
}

//setters
void Triangle::setEdge(int index)
{
	if (index == 1)
	{
		SUB3(m_e1, m_v2, m_v1)
	}
	else if (index == 2)
	{
		SUB3(m_e2, m_v3, m_v1)
	}
	else
	{
		std::printf("failure to set edge\n");
		m_e1[0] = 0;
		m_e1[1] = 0;
		m_e1[2] = 0;

		m_e2[0] = 0;
		m_e2[1] = 0;
		m_e2[2] = 0;
	}
}

void Triangle::setNorm()
{
	if (m_e1 != NULL && m_e2 != NULL)
	{
		CROSS(m_n, m_e1, m_e2)
	}
	else
	{
		std::printf("failure to set norm\n");

		m_n[0] = 0;
		m_n[1] = 0;
		m_n[2] = 0;
	}
}

double* Triangle::getEdge(int index)
{

	return (index == 1) ? m_e1 : m_e2;

}

double* Triangle::getNorm()
{
	return m_n;
}

double* Triangle::getVertex(int index)
{
	switch (index)
	{
	case 1:
		return m_v1;
		break;

	case 2:
		return m_v2;
		break;

	case 3:
		return m_v3;
		break;

	default:
		//throw an error here
		return NULL;
		break;
	}
}
