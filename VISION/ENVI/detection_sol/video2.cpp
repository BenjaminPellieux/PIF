#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

// Structure pour les réglages HSV
struct HSVSettings {
    int low_h = 0, high_h = 179;
    int low_s = 0, high_s = 255;
    int low_v = 0, high_v = 122;  
    int threshold_white = 5;      // Ajout du seuil
};

// Instancier la structure de réglages HSV
HSVSettings hsvSettings;

int main() {
    // Initialiser la capture vidéo depuis la webcam
    VideoCapture cap;
    cap.open(0);  // 0 indique le premier périphérique de la webcam, changez-le si vous avez plusieurs caméras

    // Vérifier si la capture vidéo est ouverte
    if (!cap.isOpened()) {
        std::cerr << "Erreur lors de l'ouverture de la webcam." << std::endl;
        return -1;
    }

    // Création de la fenêtre de seuillage
    namedWindow("Seuillage", WINDOW_AUTOSIZE);

    // Paramètres HSV fixes
    hsvSettings.low_h = 0;
    hsvSettings.high_h = 179;
    hsvSettings.low_s = 0;
    hsvSettings.high_s = 255;
    hsvSettings.low_v = 0;
    hsvSettings.high_v = 122;  
    hsvSettings.threshold_white = 5;

    while (true) {
        // Capturer une image depuis la webcam
        Mat src;
        cap >> src;

        // Vérifier si l'image est correctement capturée
        if (src.empty()) {
            std::cerr << "Erreur lors de la capture de l'image depuis la webcam." << std::endl;
            break;
        }

        // Convertir l'image en espace de couleur HSV
        Mat hsv;
        cvtColor(src, hsv, COLOR_BGR2HSV);

        // Appliquer un masque en utilisant les valeurs HSV fixes
        Mat mask;
        inRange(hsv, Scalar(hsvSettings.low_h, hsvSettings.low_s, hsvSettings.low_v),
                Scalar(hsvSettings.high_h, hsvSettings.high_s, hsvSettings.high_v), mask);

        // Appliquer l'érosion pour éliminer le bruit
        Mat erosion;
        Mat element = getStructuringElement(MORPH_RECT, Size(10, 10));
        erode(mask, erosion, element);

        // Appliquer le flou gaussien
        Mat result;
        GaussianBlur(erosion, result, Size(5, 5), 4);

        // Déterminer si le véhicule peut avancer ou non
        Mat bottomRegion = result.rowRange(result.rows * 0.8, result.rows - 1);
        double whitePercentage = (countNonZero(bottomRegion) * 100.0) / bottomRegion.total();

        // Afficher le résultat
        imshow("Image", src);
        imshow("Seuillage", result);

        // Faire quelque chose en fonction du pourcentage de pixels blancs
        if (whitePercentage > hsvSettings.threshold_white) {
            std::cout << "Obstacle détecté, ne pas avancer." << std::endl;
            // Ajouter ici le code pour arrêter le véhicule
        } else {
            std::cout << "Aucun obstacle détecté, vous pouvez avancer." << std::endl;
            // Ajouter ici le code pour commander l'avancement du véhicule
        }

        // Attendre une petite période et vérifier si une touche est pressée
        if (waitKey(30) >= 0)
            break;
    }

    // Fermer la fenêtre et libérer la capture vidéo
    destroyAllWindows();
    cap.release();

    return 0;
}
