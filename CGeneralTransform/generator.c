/*
* generator.c
*
*  Created on: Mar 28, 2015
*      Author: Mike
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Objects.h"


int genTrans(double *v1, double *v2, double *v3, double inv[4][4]);

int generator(int triangles, int rays, struct Triangle* triArray, struct Ray* rayArray){
	/*generate triangles and trace parameters using rand and loops
	* for an arbitrary number of each. Maybe pass this from main?
	* Use a command line parameter?

	int numSpecificTriangles = 1;
	double  triArray[triangles][3][3] ;
	double  rayArray[rays][2] ;
	*/

	int i;
	time_t t;

	srand((unsigned)time(&t));

	for (i = 0; i < triangles; i++)
	{
		triArray[i].v1[0] = (PIC_WIDTH*(double)rand() / RAND_MAX) - (PIC_WIDTH*(double)rand() / RAND_MAX);
		triArray[i].v1[1] = (PIC_HEIGHT*(double)rand() / RAND_MAX) - (PIC_HEIGHT*(double)rand() / RAND_MAX);
		triArray[i].v1[2] = (Z*(double)rand() / RAND_MAX) - (10 * (double)rand() / RAND_MAX);

		triArray[i].v2[0] = (PIC_WIDTH*(double)rand() / RAND_MAX) - (PIC_WIDTH*(double)rand() / RAND_MAX);;
		triArray[i].v2[1] = (PIC_HEIGHT*(double)rand() / RAND_MAX) - (PIC_HEIGHT*(double)rand() / RAND_MAX);
		triArray[i].v2[2] = (Z*(double)rand() / RAND_MAX) - (10 * (double)rand() / RAND_MAX);

		triArray[i].v3[0] = (PIC_WIDTH*(double)rand() / RAND_MAX) - (PIC_WIDTH*(double)rand() / RAND_MAX);;
		triArray[i].v3[1] = (PIC_HEIGHT*(double)rand() / RAND_MAX) - (PIC_HEIGHT*(double)rand() / RAND_MAX);
		triArray[i].v3[2] = (Z*(double)rand() / RAND_MAX) - (10 * (double)rand() / RAND_MAX);

		genTrans(triArray[i].v1, triArray[i].v2, triArray[i].v3, triArray[i].inv);
	}

	for (i = 0; i < rays; i++)
	{
		rayArray[i].x = (50 * (double)rand() / RAND_MAX);
		rayArray[i].y = (50 * (double)rand() / RAND_MAX);
	}

	return 0;
}
