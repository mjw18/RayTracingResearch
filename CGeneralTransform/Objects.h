/*
* Objects.h
*
*  Created on: Jun 24, 2015
*      Author: Mike
*/

#ifndef OBJECTS_H_
#define OBJECTS_H_

typedef struct Triangle {
	double v1[3];
	double v2[3];
	double v3[3];

	double inv[4][4];
}Triangle;

typedef struct Ray {
	double x;
	double y;
}Ray;

#define PIC_WIDTH 50.0
#define PIC_HEIGHT 50.0
#define Z 3
#endif /* OBJECTS_H_ */
