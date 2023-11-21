/* -----------------------------------------------------*/
/* Fichier  : CVVidInRangeHSV.cpp                       */
/* Role     : Seuillage parallelepipedique HSV          */
/*          : Decomposition en Composantes Connexes     */
/*          :                                           */
/* Auteur   : Patrick Bonnin                            */
/*          : Cours OpenCV 2022 - OpenCV4               */
/*          : Traitements Elementaires                  */
/* -----------------------------------------------------*/
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

#define SURFMIN 2500

using namespace cv;
using namespace std;

int high_h = 179, low_h = 0;
int high_s = 255, low_s = 0;
int high_v = 255, low_v = 0;

Mat src, src_hsv, select_pts;
Mat K ; // Kernel : element structurant;

void inRangeDemo( int, void* );
void Low_h (int, void* );
void High_h (int, void* );

void Low_s (int, void* );
void High_s (int, void* );

void Low_v (int, void* );
void High_v (int, void* );

/* --- Blobs --- */
int area_min = 100;
vector <vector <Point> > contours;
vector <Vec4i> hierarchy;

Mat edges, polygones;
void BlobUpgrade( int, void* );

int main( int argc, char** argv )
{
  Mat src;
  VideoCapture cap(0); // 0 pour une seule camera
  if(!cap.isOpened())
  {
      return -1;
  }
  
  namedWindow( "Image", WINDOW_AUTOSIZE );

  namedWindow( "Reglage", WINDOW_AUTOSIZE );
  namedWindow( "Seuillage", WINDOW_AUTOSIZE );

  createTrackbar( "HUE low",
                  "Reglage", &low_h,
                  179, Low_h );

  createTrackbar( "HUE high",
                  "Reglage", &high_h,
                  179, High_h );
        
  createTrackbar( "SATURATION low",
                  "Reglage", &low_s,
                  255, Low_s );

  createTrackbar( "SATURATION high",
                  "Reglage", &high_s,
                  255, High_s );
  
  createTrackbar( "VALUE low",
                  "Reglage", &low_v,
                  255, Low_v );

  createTrackbar( "VALUE high",
                  "Reglage", &high_v,
                  255, High_v );
                  
  setTrackbarMax ("HUE low", "Reglage", 179);
  setTrackbarMin ("HUE low", "Reglage", 0);
  setTrackbarPos ("HUE low", "Reglage", 0);
  setTrackbarMax ("HUE high", "Reglage", 179);
  setTrackbarMin ("HUE high", "Reglage", 0);
  setTrackbarPos ("HUE high", "Reglage", 255);
  
  setTrackbarMax ("SATURATION low", "Reglage", 255);
  setTrackbarMin ("SATURATION low", "Reglage", 0);
  setTrackbarPos ("SATURATION low", "Reglage", 0);
  setTrackbarMax ("SATURATION high", "Reglage", 255);
  setTrackbarMin ("SATURATION high", "Reglage", 0);
  setTrackbarPos ("SATURATION high", "Reglage", 255);
  
  setTrackbarMax ("VALUE low", "Reglage", 255);
  setTrackbarMin ("VALUE low", "Reglage", 0);
  setTrackbarPos ("VALUE low", "Reglage", 0);
  setTrackbarMax ("VALUE high", "Reglage", 255);
  setTrackbarMin ("VALUE high", "Reglage", 0);
  setTrackbarPos ("VALUE high", "Reglage", 255);
  
  K = getStructuringElement(MORPH_RECT, Size(3,3));

  namedWindow("Edges",WINDOW_AUTOSIZE);
  createTrackbar("Surf Min", "Edges", &area_min,
                  SURFMIN, BlobUpgrade);
  setTrackbarMax ("Surf Min", "Edges", SURFMIN);
  setTrackbarMin ("Surf Min", "Edges", 10);
  
  namedWindow("Polygones",WINDOW_AUTOSIZE); 
  
  
  for(;;) // Boucle d'Acquisition
  {
    cap >> src; // Obtenir une image de la camera        
    imshow( "Image", src );
  
    cvtColor(src, src_hsv, COLOR_BGR2HSV);
    inRangeDemo( 0, 0 );

    findContours (select_pts, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_NONE);
    edges.create (src.rows, src.cols, CV_8UC3);
    edges.setTo(0);
    polygones.create (src.rows, src.cols, CV_8UC3);
    polygones.setTo(0);
  
  
    BlobUpgrade( 0, 0 );

      
    if(waitKey(1) >= 0) break;
  }
  
  
  
  
  
  waitKey();

}

void Low_h (int, void* )
{
  if (low_h > high_h)
  {
    high_h = low_h;
    setTrackbarPos ("HUE high", "Image", high_h);
  }
}
void High_h (int, void* )
{
  if (high_h < low_h)
  {
    low_h = high_h;
    setTrackbarPos ("HUE low", "Image", low_h);
  }
}

void Low_s(int, void* )
{
  if (low_s > high_s)
  {
    high_s = low_s;
    setTrackbarPos ("SATURATION high", "Image", high_s);
  }
}
void High_s (int, void* )
{
  if (high_s < low_s)
  {
    low_s = high_s;
    setTrackbarPos ("SATURATION low", "Image", low_s);
  }
}

void Low_v (int, void* )
{
  if (low_v > high_v)
  {
    high_v = low_v;
    setTrackbarPos ("VALUE high", "Image", high_v);
  }
}
void High_v (int, void* )
{
  if (high_v < low_v)
  {
    low_v = high_v;
    setTrackbarPos ("VALUE low", "Image", low_v);
  }
}

/* --- Classification --- */
void inRangeDemo( int, void* )
{
    inRange(src_hsv,Scalar(low_h, low_s, low_v),Scalar(high_h, high_s, high_v),select_pts);
    morphologyEx(select_pts, select_pts, MORPH_OPEN, K);
    morphologyEx(select_pts, select_pts, MORPH_CLOSE, K);
    imshow("Seuillage", select_pts);
}

/* --- Blob --- */
void BlobUpgrade( int, void* )
{
  vector<Moments> mu(contours.size());
  vector<Point2f> mc(contours.size());
  vector<vector<Point> > app_poly(contours.size());
  vector<Rect> boundRect(contours.size());
  double area;
  
  edges.setTo(0);
  polygones.setTo(0);
  fprintf(stderr,"SurfMin = %d\n",area_min);
  for (unsigned int nb_ctr = 0; nb_ctr < contours.size(); nb_ctr++)
  {
    mu[nb_ctr] = moments(contours[nb_ctr], false);
    area = mu[nb_ctr].m00;
    if (area >= (double)area_min)
    {    
      mc[nb_ctr] = Point2f(mu[nb_ctr].m10/mu[nb_ctr].m00, mu[nb_ctr].m01/mu[nb_ctr].m00);
      Scalar colour(rand()&0xFF,rand()&0xFF,rand()&0xFF);
      Scalar colourCenter(0x00, 0x00, 0xFF);
      drawContours(edges, contours, nb_ctr, colour, FILLED, 8, hierarchy);
      circle(edges, mc[nb_ctr], 4, colourCenter, -1, 8, 0);
      
      /* --- Approximation Polygonale --- */
      approxPolyDP(Mat(contours[nb_ctr]),app_poly[nb_ctr], 3, true);
      Scalar colourPoly(rand()&0xFF,rand()&0xFF,rand()&0xFF);
      drawContours(polygones, app_poly, nb_ctr, colourPoly, 1, 8, 
         vector <Vec4i>(),0, Point());

      boundRect[nb_ctr] = boundingRect(app_poly[nb_ctr]);
      Scalar colourRect(0x00, 0xFF, 0xFF);
      rectangle(edges, boundRect[nb_ctr].tl(), boundRect[nb_ctr].br(), colourRect, 2);
    }
  }
  imshow("Edges", edges); 
  // imshow("Polygones", polygones);
}

