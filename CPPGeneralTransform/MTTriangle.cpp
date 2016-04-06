/*
* MTIntersect.c
*
*  Created on: 1997
*      Author: Tomas Moller -- Chalmers University of Technology
*      	  & Ben Trumbore -- Cornell University
*      Title:  Fast, Minimum Storage Ray /Triangle Intersection
*      Source: http://www.cs.virginia.edu/~gfx/Courses/2003/ImageSynthesis/papers/Acceleration/Fast%20MinimumStorage%20RayTriangle%20Intersection.pdf
*/
#include "MTTriangle.h"
#include "LinearAlgebra.h"

MTTriangle::MTTriangle(Triangle* triangle)
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

}


MTTriangle::~MTTriangle()
{
}

int MTTriangle::intersect(Ray* ray)
{
		/* Create source and direction vectors and t u v pointers for MT */
		double S3[3] = { 0, 0, z };
		double P3[3] = { xL + ray->x * w, yT - h*ray->y, z - 1 };
		double D3[3];
		SUB3(D3, P3, S3)

		double tvec[3], pvec[3], qvec[3];
		double det, inv_det;

		/* find vectors for two edges sharing vert 0*/
		SUB3(m_e1, m_v2, m_v1);
		SUB3(m_e2, m_v3, m_v1);

		/*begin calculating determinant, also used to calculate U parameter*/

		CROSS(pvec, D3, m_e2);

		/*if determinant is near zero, ray lies in plane of triangle */

		det = DOT(m_e1, pvec);

	#ifdef TEST_CULL /*define TEST_CULL if culling is desired*/
		if (det < EPSILON)
			return 0;

		/* calculate distance from vert to ray origin*/
		SUB3(tvec, S3, m_v1)

			/*calculate U parameter and test bounds*/
			u = DOT(tvec, pvec);
		if (u < 0.0 || u > det)
			return 0;

		/*prepare to test V parameter*/
		CROSS(qvec, tvec, m_e1);

		/*calculate V parameter and test bounds*/
		v = DOT(D3, qvec);
		if (v < 0.0 || u + v > det)
			return 0;

		/*calculate t, scale parameters, ray intersects triangle */
		t = DOT(m_e2, qvec);
		inv_det = 1.0 / det;
		t *= inv_det;
		u *= inv_det;
		v *= inv_det;
	#else 		/*the non-culling branch */
		if (det > -EPSILON && det < EPSILON)
			return 0;
		inv_det = 1.0 / det;

		/* calculate distance from vert to ray origin */
		SUB3(tvec, S3, m_v1);

		/* calculate U parameter and test bounds */
		u = DOT(tvec, pvec) * inv_det;
		if (u < 0.0 || u > 1.0)
			return 0;

		/* prepare to test V parameter */
		CROSS(qvec, tvec, m_e1);

		/* calculate V parameter and test bounds */
		v = DOT(D3, qvec) * inv_det;
		if (v < 0.0 || u + v > 1.0)
			return 0;

		/* calculate t, ray intersects triangle */
		t = DOT(m_e2, qvec) * inv_det;
		if (t < 0.0)
			return 0;
		#endif
		return 1;

}

int MTTriangle::doNothing(Ray* ray)
{
	return 0;
}