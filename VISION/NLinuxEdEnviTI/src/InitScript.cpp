#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdint.h>


void calc_moyenne(){

    std::cout<<"Calcule de la moyenne\n";


}

void etalonage(cv::Mat img){

    /*
	
    uint16_t compt = 0;
    Vec3b* tab_pixel = (Vec3b*) malloc(Vec3b * total_px);
    for(uint16_t i; i != img.row; i++){
        for(uint16_t j; j != img.cols; j++){
            
            tab_pixel[compt] = foo.at<Vec3b>(i, j);
            
            compt += 1;
        }
    }
    */

    uint16_t total_px = img.rows * img.cols;
    cv::Mat hsv_img, dst;
    
    cv::cvtColor(img, hsv_img, cv::COLOR_BGR2HSV);
	std::cout<<"Total px: "<< total_px << "\n";
	std::cout<<"Etalonage img"<<"\n";

    //cv::imshow("HSV img", hsv_img);
    cv::threshold(img, dst, 0, 255, cv::THRESH_BINARY_INV); 
    cv::imshow("Threshold img", dst);

    cv::waitKey(0);
    //cv::imwrite("opencv-thresh-binary-inv.jpg", dst); 
    /*
    
        ret,thresh1 = cv.threshold(img,127,255,cv.THRESH_BINARY)
        ret,thresh2 = cv.threshold(img,127,255,cv.THRESH_BINARY_INV)
        ret,thresh3 = cv.threshold(img,127,255,cv.THRESH_TRUNC)
        ret,thresh4 = cv.threshold(img,127,255,cv.THRESH_TOZERO)
        ret,thresh5 = cv.threshold(img,127,255,cv.THRESH_TOZERO_INV)
    */

}


void grey_img(cv::Mat img){

    cv::Mat dst, graymat;
    cv::cvtColor(img, graymat, cv::COLOR_BGR2GRAY);
    

    cv::imshow("Grey Img", graymat);
    cv::threshold(graymat, dst, 220, 255, cv::THRESH_BINARY); 
    cv::imshow("Threshold img", dst);

    cv::waitKey(0);
}

int main(int argc, char** argv) {
    

    // Charger l'image depuis un fichier JPG IMREAD_GRAYSCALE
    cv::Mat image = cv::imread("../Image/vision_test_small.jpg");
    cv::Mat img;

    // Vérifier si l'image a été chargée avec succès
    if (!image.data){
        std::cout << "Erreur lors du chargement de l'image." << std::endl;
        return -1;
    }

    // Afficher l'image dans une fenêtre
    //cv::imshow("Image test", image);

    // Apply the Gaussian Blur filter. 
    // The Size object determines the size of the filter (the "range" of the blur)
    cv::GaussianBlur( image, img, cv::Size( 9, 9 ), 1.5);

    etalonage(img);

    cv::imshow("Image lisse", img);
    // Attendre une touche pour fermer la fenêtre
    // cv::waitKey(0);

    grey_img(img);
    //etalonage(img);

    return EXIT_SUCCESS;
}
