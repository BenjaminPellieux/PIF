#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>

int main() {
    // Chargez une image depuis le disque
    cv::Mat image = cv::imread("../Image/detectionrouge.jpeg");

    if (image.empty()) {
        std::cout << "Impossible de charger l'image." << std::endl;
        return -1;
    }

    // Définissez le nombre de divisions horizontales et verticales
    int numHorizontalDivisions = 3; // Divisions horizontales
    int numVerticalDivisions = 3;   // Divisions verticales

    // Calculez les dimensions de chaque partie
    int partWidth = image.cols / numHorizontalDivisions;
    int partHeight = image.rows / numVerticalDivisions;

    // Parcourez les divisions horizontales et verticales
    for (int i = 0; i < numVerticalDivisions; i++) {
        for (int j = 0; j < numHorizontalDivisions; j++) {
            // Définissez la région rectangulaire pour chaque partie
            cv::Rect roi(j * partWidth, i * partHeight, partWidth, partHeight);

            // Extrayez la partie de l'image
            cv::Mat part = image(roi).clone();

            // Appliquez un seuillage sur chaque partie
            cv::cvtColor(part, part, cv::COLOR_BGR2GRAY); // Convertissez en niveau de gris si nécessaire
            cv::threshold(part, part, 128, 255, cv::THRESH_BINARY); // Appliquez un seuil (ajustez les valeurs selon vos besoins)

            // Créez un nom de fenêtre unique pour chaque partie
            std::string windowName = "Part " + std::to_string(i * numHorizontalDivisions + j);

            // Affichez chaque partie dans une fenêtre séparée
            cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
            cv::imshow(windowName, part);
        }
    }

    // Attendez que l'utilisateur appuie sur une touche (appuyez sur n'importe quelle touche pour quitter)
    cv::waitKey(0);

    return 0;
}
