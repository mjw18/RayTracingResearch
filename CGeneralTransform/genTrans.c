/*
* genTrans.c
*
*  Created on: Mar 22, 2015
*      Author: Mike
*/
#include "LinearAlgebra.h"

int genTrans(double *v1, double *v2, double *v3, double inv[4][4]){

	double e1[3], e2[3], n[3], x1[3], x2[3];

	SUB3(e1, v2, v1)
		SUB3(e2, v3, v1)
		CROSS(n, e1, e2)
		/*CROSS(x1,v2,v1)
		CROSS(x2,v3,v1)*/

		//Used in index [3][4] of each matrix
		double num = DOT(v1, n);

	if (n[0] != 0){

		x1[0] = v2[1] * v1[2] - v2[2] * v1[1];
		x2[0] = v3[1] * v1[2] - v3[2] * v1[1];

		//printf("a\n");
		//Do matrix set up stuff here for when b=c=0 formula
		inv[0][0] = 0;
		inv[0][1] = e2[2] / n[0];
		inv[0][2] = -e2[1] / n[0];
		inv[0][3] = x2[0] / n[0];

		inv[1][0] = 0;
		inv[1][1] = -e1[2] / n[0];
		inv[1][2] = e1[1] / n[0];
		inv[1][3] = -x1[0] / n[0];

		inv[2][0] = 1;
		inv[2][1] = n[1] / n[0];
		inv[2][2] = n[2] / n[0];
		inv[2][3] = -num / n[0];

		inv[3][0] = 0;
		inv[3][1] = 0;
		inv[3][2] = 0;
		inv[3][3] = 1;

		return 0;
	}

	else if (n[1] == 0){
		//Make Sure we have valid triangle
		if (n[2] == 0){
			return 1;
		}
		//printf("c\n");

		x1[2] = v2[0] * v1[1] - v2[1] * v1[0];
		x2[2] = v3[0] * v1[1] - v3[1] * v1[0];
		//c case
		inv[0][0] = e2[1] / n[2];
		inv[0][1] = -e2[0] / n[2];
		inv[0][2] = 0;
		inv[0][3] = x2[2] / n[2];

		inv[1][0] = -e1[1] / n[2];
		inv[1][1] = e1[0] / n[2];
		inv[1][2] = 0;
		inv[1][3] = -x1[2] / n[2];

		inv[2][0] = n[0] / n[2];
		inv[2][1] = n[1] / n[2];
		inv[2][2] = 1;
		inv[2][3] = -num / n[2];

		inv[3][0] = 0;
		inv[3][1] = 0;
		inv[3][2] = 0;
		inv[3][3] = 1;

		return 0;

	}
	else{
		x1[1] = v2[2] * v1[0] - v2[0] * v1[2];
		x2[1] = v3[2] * v1[0] - v3[0] * v1[2];

		//printf("b\n");
		//b case
		inv[0][0] = -e2[2] / n[1];
		inv[0][1] = 0;
		inv[0][2] = e2[0] / n[1];
		inv[0][3] = x2[1] / n[1];

		inv[1][0] = e1[2] / n[1];
		inv[1][1] = 0;
		inv[1][2] = -e1[0] / n[1];
		inv[1][3] = -x1[1] / n[1];

		inv[2][0] = n[0] / n[1];
		inv[2][1] = 1;
		inv[2][2] = n[2] / n[1];
		inv[2][3] = -num / n[1];

		inv[3][0] = 0;
		inv[3][1] = 0;
		inv[3][2] = 0;
		inv[3][3] = 1;

		return 0;
	}
}