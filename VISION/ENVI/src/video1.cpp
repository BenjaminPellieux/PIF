#include <iostream>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>

using namespace cv;

// Structure pour les réglages HSV
struct HSVSettings {
    int low_h = 0, high_h = 179;
    int low_s = 0, high_s = 255;
    int low_v = 0, high_v = 255;
    int threshold_white = 5;  // Ajout du seuil
};

// Instancier la structure de réglages HSV
HSVSettings hsvSettings;

// Fonctions de rappel pour ajuster les plages de valeurs HSV
//teinte = HUE
void Low_h(int, void*) {
    if (hsvSettings.low_h > hsvSettings.high_h) {
        hsvSettings.high_h = hsvSettings.low_h;
        setTrackbarPos("HUE high", "Reglage", hsvSettings.high_h);
    }
}

void High_h(int, void*) {
    if (hsvSettings.high_h < hsvSettings.low_h) {
        hsvSettings.low_h = hsvSettings.high_h;
        setTrackbarPos("HUE low", "Reglage", hsvSettings.low_h);
    }
}
//saturation = intensité de couleur
void Low_s(int, void*) {
    if (hsvSettings.low_s > hsvSettings.high_s) {
        hsvSettings.high_s = hsvSettings.low_s;
        setTrackbarPos("SATURATION high", "Reglage", hsvSettings.high_s);
    }
}

void High_s(int, void*) {
    if (hsvSettings.high_s < hsvSettings.low_s) {
        hsvSettings.low_s = hsvSettings.high_s;
        setTrackbarPos("SATURATION low", "Reglage", hsvSettings.low_s);
    }
}
// value = luminausité
void Low_v(int, void*) {
    if (hsvSettings.low_v > hsvSettings.high_v) {
        hsvSettings.high_v = hsvSettings.low_v;
        setTrackbarPos("VALUE high", "Reglage", hsvSettings.high_v);
    }
}

void High_v(int, void*) {
    if (hsvSettings.high_v < hsvSettings.low_v) {
        hsvSettings.low_v = hsvSettings.high_v;
        setTrackbarPos("VALUE low", "Reglage", hsvSettings.low_v);
    }
}

// Fonction de rappel pour ajuster la valeur de "Threshold White"
void ThresholdWhite(int, void*) {
    // Ajoutez ici le code pour obtenir la valeur de la trackbar
    hsvSettings.threshold_white = getTrackbarPos("Threshold White", "Reglage");
}

// Fonction pour ajuster la luminosité de l'image
void adjustBrightness(Mat& image, double alpha, int beta) {
    image.convertTo(image, -1, alpha, beta);
}

int main() {

    //ROS
    
    // Initialiser la capture vidéo depuis la webcam
    VideoCapture cap;
    cap.open(0);  // 0 indique le premier périphérique de la webcam, changez-le si vous avez plusieurs caméras

    // Vérifier si la capture vidéo est ouverte
    if (!cap.isOpened()) {
        std::cerr << "Erreur lors de l'ouverture de la webcam." << std::endl;
        return -1;
    }

    // Création des fenêtres
    namedWindow("Image", WINDOW_AUTOSIZE);
    namedWindow("Reglage", WINDOW_AUTOSIZE);
    namedWindow("Seuillage", WINDOW_AUTOSIZE);

    // Création des trackbars pour les réglages des plages de couleurs
    createTrackbar("HUE low", "Reglage", &hsvSettings.low_h, 179, Low_h);
    createTrackbar("HUE high", "Reglage", &hsvSettings.high_h, 179, High_h);

    createTrackbar("SATURATION low", "Reglage", &hsvSettings.low_s, 255, Low_s);
    createTrackbar("SATURATION high", "Reglage", &hsvSettings.high_s, 255, High_s);

    createTrackbar("VALUE low", "Reglage", &hsvSettings.low_v, 255, Low_v);
    createTrackbar("VALUE high", "Reglage", &hsvSettings.high_v, 255, High_v);

    createTrackbar("Threshold White", "Reglage", &hsvSettings.threshold_white, 100, ThresholdWhite);

    // Paramètres de luminosité
    double alpha = 1.5;  // ajustez ce paramètre pour la luminosité (1 = pas de changement)
    int beta = 20;       // ajustez ce paramètre pour la luminosité (0 = pas de changement)

    while (true) {
        // Capturer une image depuis la webcam
        Mat src;
        cap >> src;

        // Vérifier si l'image est correctement capturée
        if (src.empty()) {
            std::cerr << "Erreur lors de la capture de l'image depuis la webcam." << std::endl;
            break;
        }

        // Ajuster la luminosité de l'image
        adjustBrightness(src, alpha, beta);

        // Convertir l'image en espace de couleur HSV
        Mat hsv;
        cvtColor(src, hsv, COLOR_BGR2HSV);

        // Appliquer un masque en utilisant les valeurs HSV ajustées
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
        Mat bottomRegion = result.rowRange(result.rows * 0.6, result.rows - 1);
        double whitePercentage = (countNonZero(bottomRegion) * 100.0) / bottomRegion.total();

        // Afficher le résultat
        imshow("Image", src);
        imshow("Seuillage", result);

        // Faire quelque chose en fonction du pourcentage de pixels blancs
        if (whitePercentage > hsvSettings.threshold_white) {
            std::cout << "Obstacle détecté, ne pas avancer." << std::endl;
            // Ajouter ici le code pour arrêter le véhicule
        } else {
            std::cout << "Aucun obstacle détecté, avancer." << std::endl;
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
