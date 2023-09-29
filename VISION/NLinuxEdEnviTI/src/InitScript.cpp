#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdint.h>


void calc_moyenne(){

    std::cout<<"Calcule de la moyenne\n";

}

void etalonage(cv::Mat img){
    cv::Mat hsv_img, dst;    
    cv::cvtColor(img, hsv_img, cv::COLOR_BGR2HSV);
    //cv::imshow("HSV img", hsv_img);
    cv::threshold(img, dst, 0, 255, cv::THRESH_BINARY_INV); 
    cv::imshow("Threshold img", dst);

    //cv::imwrite("opencv-thresh-binary-inv.jpg", dst); 
    /*
    
        ret,thresh1 = cv.threshold(img,127,255,cv.THRESH_BINARY)
        ret,thresh2 = cv.threshold(img,127,255,cv.THRESH_BINARY_INV)
        ret,thresh3 = cv.threshold(img,127,255,cv.THRESH_TRUNC)
        ret,thresh4 = cv.threshold(img,127,255,cv.THRESH_TOZERO)
        ret,thresh5 = cv.threshold(img,127,255,cv.THRESH_TOZERO_INV)
    */

}


void quick_short(uint8_t* tab_value){

    std::cout<<"[TODO] : Trie rapide\n";

}

float median_cal(cv::Mat img){
    
    int total_px = img.rows * img.cols;
    uint8_t* tab_value = (uint8_t*) malloc(sizeof(uint8_t) * total_px);
    
    for(uint16_t i = 0; i != img.rows; i++){
        for(uint16_t j = 0; j != img.cols; j++){
            tab_value[i*j+j] = (uint8_t) img.at<cv::Vec3b>(i,j)[0];
        }
    }
    // std::cout<<"Sum: "<< sum <<" Totale px: "<< total_px <<" Mean value "<<sum / total_px<<"\n";
    quick_short(tab_value);
    return tab_value[total_px / 2];
    
}

float mean_cal(cv::Mat img){
    int sum = 0;
    int total_px = img.rows * img.cols;

    for(uint16_t i = 0; i != img.rows; i++){
        for(uint16_t j = 0; j != img.cols; j++){
            // std::cout<<"Pixel n °"<<i * j + j<<" Value: "<<(int) img.at<cv::Vec3b>(i,j)[0] <<"\n";
            sum += (uint8_t) img.at<cv::Vec3b>(i,j)[0];
        }
    
    }
    std::cout<<"Sum: "<< sum <<" Totale px: "<< total_px <<" Mean value "<<sum / total_px<<"\n";
    return sum / (float)total_px;
}

void grey_img(cv::Mat img){

    cv::Mat dst, graymat;
    cv::cvtColor(img, graymat, cv::COLOR_BGR2GRAY);
    int mean_grey =  (int) mean_cal(graymat);
    int meadian_grey = 0;
    cv::imshow("Grey Img", graymat);
    cv::threshold(graymat, dst, 215 , 255, cv::THRESH_BINARY); 
    cv::imshow("Threshold img", dst);

    cv::waitKey(0);
    // cv::imwrite("../Imres/test_threshold    ")
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
    cv::GaussianBlur( image, img, cv::Size( 9, 9 ), 2);

    etalonage(img);

    cv::imshow("Image lisse", img);
    // Attendre une touche pour fermer la fenêtre
    // cv::waitKey(0);

    grey_img(img);
    //etalonage(img);

    return EXIT_SUCCESS;
}
