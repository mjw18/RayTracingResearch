/*
* MTIntersect.c
*
*  Created on: 1997
*      Author: Tomas Moller -- Chalmers University of Technology
*      	  & Ben Trumbore -- Cornell University
*      Title:  Fast, Minimum Storage Ray /Triangle Intersection
*      Source: http://www.cs.virginia.edu/~gfx/Courses/2003/ImageSynthesis/papers/Acceleration/Fast%20MinimumStorage%20RayTriangle%20Intersection.pdf
*/
#include "LinearAlgebra.h"
#define EPSILON 0.000001

int intersect_triangle(double orig[3], double dir[3],
	double vert0[3], double vert1[3], double vert2[3],
	double *t, double *u, double *v)
{
	double edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
	double det, inv_det;

	/* find vectors for two edges sharing vert 0*/
	SUB3(edge1, vert1, vert0);
	SUB3(edge2, vert2, vert0);

	/*begin calculating determinant, also used to calculate U parameter*/

	CROSS(pvec, dir, edge2);

	/*if determinant is near zero, ray lies in plane of triangle */

	det = DOT(edge1, pvec);

#ifdef TEST_CULL /*define TEST_CULL if culling is desired*/
	if (det < EPSILON)
		return 0;

	/* calculate distance from vert to ray origin*/
	SUB3(tvec, orig, vert0)

		/*calculate U parameter and test bounds*/
		*u = DOT(tvec, pvec);
	if (*u < 0.0 || *u > det)
		return 0;

	/*prepare to test V parameter*/
	CROSS(qvec, tvec, edge1);

	/*calculate V parameter and test bounds*/
	*v = DOT(dir, qvec);
	if (*v < 0.0 || *u + *v > det)
		return 0;

	/*calculate t, scale parameters, ray intersects triangle */
	*t = DOT(edge2, qvec);
	inv_det = 1.0 / det;
	*t *= inv_det;
	*u *= inv_det;
	*v *= inv_det;
#else 		/*the non-culling branch */
	if (det > -EPSILON && det < EPSILON)
		return 0;
	inv_det = 1.0 / det;

	/* calculate distance from vert to ray origin */
	SUB3(tvec, orig, vert0);

	/* calculate U parameter and test bounds */
	*u = DOT(tvec, pvec) * inv_det;
	if (*u < 0.0 || *u > 1.0)
		return 0;

	/* prepare to test V parameter */
	CROSS(qvec, tvec, edge1);

	/* calculate V parameter and test bounds */
	*v = DOT(dir, qvec) * inv_det;
	if (*v < 0.0 || *u + *v > 1.0)
		return 0;

	/* calculate t, ray intersects triangle */
	*t = DOT(edge2, qvec) * inv_det;
#endif
	return 1;
}
