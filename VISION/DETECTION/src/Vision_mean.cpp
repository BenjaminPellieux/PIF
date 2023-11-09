#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

int main() {
    // Charger l'image
    cv::Mat image= cv::imread("../Image/vision_test_small.jpg");

    // Vérifier si l'image a été chargée correctement
    if(image.empty()) {
        std::cerr << "Erreur lors de la lecture de l'image." << std::endl;
        return -1;
    }    

    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

    // Séparer les canaux HSV
    std::vector<cv::Mat> hsv_channels;
    cv::split(hsv, hsv_channels);
    cv::Mat hue_channel = hsv_channels[0]; // canal H (teinte)

    // Calculer la moyenne des valeurs de teinte
    cv::Scalar mean_val = cv::mean(hue_channel);

    // Appliquer le seuillage autour de la moyenne
    cv::Mat mask;
    cv::inRange(hue_channel, mean_val[0] - 10, mean_val[0] + 10, mask); // 10 est un exemple de seuil arbitraire autour de la moyenne

    // Inverser le masque si vous souhaitez éliminer les valeurs proches de la moyenne
    cv::Mat mask_inverted = ~mask;

    // Appliquer le masque sur l'image
    cv::Mat result;
    image.copyTo(result, mask_inverted);
    std::cout<<"[INFO] Mean " << mean_val[0] <<"\n";  
    // Afficher l'image résultante
    cv::imshow("Base",image);
    cv::imshow("Result", result);
    cv::waitKey(0);
    return 0;
}
