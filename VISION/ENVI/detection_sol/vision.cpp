#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    // Charger l'image depuis un fichier
    Mat src = imread("route.jpg");

    // Vérifier si l'image est correctement chargée
    if (src.empty()) {
        std::cerr << "Erreur lors du chargement de l'image." << std::endl;
        return -1;
    }

    // Convertir l'image en niveaux de gris
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);

    // Appliquer Canny Edge Detector
    Mat edges;
    Canny(gray, edges, 80, 255);

    // Remplir les zones non-obstacle avec du blanc
    Mat dst = Mat::zeros(src.size(), CV_8UC1);
    for (int i = 0; i < edges.cols; ++i) {
        int j = edges.rows - 1;
        for (j = edges.rows - 1; j > 0; --j) {
            if (edges.at<uchar>(j, i) > 0) {
                break;
            }
        }
        dst(Range(j, dst.rows - 1), Range(i, i + 1)) = 255;
    }

    // Appliquer l'érosion pour éliminer le bruit
    Mat erosion;
    Mat element = getStructuringElement(MORPH_RECT, Size(10, 10));
    erode(dst, erosion, element);

    // Appliquer le flou gaussien
    Mat result;
    GaussianBlur(erosion, result, Size(5, 5), 4);

    // Déterminer si le véhicule peut avancer ou non
    Mat bottomRegion = result.rowRange(result.rows * 0.8, result.rows - 1);
    double whitePercentage = (countNonZero(bottomRegion) * 100.0) / bottomRegion.total();

    // Définir un seuil pour considérer la présence d'obstacles
    double thresholdWhite = 5.0;

    // Afficher le résultat
    namedWindow("Result", WINDOW_NORMAL);
    imshow("Result", result);
    
    // Faire quelque chose en fonction du pourcentage de pixels blancs
    if (whitePercentage > thresholdWhite) {
        std::cout << "Obstacle détecté, ne pas avancer." << std::endl;
        // Ajouter ici le code pour arrêter le véhicule
    } else {
        std::cout << "Aucun obstacle détecté, vous pouvez avancer." << std::endl;
        // Ajouter ici le code pour commander l'avancement du véhicule
    }

    // Attendre une touche
    waitKey(0);
    destroyAllWindows();

    return 0;
}
