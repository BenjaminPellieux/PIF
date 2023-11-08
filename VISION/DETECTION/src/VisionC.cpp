#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

int main() {
    // Charger l'image
    cv::Mat image = cv::imread("../Image/vision_test_small.jpg");
    if(image.empty()) {
        std::cout << "Could not read the image" << std::endl;
        return 1;
    }

    // Appliquer un filtre gaussien pour lisser l'image
    cv::Mat image_blurred;
    cv::GaussianBlur(image, image_blurred, cv::Size(9, 9), 3, 3);

    // Convertir l'image en espace couleur HSV
    cv::Mat hsv;
    cv::cvtColor(image_blurred, hsv, cv::COLOR_BGR2HSV);

    // Calculer l'histogramme de la teinte (H)
    int h_bins = 180; // Nombre de bins pour la teinte
    int histSize[] = { h_bins };
    float h_ranges[] = { 0, 180 };
    const float* ranges[] = { h_ranges };
    int channels[] = { 0 };
    cv::Mat hist_hue;
    cv::calcHist(&hsv, 1, channels, cv::Mat(), hist_hue, 1, histSize, ranges, true, false);

    // Trouver la teinte la plus fréquente
    double minVal; // Si vous n'avez pas besoin du minimum, cette variable peut rester non utilisée.
    double maxVal = 0;
    cv::Point minLoc; // Utilisé pour stocker la position du minimum
    cv::Point maxLoc; // Utilisé pour stocker la position du maximum
    int most_frequent_hue = 0;
	// Appel correct à minMaxLoc
    cv::minMaxLoc(hist_hue, &minVal, &maxVal, &minLoc, &maxLoc);

	// La teinte la plus fréquente sera l'indice de la valeur maximale
    most_frequent_hue = maxLoc.y; // ou maxLoc.x selon l'orientation de l'histogramme

    // Déterminer les seuils pour isoler la couleur majoritaire
    int hue_range = 70;  // à ajuster selon vos besoins
    cv::Scalar lower_hue(most_frequent_hue - hue_range, 20, 20);
    cv::Scalar upper_hue(most_frequent_hue + hue_range, 255, 255);
    std::cout << "[DEBUG] lower_hue=" << lower_hue << std::endl;
    std::cout << "[DEBUG] upper_hue=" << upper_hue << std::endl;

    // Créer un masque pour les couleurs qui ne sont pas dans la plage de la couleur majoritaire
    cv::Mat mask_majority_color, mask_others;
    cv::inRange(hsv, lower_hue, upper_hue, mask_majority_color);
    mask_others = ~mask_majority_color;

    // Optionnel: appliquer des opérations morphologiques pour nettoyer le masque
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::morphologyEx(mask_others, mask_others, cv::MORPH_OPEN, kernel);
    cv::morphologyEx(mask_others, mask_others, cv::MORPH_CLOSE, kernel);

    // Trouver les contours dans le masque des autres couleurs
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask_others.clone(), contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    // Filtrer et dessiner les contours
    for (size_t i = 0; i < contours.size(); i++) {
        double area = cv::contourArea(contours[i]);
        if (area > 100) { // Filtre basé sur la taille de l'objet
            cv::Rect rect = cv::boundingRect(contours[i]);
            cv::rectangle(image, rect.tl(), rect.br(), cv::Scalar(0, 255, 0), 2);
        }
    }

    // Afficher l'image originale avec les détections
    cv::imshow("Detection de l'element", image);

    // Afficher le masque des autres couleurs
    cv::imshow("Masque des autres couleurs", mask_others);
    cv::imshow("Blurred Image", image_blurred);

    // Attendre qu'une touche soit pressée avant de fermer les fenêtres d'image
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}

