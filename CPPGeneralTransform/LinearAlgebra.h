/*
* Citation for macros dealing wth 3-compoent vectors taken from M&T's original code
* 
* Created on: 1997
*      Author: Tomas Moller -- Chalmers University of Technology
*      	  & Ben Trumbore -- Cornell University
*      Title:  Fast, Minimum Storage Ray /Triangle Intersection
*      Source: http://www.cs.virginia.edu/~gfx/Courses/2003/ImageSynthesis/papers/Acceleration/Fast%20MinimumStorage%20RayTriangle%20Intersection.pdf
*
* 4-component macros
*  Created on: Mar 30, 2015
*      Author: Mike Weber
*
*/

#ifndef LINEARALGEBRA_H_
#define LINEARALGEBRA_H_

#define CROSS(res, v1, v2)\
		res[0]=v1[1]*v2[2]-v1[2]*v2[1];\
		res[1]=v1[2]*v2[0]-v1[0]*v2[2];\
		res[2]=v1[0]*v2[1]-v1[1]*v2[0];
#define DOT(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])
#define MATMULT(res,mat,v)\
		res[0]=(mat[0][0]*v[0]+mat[0][1]*v[1]+mat[0][2]*v[2]+mat[0][3]*v[3]);\
		res[1]=(mat[1][0]*v[0]+mat[1][1]*v[1]+mat[1][2]*v[2]+mat[1][3]*v[3]);\
		res[2]=(mat[2][0]*v[0]+mat[2][1]*v[1]+mat[2][2]*v[2]+mat[2][3]*v[3]);\
		res[3]=(mat[3][0]*v[0]+mat[3][1]*v[1]+mat[3][2]*v[2]+mat[3][3]*v[3]);
#define SUB(res,v1,v2)\
		res[0]=v1[0]-v2[0];\
		res[1]=v1[1]-v2[1];\
		res[2]=v1[2]-v2[2];\
		res[3]=v1[3]-v2[3];
#define SUB3(res,v1,v2)\
		res[0]=v1[0]-v2[0];\
		res[1]=v1[1]-v2[1];\
		res[2]=v1[2]-v2[2];
#define ADD(res,v1,v2)\
		res[0]=v1[0]+v2[0];\
		res[1]=v1[1]+v2[1];\
		res[2]=v1[2]+v2[2];\
		res[3]=v1[3]+v2[3];
#define ADD3(res,v1,v2)\
		res[0]=v1[0]+v2[0];\
		res[1]=v1[1]+v2[1];\
		res[2]=v1[2]+v2[2];
#define SCALEMULT(res,m,v1)\
		res[0]=m*v1[0];\
		res[1]=m*v1[1];\
		res[2]=m*v1[2];\
		res[3]=m*v1[3];

#endif /* LINEARALGEBRA_H_ */
