// ------------------------------------------------------------------
/**
 * @file EdStructures.h
 *
 * @brief Data Structures : EdIMAGE, EdPOINT and Macro Definition
 * to access to the data
 *
 * 
 * @author Patrick Bonnin
 * @email  patrick.bonnin@gmail.com
 * @date 2012.11.01 : creation.
 * @date 2012.11.01 : last modification.
 */
// ------------------------------------------------------------------
/* COPYRIGHT (C)	2012, P. Bonnin <patrick.bonnin@gmail.com>
 *
 * This  library  is  a free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as  published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This  Library  is  distributed in the hope that it will be useful,
 * but  WITHOUT  ANY  WARRANTY;  without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULIAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You  should  have received a copy of the GNU Lesser General Public 
 * License  along  with  this  library;  if  not,  write  to the Free 
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
// ------------------------------------------------------------------
/* Modifications :
 * 2012.11.01 : creation
 */
// ------------------------------------------------------------------
#ifndef _Struct
#define _Struct
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define WINDOWS 1

// Some Usefull constants and macros
#define TRUE    1
#define FALSE   0
#define PI 3.14159

#define	ABS(X) (((X) > 0) ? (X) : -(X)
#define SIGN(X) (((X) > 0) ? 1 : (((X) < 0) ? -1 : 0 )) 
#define MIN(X,Y) (((X) > (Y)) ? (Y) : (X))
#define MAX(X,Y) (((X) > (Y)) ? (X) : (Y))
		
#define MALLOC(XX) malloc(XX)
#define FREE(XX) free(XX)

/* -------------------------------------------------------------------- */		
/* --- Data Structures --- */	       
/* --- EdIMAGE : union of pointers PDATA --- */
union pdata
{
  unsigned char   *poctet; /* N&B, RVB or YUV Color Image */
  int             *petiq;  /* label or difference Image */
  float 	      *preel;  /* Real Image */
};		
typedef union pdata PDATA;

/* ---	EdIMAGE Structure 		--- */
struct image 	
{	
  int         nlig; 	/* number of lines */
  int         ncol; 	/* number of columns */
  unsigned char prof; 	/* depth : 1 N&B, 3 RVB, but type : YUV : 5 */
  PDATA       ptdata;   /* union of pointers */
};
typedef struct image EdIMAGE;

// Coding depths or types of Image
// 1 : B&W, 3 RVB Color Image
// 2 : Label or Difference Image

/* --- EdPOINT Structure --- */
struct point
{
  int   x; /* x coordinate */
  int   y; /* y coordinate */
};
typedef struct point EdPOINT;

/* --------------------------------------------------------------*/
/*    MACROS : Acces to the data, and Memory Allocation          */ 
/* --------------------------------------------------------------*/
/* --- EdIMAGE   --- */
/* --- Acces to the Data --- */
#define NLIG(XX) ((XX)->nlig) /* number of Lines */
#define NCOL(XX) ((XX)->ncol) /* number of column */
#define PROF(XX) ((XX)->prof) /* depth or type*/

/* --- Memory Allocation --- */
#define crea_IMAGE(XX) ((XX) = (EdIMAGE *)MALLOC(sizeof(EdIMAGE)))

/* --- Acces to Image Data : First Pixel Address --- */
#define PIOCTET(XX) ((XX)->ptdata.poctet)        /* unsigned char data */
#define PIETIQ(XX) ((XX)->ptdata.petiq)          /* int data */
#define PIFLOAT(XX) ((XX)->ptdata.preel)         /* float data */

/* --- EdPOINT --- */
/* --- Acces to the Data --- */
#define POINT_X(XX) ((XX)->x)
#define POINT_Y(XX) ((XX)->y)

/* --- Memory Allocation --- */
#define crea_POINT(XX) ((XX) = (EdPOINT *)MALLOC(sizeof(EdPOINT)))
		
/* --- Acces to PIXELS --- */
/* --- B&W Image --- */
#define PIXEL(XX,YY) (*(((XX)->ptdata.poctet)+(long)((YY)->x)+(long)((XX)->ncol)*(long)((YY)->y)))

/* --- R,G,B Color Image  --- */
/* Red Component */
#define PIXEL_R(XX,YY) (*(((XX)->ptdata.poctet)+3*((long)((YY)->x)+(long)((XX)->ncol)*(long)((YY)->y)))) 

/* Green Component : Green is Vert in French !! */
#define PIXEL_V(XX,YY) (*(((XX)->ptdata.poctet)+3*((long)((YY)->x)+(long)((XX)->ncol)*(long)((YY)->y)) + 1))

/* Bleue Component */
#define PIXEL_B(XX,YY) (*(((XX)->ptdata.poctet)+3*((long)((YY)->x)+(long)((XX)->ncol)*(long)((YY)->y)) + 2)) 

/* --- Label Image --- */
#define LABEL(XX,YY) (*(((XX)->ptdata.petiq)+(long)((YY)->x)+(long)((XX)->ncol)*(long)((YY)->y)))


#endif














