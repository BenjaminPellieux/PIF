#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    // Initialiser la capture vidéo depuis la webcam
    VideoCapture cap;
    cap.open(0);  // 0 indique le premier périphérique de la webcam, changez-le si vous avez plusieurs caméras

    // Vérifier si la capture vidéo est ouverte
    if (!cap.isOpened()) {
        std::cerr << "Erreur lors de l'ouverture de la webcam." << std::endl;
        return -1;
    }

    while (true) {
        // Capturer une image depuis la webcam
        Mat src;
        cap >> src;

        // Vérifier si l'image est correctement capturée
        if (src.empty()) {
            std::cerr << "Erreur lors de la capture de l'image depuis la webcam." << std::endl;
            break;
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

        // Attendre une petite période et vérifier si une touche est pressée
        if (waitKey(30) >= 0)
            break;
    }

    // Fermer la fenêtre et libérer la capture vidéo
    destroyAllWindows();
    cap.release();

    return 0;
}

