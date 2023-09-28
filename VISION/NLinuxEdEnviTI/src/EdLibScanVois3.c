// ------------------------------------------------------------------
/**
 * @file EdLibScanVois3.c
 *
 * @brief Example of Image scan
 * using 3 by 3 pixel neighbourhood
 * This file is the part "Operator" itself
 *
 * @author Patrick Bonnin
 * @email  patrick.bonnin@gmail.com
 * @date 2022.06.15 : creation.
 * @date 2022.06.15 : last modification.
 */
// ------------------------------------------------------------------
/* COPYRIGHT (C)	2022, P. Bonnin <patrick.bonnin@gmail.com>
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
 * 2022.06.15 : creation
 */
// ------------------------------------------------------------------
#include "EdStructures.h"
#include "EdUtilities.h"

int ScanVois3(EdIMAGE *image, EdIMAGE *imres)
{
  // current and neighbour (voisin in French) point creation 
  EdPOINT	*point = NULL, *pointv = NULL;
  // index of lines and columns of the 3X3 neighbourhood
  int	i,j;                             
  unsigned char uc; /* example of pixel read and write ... */


  if(crea_POINT(point) == NULL)          /* Memory Allocation of point */
  {
     fprintf(stderr,"Error of Memory Allocation \n");
     system("PAUSE"); // Windows Only
     return 1;
  }
  if(crea_POINT(pointv) == NULL)
  {
     fprintf(stderr,"Error of Memory Allocation \n");
     system("PAUSE"); // Windows Only
     return 1;
  }
  /* --- Initialisation of Image Borders : Copy of the Original Image  --- */
  for(POINT_X(point) = 0; POINT_X(point) < NCOL(image);
           POINT_X(point)++)
  {
    POINT_Y(point) = 0;                  /* first line */
    PIXEL(imres, point) = 0;

    POINT_Y(point) = NLIG(image) - 1;    /* last line */
    PIXEL(imres, point) = 0;
  } /*--- End of copy of first and last lines --- */

  for(POINT_Y(point) = 0; POINT_Y(point) < NLIG(image);
           POINT_Y(point)++)
  {
    POINT_X(point) = 0;                  /* first column */
    PIXEL(imres, point) = 0;

    POINT_X(point) = NCOL(image) - 1;    /* last column */
    PIXEL(imres, point) = 0;
  } /*--- End of copy of first and last columns --- */

  /* --- Video Scan of the image, except the Border :
         Smooting by Mean Filtering  --- */
  for(POINT_Y(point) = 1; POINT_Y(point) < NLIG(image) - 1;
           POINT_Y(point)++)
  for(POINT_X(point) = 1; POINT_X(point) < NCOL(image) - 1;
           POINT_X(point)++)
  {
    /* --- ... Initialisation  ... */
    /* ---  Video Scan of the 3x3 neighbourhood --- */
    for(j = 0; j < 3; j++)
    for(i = 0; i < 3; i++)
    {
      /* Computation of the Image Coordinates of the Neighbour point */
      POINT_X(pointv) = POINT_X(point) + i - 1;
      POINT_Y(pointv) = POINT_Y(point) + j - 1;

      uc = PIXEL(image, pointv);
    } /* --- End of the Neighbourhood Video Scan --- */


    PIXEL(imres, point) = PIXEL(image, point);
  }/* --- End of the Image Video Scan --- */
  /* --- Memory Free  --- */
  free((void *)pointv);
  free((void *)point);
  return 0;
} /* --- End of the Operator --- */
