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


void quick_sort(uint8_t* array, int32_t array_size){
    
    std::cout<<"[DEBUG] Quik sort\n Array Size: " << array_size << "\n";
    bool flag;
    uint8_t tmp;

    do{// sort all samples using quick short as the sample size is small
        flag = 0;
        for(uint16_t k = 0; k != array_size; k++){
            if (array[k] > array[k + 1]){
                tmp = array[k + 1];
                array[k + 1] = array[k];
                array[k] = tmp;
                flag = 1;
            }
        }
    }while(flag);


}

float median_cal(cv::Mat img){
    
    int32_t total_px = img.rows * img.cols;
    uint8_t* tab_value = (uint8_t*) malloc(sizeof(uint8_t) * total_px);
    
    for(uint16_t i = 0; i != img.rows; i++){
        for(uint16_t j = 0; j != img.cols; j++){
            tab_value[i*j+j] = (uint8_t) img.at<cv::Vec3b>(i,j)[0];
        }
    }
    
    quick_sort(tab_value, total_px);
    std::cout<<"[DEBUG] Quik sort DONE\n";
    
    uint8_t median = (int)tab_value[total_px / 2];
    free(tab_value);

    std::cout<<"[DEBUG] Median: "<< median <<"\n";
    return median;
    
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
    std::cout<<"[DEBUG] Sum: "<< sum <<" Totale px: "<< total_px <<" Mean value "<<sum / total_px<<"\n";
    return sum / (float)total_px;
}

void grey_img(cv::Mat img){

    cv::Mat dst_mean, dst_median, dst_main, graymat;
    cv::cvtColor(img, graymat, cv::COLOR_BGR2GRAY);
    cv::imshow("Grey Img", graymat);
    std::cout<<"[DEBUG] Grey IMG\n";

    // moyenne filtrage 
    int mean_grey =  (int) mean_cal(graymat);
    cv::threshold(graymat, dst_mean, mean_grey , 255, cv::THRESH_BINARY); 
    cv::imshow("Threshold img mean", dst_mean);
    std::cout<<"[DEBUG] Threshold img mean\n";

    // // median filtrage 
    // int meadian_grey = (int) median_cal(graymat);
    // cv::threshold(graymat, dst_median, meadian_grey , 255, cv::THRESH_BINARY); 
    // cv::imshow("Threshold img median", dst_median);
    // std::cout<<"[DEBUG] Threshold img median\n";

    // main filtrage
    cv::threshold(graymat, dst_main, 215 , 255, cv::THRESH_BINARY); 
    cv::imshow("Threshold img main", dst_main);
    std::cout<<"[DEBUG] Threshold img main\n";
    
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
    cv::imshow("Image lisse", img);
    // Attendre une touche pour fermer la fenêtre
    // cv::waitKey(0);

    grey_img(img);
    //etalonage(img);

    return EXIT_SUCCESS;
}
