// ------------------------------------------------------------------
/**
 * @file 	EdUtilities.h
 *
 * @brief 	Prototypes of Functions of Reading, Writing, creation of images.
 *
 * @author 	Patrick J. Bonnin
 * @email  	patrick.bonnin@gmail.com
 * @date 2012.11.01 : creation.
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
#ifndef _UT
#define _UT
int Reading_ImageHeader(FILE *fichier, int *pncol, 
  int *pnlig, unsigned char *pprof);
int Creation_Image (EdIMAGE *image, int nlig, int ncol, 
       unsigned char prof);
int Reading_ImageData(FILE *fichier,EdIMAGE *image);
int Writing_ImageData(FILE *fichier,EdIMAGE *image);
int Free_Image(EdIMAGE *image);
void Label_Conversion(EdIMAGE *imLbl, EdIMAGE *imCLbl);
void LUT_Edition(unsigned char palette[64][3]);
unsigned char  Level(int k);

#endif











