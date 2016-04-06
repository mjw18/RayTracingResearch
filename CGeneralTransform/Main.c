/*
* main.c
*
*  Created on: Mar 22, 2015
*      Author: Mike
*/
#include "stdio.h"
#include "LinearAlgebra.h"
#include "Objects.h"


int generator(int triangles, int rays, struct Triangle* triArray, struct Ray* rayArray);
int trace(int triangles, int rays, struct Triangle* triArray, struct Ray* rayArray, double z);
#define numTriangles 1000
#define numRays 10000

int main(void){

	//int numTriangles = 10000;
	//int numRays = 10000;

	Triangle tris[numTriangles];
	Ray rays[numRays];

	generator(numTriangles-1, numRays-1, tris, rays);

	tris[numTriangles - 1].v1[0] = 0;
	tris[numTriangles -	1].v1[1] = -1;
	tris[numTriangles - 1].v1[2] = 0;

	tris[numTriangles - 1].v2[0] = 0;
	tris[numTriangles - 1].v2[1] = -1;
	tris[numTriangles - 1].v2[2] = -100;

	tris[numTriangles - 1].v3[0] = 100;
	tris[numTriangles - 1].v3[1] = -1;
	tris[numTriangles - 1].v3[2] = 0;

	genTrans(tris[numTriangles - 1].v1, tris[numTriangles - 1].v2, tris[numTriangles - 1].v3, tris[numTriangles - 1].inv);

	rays[numRays - 1].x = PIC_WIDTH + 0.1;
	rays[numRays - 1].y = PIC_HEIGHT + 0.2;

	trace(numTriangles, numRays, tris, rays, Z);

	int a;
	scanf_s("%d", &a);

	return 0;
}
