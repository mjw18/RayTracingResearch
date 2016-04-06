#include "GenTransTriangle.h"
#include "LinearAlgebra.h"

GenTransTriangle::GenTransTriangle(Triangle* triangle)
{
	m_v1[0] = triangle->getVertex(1)[0];
	m_v1[1] = triangle->getVertex(1)[1];
	m_v1[2] = triangle->getVertex(1)[2];

	m_v2[0] = triangle->getVertex(2)[0];
	m_v2[1] = triangle->getVertex(2)[1];
	m_v2[2] = triangle->getVertex(2)[2];

	m_v3[0] = triangle->getVertex(3)[0];
	m_v3[1] = triangle->getVertex(3)[1];
	m_v3[2] = triangle->getVertex(3)[2];

	setEdge(1);
	setEdge(2);
	setNorm();

	generalTransform();
	printInverse();
}


GenTransTriangle::~GenTransTriangle()
{
}

int GenTransTriangle::intersect(Ray* ray)
{
	/* Create source and pixel vectors for GT */
	double S[4] = { 0, 0, z, 1 };
	double P[4] = { xL + ray->x * w, yT - h * ray->y, z - 1, 1 };
	double D[4];
	SUB(D, P, S)

	double tMin = 10000;
	
	double ta, wr[4], tD[4], transS, transD;

	//Do matrix set up stuff here for when b=c=0 formula

	//Get z components of transformed vectors for calculation of t value
	transS = m_inverse[8] * S[0] + m_inverse[9] * S[1] + m_inverse[10] * S[2] + m_inverse[11] * S[3];
	transD = m_inverse[8] * D[0] + m_inverse[9] * D[1] + m_inverse[10] * D[2] + m_inverse[11] * D[3];

	ta = -transS / transD;
	/* Reject negative t values and parallel rays */
	if (ta < EPSILON || ta > tMin)
		return 0;

	/* Get Canonically Transformed Ray */
	SCALEMULT(tD, ta, D)
		ADD(wr, S, tD)

		//test "x" barycentric component
		if ((xg = m_inverse[0] * wr[0] + m_inverse[1] * wr[1] + m_inverse[2] * wr[2] + m_inverse[3] * wr[3]) < 0.0)
			return 0;

	//test "y" barycentric component
	if ((yg =m_inverse[4] * wr[0] +m_inverse[5] * wr[1] + m_inverse[6] * wr[2] + m_inverse[7] * wr[3]) < 0.0)
		return 0;

	//final intersect test
	if (yg + xg < 1.0){
		tg = ta;
		return 1;
	}
	return 0;
}

int GenTransTriangle::doNothing(Ray* ray)
{
	return 0;
}

//This is the calculator for the general transformation intersection
int GenTransTriangle::generalTransform()
{
	double x1, x2;

	//Used in index [3][4] of each matrix
	double num = DOT(m_v1, m_n);

	if (m_n[0] != 0){
		x1 = m_v2[1] * m_v1[2] - m_v2[2] * m_v1[1];
		x2 = m_v3[1] * m_v1[2] - m_v3[2] * m_v1[1];

		//Do matrix set up stuff here for when b=c=0 formula
		m_inverse[0] = 0;
		m_inverse[1] = m_e1[2] / m_n[0];
		m_inverse[2] = -m_e1[1] / m_n[0];
		m_inverse[3] = x1 / m_n[0];

		m_inverse[4] = 0;
		m_inverse[5] = -m_e2[2] / m_n[0];
		m_inverse[6] = m_e2[1] / m_n[0];
		m_inverse[7] = -x2 / m_n[0];

		m_inverse[8] = 1;
		m_inverse[9] = m_n[1] / m_n[0];
		m_inverse[10] = m_n[2] / m_n[0];
		m_inverse[11] = -num / m_n[0];

		m_inverse[12] = 0;
		m_inverse[13] = 0;
		m_inverse[14] = 0;
		m_inverse[15] = 1;

		return 0;
	}

	else if (m_n[2] != 0){
		x1 = m_v2[0] * m_v1[1] - m_v2[1] * m_v1[0];
		x2 = m_v3[0] * m_v1[1] - m_v3[1] * m_v1[0];
		//c case
		m_inverse[0] = m_e1[1] / m_n[2];
		m_inverse[1] = -m_e1[0] / m_n[2];
		m_inverse[2] = 0;
		m_inverse[3] = x1 / m_n[2];

		m_inverse[4] = -m_e2[1] / m_n[2];
		m_inverse[5] = m_e2[0] / m_n[2];
		m_inverse[6] = 0;
		m_inverse[7] = -x2 / m_n[2];

		m_inverse[8] = m_n[0] / m_n[2];
		m_inverse[9] = m_n[1] / m_n[2];
		m_inverse[10] = 1;
		m_inverse[11] = -num / m_n[2];

		m_inverse[12] = 0;
		m_inverse[13] = 0;
		m_inverse[14] = 0;
		m_inverse[15] = 1;

		return 0;

	}
	else if (m_n[1] != 0){
		x1 = m_v2[2] * m_v1[0] - m_v2[0] * m_v1[2];
		x2 = m_v3[2] * m_v1[0] - m_v3[0] * m_v1[2];

		//b case
		m_inverse[0] = -m_e1[2] / m_n[1];
		m_inverse[1] = 0;
		m_inverse[2] = m_e1[0] / m_n[1];
		m_inverse[3] = x1 / m_n[1];

		m_inverse[4] = m_e2[2] / m_n[1];
		m_inverse[5] = 0;
		m_inverse[6] = -m_e2[0] / m_n[1];
		m_inverse[7] = -x2 / m_n[1];

		m_inverse[8] = m_n[0] / m_n[1];
		m_inverse[9] = 1;
		m_inverse[10] = m_n[2] / m_n[1];
		m_inverse[11] = -num / m_n[1];

		m_inverse[12] = 0;
		m_inverse[13] = 0;
		m_inverse[14] = 0;
		m_inverse[15] = 1;

		return 0;
	}
	else
	{
		std::printf("Failed to get inverse\n");
		return 1;
	}
}