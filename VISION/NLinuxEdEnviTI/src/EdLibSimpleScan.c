// ------------------------------------------------------------------
/**
 * @file EdLibScanVois3.c
 *
 * @brief Example of simple Image scan 
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

int SimpleScan(EdIMAGE *image, EdIMAGE *imres)
{
  EdPOINT       *point = NULL; /* current point */
  unsigned char uc; /* example of pixel read and write ... */
  

  if(crea_POINT(point) == NULL)          /* Memory Allocation of point */
  {
     fprintf(stderr,"Error of Memory Allocation \n");
     system("PAUSE"); // Windows Only
     return 1; 
  }

  /* --- Video Scan of the image, except the Border :
         Smooting by Mean Filtering  --- */	
  for(POINT_Y(point) = 0; POINT_Y(point) < NLIG(image); 
           POINT_Y(point)++)
  for(POINT_X(point) = 0; POINT_X(point) < NCOL(image); 
           POINT_X(point)++)
  {
    uc = PIXEL(image, point);
    PIXEL(imres, point) = uc;
  }/* --- End of the Image Video Scan --- */
  /* --- Memory Free  --- */
  free((void *)point);
  return 0;
} /* --- End of the Operator --- */   
