/*
* general_intersection.c
*
*  Created on: Apr 2, 2015
*      Author: Mike
*/


#include "LinearAlgebra.h"
#define EPSILON2 0.0000001

//int genTrans(double *v1, double *v2, double *v3, double inv[4][4]);
int triangleHit(double *S, double *D, double inv[4][4], double tMin,
	double *tg, double *xg, double *yg);

int general_intersection(double *S, double *D, double *v1, double *v2, double *v3,
	double *tg, double *xg, double *yg, double inv[4][4]){

	double tMin = 10000;
	/*get triangle inverse, end if no matrix */

	/*calculate hit*/
	return(triangleHit(S, D, inv, tMin, tg, xg, yg));

}

int triangleHit(double * S, double * D, double inv[4][4], double tMin,
	double *tgen, double *xgen, double *ygen) {
	double ta, wr[4], tD[4], transS, transD;

	transS = inv[2][0] * S[0] + inv[2][1] * S[1] + inv[2][2] * S[2] + inv[2][3] * S[3];
	transD = inv[2][0] * D[0] + inv[2][1] * D[1] + inv[2][2] * D[2] + inv[2][3] * D[3];

	ta = -transS / transD;

	/* Reject negative t values and parallel rays */
	if (ta < EPSILON2 || ta > tMin)
		return 0;
	/* Get Canonically Transformed Ray */

	SCALEMULT(tD, ta, D)
		ADD(wr, S, tD)
		//MATMULT(cr, inv, wr)

		if ((*xgen = inv[0][0] * wr[0] + inv[0][1] * wr[1] + inv[0][2] * wr[2] + inv[0][3] * wr[3]) < EPSILON2)
			return 0;

	if ((*ygen = inv[1][0] * wr[0] + inv[1][1] * wr[1] + inv[1][2] * wr[2] + inv[1][3] * wr[3]) < EPSILON2)
		return 0;

	if (*ygen + *xgen <= 1){
		*tgen = ta;
		return 1;
	}
	return 0;
}
