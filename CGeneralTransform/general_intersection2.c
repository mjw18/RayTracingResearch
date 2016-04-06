/*
* general_intersection2.c
*
*  Created on: Apr 2, 2015
*      Author: Mike
*/
#include <time.h>
#include "LinearAlgebra.h"
#define EPSILON2 0.0000001

int general_intersection2(double *S, double *D, double *v1, double *v2, double *v3,
	double *tg, double *xg, double *yg, double inv[4][4])
{

	double tMin = 10000;

	double n[3], ta, wr[4], tD[4], transS, transD;

	//Do matrix set up stuff here for when b=c=0 formula

	//Get z components of transformed vectors for calculation of t value
	transS = inv[2][0] * S[0] + inv[2][1] * S[1] + inv[2][2] * S[2] + inv[2][3] * S[3];
	transD = inv[2][0] * D[0] + inv[2][1] * D[1] + inv[2][2] * D[2] + inv[2][3] * D[3];

	ta = -transS / transD;

	/* Reject negative t values and parallel rays */
	if (ta < EPSILON2 || ta > tMin)
		return 0;

	/* Get Canonically Transformed Ray */
	SCALEMULT(tD, ta, D)
		ADD(wr, S, tD)

		//test "x" barycentric component
		if ((*xg = inv[0][0] * wr[0] + inv[0][1] * wr[1] + inv[0][2] * wr[2] + inv[0][3] * wr[3]) < -EPSILON2)
			return 0;

	//test "y" barycentric component
	if ((*yg = inv[1][0] * wr[0] + inv[1][1] * wr[1] + inv[1][2] * wr[2] + inv[1][3] * wr[3]) < -EPSILON2)
		return 0;

	//final intersect test
	if (*yg + *xg <= 1){
		*tg = ta;
		return 1;
	}
	return 0;
}