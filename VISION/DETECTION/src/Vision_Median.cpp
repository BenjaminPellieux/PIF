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

    // Convertir l'image en espace couleur HSV
    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

    // Séparer les canaux HSV
    std::vector<cv::Mat> hsv_channels;
    cv::split(hsv, hsv_channels);
    cv::Mat hue_channel = hsv_channels[0]; // canal H (teinte)

    // Aplatir le canal de teinte en un tableau 1D pour le tri et trouver la médiane
    cv::Mat hue_array;
    hue_channel.reshape(0, 1).copyTo(hue_array); // On reshape à une seule rangée
    
    // Trier le tableau pour obtenir la médiane
    std::vector<uchar> hue_vector;
    hue_array.copyTo(hue_vector); // Copier les éléments du Mat dans un vecteur
    std::nth_element(hue_vector.begin(), hue_vector.begin() + hue_vector.size() / 2, hue_vector.end());
    double median_val = hue_vector[hue_vector.size() / 2];

    // Appliquer le seuillage autour de la médiane
    cv::Mat mask;
    cv::inRange(hue_channel, static_cast<uchar>(median_val - 10), static_cast<uchar>(median_val + 10), mask); // 10 est un exemple de seuil arbitraire autour de la médiane

    // Inverser le masque si vous souhaitez éliminer les valeurs proches de la médiane
    cv::Mat mask_inverted = ~mask;

    // Appliquer le masque sur l'image
    cv::Mat result;
    image.copyTo(result, mask_inverted);

    std::cout<<"[INFO] Mean " << median_val[0] <<"\n";  
    // Afficher l'image résultante
    cv::imshow("base", image);
    cv::imshow("Result", result);
    cv::waitKey(0);
    return 0;
}

