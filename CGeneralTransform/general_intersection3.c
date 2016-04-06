/*
* general_intersection3.c
*
*  Created on: Apr 13, 2015
*      Author: Mike
*/
/*
* general_intersection2.c
*
*  Created on: Apr 2, 2015
*      Author: Mike
*/

#include "LinearAlgebra.h"
#define EPSILON 0.0000001

int general_intersection3(double *S, double *D, double *v1, double *v2, double *v3,
	double *e1, double *e2, double *n,
	double *tg, double *xg, double *yg){

	double ta, wr[4], tD[4], transS, transD, tMin = 10000;

	if (n[0] != 0){

		double num = DOT(v1, n);

		transS = n[0] * S[0] + (n[1] * S[1] + n[2] * S[2] - num*S[3]);
		transD = n[0] * D[0] + (n[1] * D[1] + n[2] * D[2] - num*D[3]);

		ta = -transS / transD;

		/* Reject negative t values and parallel rays */
		if (ta < EPSILON || ta > tMin)
			return 0;

		/* Get Canonically Transformed Ray */
		SCALEMULT(tD, ta, D)
			ADD(wr, S, tD)

			if (n[0] > 0){

				double a, x2 = v3[1] * v1[2] - v3[2] * v1[1];

				if ((a = (e2[2] * wr[1] - e2[1] * wr[2] + x2*wr[3])) < EPSILON)
				{
					return 0;
				}

				double b, x1 = v2[1] * v1[2] - v2[2] * v1[1];

				if ((b = (-e1[2] * wr[1] + e1[1] * wr[2] - x1*wr[3])) < EPSILON)
				{
					return 0;
				}

				if (a + b <= n[0]){
					*tg = ta;
					return 1;
				}
			}

		if (n[0] < 0){

			double a, x2 = v3[1] * v1[2] - v3[2] * v1[1];

			if ((a = (e2[2] * wr[1] - e2[1] * wr[2] + x2*wr[3])) > -EPSILON)
			{
				return 0;
			}

			double b, x1 = v2[1] * v1[2] - v2[2] * v1[1];

			if ((b = (-e1[2] * wr[1] + e1[1] * wr[2] - x1*wr[3])) > -EPSILON)
			{
				return 0;
			}

			if (a + b >= n[0]){
				*tg = ta;
				return 1;
			}
		}

	}
	return 0;
}

