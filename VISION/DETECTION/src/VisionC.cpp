#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Charger l'image
    cv::Mat img = cv::imread("../Image/vision_test_small.jpg");

    // Vérifier si l'image a été chargée correctement
    if(img.empty()) {
        std::cerr << "Erreur lors de la lecture de l'image." << std::endl;
        return -1;
    }

    // Convertir en niveaux de gris
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    // Appliquer un flou gaussien
    cv::GaussianBlur(gray, gray, cv::Size(5, 5), 0);

    // Seuillage adaptatif ou binaire
    cv::Mat thresh;
    cv::adaptiveThreshold(gray, thresh, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY_INV, 11, 2);

    // Opérations morphologiques
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::morphologyEx(thresh, thresh, cv::MORPH_CLOSE, kernel);

    // Trouver les contours
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(thresh, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // Filtrer les contours ici si nécessaire...

    // Dessiner les contours sur l'image originale
    cv::Mat result;
    img.copyTo(result);
    cv::drawContours(result, contours, -1, cv::Scalar(0, 255, 0), 2);

    // Afficher l'image résultante
    cv::imshow("Résultat", result);
    cv::waitKey(0);

    return 0;
}

