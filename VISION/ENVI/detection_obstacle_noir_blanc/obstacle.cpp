#include <opencv2/opencv.hpp>

int main() {
    // Initialiser la capture vidéo depuis la webcam
    cv::VideoCapture cap(0);

    // Vérifier si la capture vidéo est ouverte
    if (!cap.isOpened()) {
        std::cout << "Erreur lors de l'ouverture de la webcam." << std::endl;
        return -1;
    }

    // Définir la valeur de seuil
    int seuil = 100;

    // Définir la valeur de seuil_obstacle
    double seuil_obstacle = 10.0;  // Ajustez selon vos besoins

    while (true) {
        // Capturer une image depuis la webcam
        cv::Mat src;
        cap >> src;

        // Vérifier si l'image est correctement capturée
        if (src.empty()) {
            std::cout << "Erreur lors de la capture de l'image depuis la webcam." << std::endl;
            break;
        }

        // Convertir l'image en niveaux de gris
        cv::Mat gray;
        cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

        // Seuillage
        cv::Mat binary_image;
        cv::threshold(gray, binary_image, seuil, 255, cv::THRESH_BINARY);

        // Analyse de l'image seuillée   
        int half_height = binary_image.rows / 2;
        cv::Mat bottom_half = binary_image.rowRange(half_height, binary_image.rows);

        // Calculer le pourcentage de pixels noirs dans la moitié inférieure de l'image
        double black_percentage = (cv::countNonZero(bottom_half == 0) * 100.0) / bottom_half.total();

        // Prendre une décision
        if (black_percentage > seuil_obstacle) {
            std::cout << "Obstacle détecté, ne pas avancer." << std::endl;
            // Ajoutez ici le code pour arrêter le véhicule
        } else {
            std::cout << "Aucun obstacle détecté dans la moitié inférieure, vous pouvez avancer." << std::endl;
            // Ajoutez ici le code pour commander l'avancement du véhicule
        }

        // Afficher l'image seuillée
        cv::imshow("Resultat", binary_image);

        // Attendre une petite période et vérifier si une touche est pressée
        if (cv::waitKey(30) >= 0) {
            break;
        }
    }

    // Fermer la fenêtre et libérer la capture vidéo
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
