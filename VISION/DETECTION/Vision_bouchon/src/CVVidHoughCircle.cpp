/* -----------------------------------------------------*/
/* Fichier  : CVVidHoughCircle.cpp                      */
/* Role     : Acquisition Video d'Images                */
/*          : et Transformee de Hough Cercle            */          
/* Auteur   : Patrick Bonnin                            */
/*          : Formation Captronique 2017                */
/* -----------------------------------------------------*/
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;




/**  @function main */
int main( int argc, char** argv )
{
  Mat frame, frameBW;
  VideoCapture cap(0); // 0 pour la camera PC ou PICAM, 1 USB

  
  const int cannyThresholdInitialValue = 200;
  const int accumulatorThresholdInitialValue = 50;
  const int maxAccumulatorThreshold = 200;
  const int maxCannyThreshold = 255;
  int cannyThreshold = cannyThresholdInitialValue;
  int accumulatorThreshold = accumulatorThresholdInitialValue;
  int radius;

  if(!cap.isOpened())
  {
      return -1;
  }
  

  // Display Image
  namedWindow( "Image", WINDOW_AUTOSIZE );

  // cap.set(CAP_PROP_FRAME_WIDTH, 320);
  // cap.set(CAP_PROP_FRAME_HEIGHT, 240);
  createTrackbar("cannyThreshold", "Image", &cannyThreshold,maxCannyThreshold,NULL);
  createTrackbar("accumulatorThreshold", "Image", &accumulatorThreshold, maxAccumulatorThreshold, NULL);

  
  for(;;) // Boucle d'Acquisition
  {
    cap >> frame; // Obtenir une image de la camera  
    cvtColor(frame,frameBW,COLOR_RGB2GRAY);
    //Filtre gaussien
    GaussianBlur( frameBW, frameBW, Size(9, 9), 2, 2 );

    std::vector<Vec3f> circles;
    //Detecte les cercles
    cannyThreshold = std::max(cannyThreshold, 1);
    accumulatorThreshold = std::max(accumulatorThreshold, 1);
    HoughCircles( frameBW, circles, HOUGH_GRADIENT, 1, frameBW.rows/8, cannyThreshold, accumulatorThreshold, 0, 0 );

    for( size_t i = 0; i < circles.size(); i++ )
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        radius = cvRound(circles[i][2]);
        //Centre de cercle
        circle( frame, center, 3, Scalar(0,255,0), -1, 8, 0 );
        //Cercle
        circle( frame, center, radius, Scalar(0,0,255), 3, 8, 0 );
    }
    
    imshow( "Image", frame );
    if(waitKey(1) >= 0) break;
  }
  // Wait until user exits the program
  waitKey(0);
  return 0;
}

