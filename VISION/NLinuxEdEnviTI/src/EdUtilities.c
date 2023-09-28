// ------------------------------------------------------------------
/**
 * @file 	EdUtilities.c
 *
 * @brief 	Functions of Reading, Writing, creation of images.
 *
 * @author 	Patrick J. Bonnin
 * @email  	patrick.bonnin@gmail.com
 * @date    2012.11.01 : creation.
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
#include "EdStructures.h"
#include "EdUtilities.h"

//    --- Functions of Utilities.h:
//   void Reading_ImageHeader(FILE *fichier, int *pncol, 
//        int *pnlig, unsigned char *pprof)
//   Rule  : Reading of the image header data on the image file
//   Output : Error if *pprof = 0
// 
//   int Creation_Image (EdIMAGE *image,int nlig, int ncol,
//				unsigned char prof)
//   Rule : Fill Image Header and Create Image Pixel Data 
//   Output : TRUE : OK, FALSE : Problem !
//
//   int Reading_ImageData(FILE *fichier,EdIMAGE *image); // Image Pixel Data
//   Rule : Read the Image Pixel Data from File
//   Output : TRUE : OK, FALSE : Problem !
//
//   int Writing_ImageData(FILE *fichier,EdIMAGE *image); // Image Pixel Data
//   Rule : Read the Image Pixel Data from File
//   Output : TRUE : OK, FALSE : Problem !
//
//   int Free_Image(EdIMAGE *image)
//   Rule  : Free the memory allocated from Image Pixel Data and Header
//   Output : TRUE : OK, FALSE : Problem !
//
//   void Label_ Conversion(EdIMAGE *imLbl, EdIMAGE *imCLbl)
//   Rule : Convertion of label image (int) into a color RGB image 
//        : for visualisation . 6 bits are taken into account
//        :  that is to say 64 colors 
//
// ---------------------------------------------------------------------

// Reading_ImageHeader ---------------------------------------------------
/** 
 * @brief  	Reading the Image Header from File.
 *
 *  Read only PGM and PPM files in Binary format
 * Possible to read with multiple comments beginning by '#'
 *		
 * @param	fichier : open image file 
 * @param	pnlig : pointer on the number of lines
 * @param	pncol : idem columns
 * @param	pprof : idem type : if 0 : Problem of reading
 *
 * @return 	None.
 */
// ------------------------------------------------------------------
int Reading_ImageHeader(FILE *fichier, int *pncol, 
  int *pnlig, unsigned char *pprof)
{
  char nom [512];
  char  *ret;
  *pprof = 0;
  
  /* --- Reading of the Magic Number --- */
  ret = fgets(nom,10,fichier);
  if (ret == NULL)
    return 1; // Problem of Reading
  if(nom[0] != 'P')
    return 2; // Not a PGM or PPM file
  
  if(nom[1] == '5')
    *pprof = 1; // PGM file
  else if(nom[1] == '6')
    *pprof = 3; // PPM file 
  else
    return 3; // Not a Binary PGM or PPM file
  
  /* --- Jump the optional comment(s) and reading the size --- */
  do
  {
    ret = fgets(nom,510,fichier);
    if (ret == NULL)
      return 1; // Problem of Reading
  }while (nom[0] == '#');
  
  /* --- Extraction of the Image Size --- */
  sscanf(nom, "%d %d", pncol, pnlig);
  
  /* --- Jump the optional comment(s) and reading 255 ! --- */
  do
  {
    ret = fgets(nom,510,fichier);
    if (ret == NULL)
      return 1; // Problem of Reading
  }while (nom[0] == '#');
  return 0;  
} /* End of Reading_ImageHeader */
// ------------------------------------------------------------------

// Creation_Image ---------------------------------------------------
/** 
 * @brief  	Filling of Header Data, and Creation of Image Pixel Data 
 *
 *  The EdIMAGE structure must be created before, using the macro :
 *  crea_IMAGE(image)
 *  Allocate the array of pixel, function of the depth or the type
 *  of the image
 *		
 * @param	image : la structure image, ie l'entete de l'image
 * @param	nlig : number of lines
 * @param	ncol : number of columns
 * @param	prof : depth or type
 *
 * @return 	TRUE if correct, else FALSE
 */
// ------------------------------------------------------------------
int Creation_Image (EdIMAGE *image, int nlig, int ncol, 
       unsigned char prof)
   
{
  /* --- Test of the creation of the EdIMAGE structure ---  */
  if (image == NULL) 
  {	
    fprintf(stderr,"the EdIMAGE is not allocated \n");
    return FALSE;
  }
   
  NLIG(image) = nlig; /* Filling of the Header */
  NCOL(image) = ncol;
  PROF(image) = prof;

  /* --- Creation of the Image Pixel Data--- */
  switch (prof)
  { 
    case 1: /* B&W or RVB Color Image */
    case 3:
    PIOCTET(image) = (unsigned char *)MALLOC( 			
      (long)NLIG(image)*(long)NCOL(image)* (long)prof * sizeof(unsigned char));
    
   /* Test de Reussite de l'Allocation Memoire */
    if (PIOCTET(image) == NULL)
    {	
      fprintf(stderr,"Problem of Memory Allocation \n");
      return FALSE;
    }
    break;

  case 2: /* Label or Difference Image */
    PIETIQ(image) = (int *)MALLOC( 
      (long)NLIG(image)*(long)NCOL(image)* sizeof(int));
   
   /* Test de Reussite de l'Allocation Memoire */
    if (PIETIQ(image) == NULL)
    {	
      fprintf(stderr,"Problem of Memory Allocation \n");
      return FALSE;
    }
    break;
    
  default: /* type inexistant */
    fprintf(stderr,"Unknonw depth or type \n");
    return FALSE;
    break;
  }
  return TRUE;
} /* --- End of Creation_Image Function --- */
// ------------------------------------------------------------------

// Reading_ImageData ----------------------------------------------------
/** 
 * @brief  	Reading of the Pixel Image Data
 *		
 *	Read the Image Pixel Data from the image file,
 *  and store on EdIMAGE structure, which must be created before 
 *	     
 * @param	fichier : pointer Image file
 * @param	image : pointer EdIMAGE
 *
 * @return 	TRUE if correct, else FALSE
 */
// ------------------------------------------------------------------
int Reading_ImageData(FILE *fichier,EdIMAGE *image)
{
  int ret;
  switch(PROF(image))
  {
    case 1:
    case 3:
      ret = fread(PIOCTET(image),sizeof(unsigned char),    
	    (long)NLIG(image) * (long)NCOL(image) * (long)PROF(image),fichier);
#if WINDOWS
      if (ret == 0)
#else
      if (ret != NLIG(image) * NCOL(image) * PROF (image))
#endif
        return FALSE;
    break;

    case 2:			
      ret = fread(PIETIQ(image),sizeof(int),
	    (long)NLIG(image) * (long)NCOL(image),fichier);
#if WINDOWS
      if (ret == 0)
#else
      if (ret != NLIG(image) * NCOL(image))
#endif
        return FALSE;
    break;	
    
   default:
    fprintf(stderr,"Type non existant \n");
    return FALSE;
  } /* fin du switch */
  return TRUE;

} /* --- End of Reading_ImageData --- */

// ------------------------------------------------------------------
// Writing_ImageData ----------------------------------------------------
/** 
 * @brief  	Writing of the Pixel Image Data
 *		
 *	Write the Image Pixel Data on the image file,
 *	     
 * @param	fichier : pointer Image file
 * @param	image : pointer EdIMAGE
 *
 * @return 	TRUE if correct, else FALSE
 */
// ------------------------------------------------------------------
int Writing_ImageData(FILE *fichier,EdIMAGE *image)
{
  int ret;
  switch(PROF(image))
  {
    case 1:
    case 3:
      ret = fwrite(PIOCTET(image),sizeof(unsigned char),    
	    (long)NLIG(image) * (long)NCOL(image) * (long)PROF(image),fichier);
#if WINDOWS
      if (ret == 0)
#else
      if (ret != NLIG(image) * NCOL(image) * PROF (image))
#endif
        return FALSE;
    break;

    case 2:			
      ret = fwrite(PIETIQ(image),sizeof(int),
	    (long)NLIG(image) * (long)NCOL(image),fichier);
#if WINDOWS
      if (ret == 0)
#else
      if (ret != NLIG(image) * NCOL(image))
#endif
        return FALSE;
    break;	
    
   default:
    fprintf(stderr,"Type non existant \n");
    return FALSE;
  } /* fin du switch */
  return TRUE;
} /* --- End of Writing_ImageData --- */

// Free_Image -----------------------------------------------------
/** 
 * @brief	Free the MEmory allocated for the EdIMAGE
 *
 * Free the Image Pixel Memory end the the Image Header.
 *		
 * @param	image : pointer on EdIMAGE
 *
 * @return 	TRUE : Ok, Else FALSE.
 */
// ------------------------------------------------------------------
int Free_Image(EdIMAGE *image)
{
  int ret;
  switch(PROF(image))	/* liberation du tableau de pixels */
  {
    case 1: /* B&W image */
    case 3: /* RVB Color Image */
    FREE(PIOCTET(image));
    ret = TRUE;			
    break;
      
    case 2: /* Label or Difference Image */
      FREE(PIETIQ(image));
      ret = TRUE;	
      break;			

    default:
      fprintf(stderr,"depth or type Error \n");
      ret = FALSE;	
      break;	
  }
  free((void *)image);
  return ret;
}
//  Label_ Conversion -----------------------------------------------------
/** 
 * @brief	Convertion of label image (int) into a color RGB image 
 * for visualisation . 6 bits are taken into accoun that is to say 64 colors. 
 *		
 * @param	imLbl  : pointer on image of labels (int)
 * @param	imCLbl : pointer on color RGB image
 *
 * @return 	TRUE : Ok, Else FALSE.
 */
// ------------------------------------------------------------------
void Label_Conversion(EdIMAGE *imLbl, EdIMAGE *imCLbl)
{
  EdPOINT         *point = NULL;
  unsigned char	  rang;
  unsigned char   palette[64][3]; /* color palette  */
  
  if(crea_POINT(point) == NULL)
  {
    fprintf(stderr,"Memory Allocation Error : Label_Convertion \n");
    exit(0);
  }
  
  LUT_Edition(palette);

  for (POINT_Y(point) = 0; POINT_Y(point) < NLIG(imLbl); 
       POINT_Y(point)++)
  for (POINT_X(point) = 0; POINT_X(point) < NCOL(imLbl); 
       POINT_X(point)++)
  {
    if(LABEL(imLbl,point) == 0xffff) /* special cases : masks */
    {                                
      PIXEL_R(imCLbl, point) = 0;
      PIXEL_V(imCLbl, point) = 0;
      PIXEL_B(imCLbl, point) = 0;
    }
    else /* ordinary case */
    {  
      rang = (unsigned char)(LABEL(imLbl, point) & 0x003f);
      PIXEL_R(imCLbl, point) =  palette [(int)rang][0];
      PIXEL_V(imCLbl, point) =  palette [(int)rang][1];
      PIXEL_B(imCLbl, point) =  palette [(int)rang][2];
      
      if ((PIXEL_R(imCLbl, point) == 255) && (PIXEL_V(imCLbl, point) == 255)
        && (PIXEL_B(imCLbl, point) == 255))
      {
        PIXEL_R(imCLbl, point) =  100;
        PIXEL_V(imCLbl, point) =  100;
        PIXEL_B(imCLbl, point) =  100;     
      }
      /* --- to avoid to visualize in black no zero label --- */
      if ((rang == 0) && (LABEL(imLbl, point) != 0))
      {
	    PIXEL_R(imCLbl, point) = 50;
	    PIXEL_V(imCLbl, point) = 50;
	    PIXEL_B(imCLbl, point) = 50;
      }
      else if ((rang == 0) && (LABEL(imLbl, point) == 0))
      {
	    PIXEL_R(imCLbl, point) = 255;
	    PIXEL_V(imCLbl, point) = 255;
	    PIXEL_B(imCLbl, point) = 255;
      }
    }
  }
  
  free((void *)point);
} /* End of Conversion of label image */

// Level -----------------------------------------------------------
/** 
 * @brief  	Function to Edit Look Up Table
 *		
 * @param	k
 *
 * @return "unsigned char"
 */
// ------------------------------------------------------------------
unsigned char  Level(int k)

{
  unsigned char n;

  switch(k)
  {
    case 0:
      n = 0;
      break;
    
    case 1:
      n = 85;
      break;
    
    case 2:
      n = 170;
      break;
    
    case 3:
      n = 255;
      break;

    default:
      fprintf(stderr,"Error of Level\n");
      exit(0);
  } /* switch end */
  return(n);
} /* End of Level PRocessing */
/*--------------------------------------------------------*/
// LUT_Edition-------------------------------------------------------
/** 
 * @brief  	To Edit the Color Palette
 *		
 * @param	palette
 *
 * @return None.
 */
// ------------------------------------------------------------------
void LUT_Edition(unsigned char palette[64][3])
{
  int   kr; /* red */
  int   kv; /* green */
  int   kb; /* bleue */
  int   rang;
  unsigned char red, green, bleue;

  for (kr = 0; kr < 4; kr++)
  {
    red = Level(kr);
    for (kv = 0; kv < 4; kv++)
    {
      green = Level(kv);
      for (kb = 0; kb < 4; kb++)
      {
	    bleue = Level(kb);
        rang = kb + kv * 4 + kr * 16;
	    palette [rang][0] = red;
	    palette [rang][1] = green;
	    palette [rang][2] = bleue;
      } /* bleue loop */	  
    } /* green loop */
  } /* red loop */
} /* End of Palette Edition */
