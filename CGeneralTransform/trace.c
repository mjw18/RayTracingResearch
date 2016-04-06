/*
* trace.c
*
*  Created on: Mar 28, 2015
*      Author: Mike
*/
#include <stdio.h>
#include <time.h>
#include "LinearAlgebra.h"
#include "Objects.h"

#define COL 100.0
#define ROW 100.0

int general_intersection(double *S, double *D,
	double *v1, double *v2, double *v3,
	double *tg, double *xg, double *yg, double inv[4][4]);

int general_intersection2(double *S, double *D,
	double *v1, double *v2, double *v3,
	double *tg, double *xg, double *yg, double inv[4][4]);

int general_intersection3(double *S, double *D,
	double *v1, double *v2, double *v3,
	double *e1, double *e2, double *n,
	double *tg, double *xg, double *yg);

int intersect_triangle(double orig[3], double dir[3],
	double vert0[3], double vert1[3], double vert2[3],
	double *t, double *u, double *v);

int trace(int triangles, int rays, struct Triangle* triArray, struct Ray* rayArray, double zs)
{
	int i, j, countb = 0, countg = 0, countg2 = 0, countg3 = 0;
	clock_t begin, end, begin2, end2, begin3, end3;
	double gen_time = 0, bar_time = 0, gen2_time = 0, gen3_time = 0, pre1_time = 0, pre3_time = 0, preb_time = 0;

	/* Set world coordinates */
	double xL = -PIC_WIDTH / 2;
	double yT = PIC_HEIGHT / 2;

	/* Set pixel dimension */
	double w = PIC_WIDTH / ROW;
	double h = PIC_HEIGHT / COL;

	double xg, yg, tg = 10000;
	double t, u, v;

	/* Intersect using ith test ray */
	for (i = 0; i < rays; i++)
	{

		/* Create source and pixel vectors for GT */

		double S[4] = { 0, 0, zs, 1 };
		double P[4] = { xL + rayArray[i].x*w, yT - h*rayArray[i].y, zs - 1, 1 };
		double D[4];
		SUB(D, P, S)
		
		begin3 = clock();
		for (j = 0; j < triangles; j++)
		{
			double* v1 = triArray[j].v1;
			double* v2 = triArray[j].v2;
			double* v3 = triArray[j].v3;

			double e1[3], e2[3], n[3];
			SUB3(e1, v2, v1)
			SUB3(e2, v3, v1)
			CROSS(n, e1, e2)

			//Loop through two methods for jth triangle and ith ray
			countg2 += general_intersection2(S, D, v1, v2, v3, &tg, &xg, &yg, triArray[j].inv);
			//printf("t: %f, u: %f, v: %f \n", tg, xg, yg);
			//printf("\ninverse\n");
			//printf("%f %f %f %f\n", triArray[j].inv[0][0], triArray[j].inv[0][1], triArray[j].inv[0][2], triArray[j].inv[0][3]);
			//printf("%f %f %f %f\n", triArray[j].inv[1][0], triArray[j].inv[1][1], triArray[j].inv[1][2], triArray[j].inv[1][3]);
			//printf("%f %f %f %f\n", triArray[j].inv[2][0], triArray[j].inv[2][1], triArray[j].inv[2][2], triArray[j].inv[2][3]);
		}
		end3 = clock();
		gen2_time += ((double)(end3 - begin3)) / CLOCKS_PER_SEC;
	}

	/* Intersect using ith test ray */
	for (i = 0; i < rays; i++)
	{
			/* Create source and direction vectors and t u v pointers for MT */
		double S3[3] = { 0, 0, zs };
		double P3[3] = { xL + rayArray[i].x*w, yT - h*rayArray[i].y, zs - 1 };
		double D3[3];
		SUB3(D3, P3, S3)

		begin2 = clock();
		for (j = 0; j < triangles; j++)
		{
			double* v1 = triArray[j].v1;
			double* v2 = triArray[j].v2;
			double* v3 = triArray[j].v3;

			double e1[3], e2[3], n[3];
			SUB3(e1, v2, v1)
			SUB3(e2, v3, v1)
			CROSS(n, e1, e2)
				//Loop through two methods for jth triangle and ith ray
			
			countb += intersect_triangle(S3, D3, triArray[j].v1, triArray[j].v2, triArray[j].v3, &t, &u, &v);
			//printf("t: %f, u: %f, v: %f \n", t, u, v);
		}
		end2 = clock();
		bar_time += ((double)(end2 - begin2)) / CLOCKS_PER_SEC;
	}

	printf(" Reduced General Time: %f, Hits: %d, Preprocess Time: %f \n\n", gen2_time, countg2, pre1_time);
	printf(" Barycentric Time: %f, Hits: %d, Preprocess Time: %f\n", bar_time, countb, preb_time);
	return 0;
}
