#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

// Réglages HSV
struct HSVSettings {
    int low_h = 0, high_h = 179;
    int low_s = 0, high_s = 255;
    int low_v = 0, high_v = 122;
    int threshold_white = 5;  // Ajout du seuil
};

// Réglages HSV avec les valeurs fixées
HSVSettings hsvSettings;

// Fonction pour ajuster la luminosité de l'image
void adjustBrightness(Mat& image, double alpha, int beta) {
    image.convertTo(image, -1, alpha, beta);
}

int main() {
    // Initialiser la capture vidéo depuis la webcam
    VideoCapture cap;
    cap.open(0);  // 0 indique le premier périphérique de la webcam
    
    // Vérifier si la capture vidéo est ouverte
    if (!cap.isOpened()) {
        std::cerr << "Erreur lors de l'ouverture de la webcam." << std::endl;
        return -1;
    }

    // Création des fenêtres
    namedWindow("Image", WINDOW_AUTOSIZE);
    namedWindow("Seuillage", WINDOW_AUTOSIZE);

    // Paramètres de luminosité
    double alpha = 1.5;  
    int beta = 20;       

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
        Mat bottomRegion = result.rowRange(result.rows * 0.7, result.rows - 1);
        
        bool resultTab[result.rows-1];
        
        
        for (int i = 0; i<result.cols-1; i++){
        
        	Mat column = bottomRegion.colRange(i, i+1); //le 1er argument est inclusif, le second est exclusif, le résultat contient donc 1 colonne
        	double columnWhitePercentage = (countNonZero(column) * 100.0) / column.total();
        	column.release();
        	if (columnWhitePercentage > hsvSettings.threshold_white){ //trop de blanc dans la colonne
        		resultTab[i] = false;
        		std::cout << "false\n";
        	}
        	else {
        		resultTab[i] = true;
        		std::cout << "true\n";
        	}
        	
        }
        
	
	
        // Afficher le résultat
        //imshow("Image", src);
        //imshow("Seuillage", result);

        // Attendre une petite période et vérifier si une touche est pressée
        if (waitKey(30) >= 0)
            break;
    }

    // Fermer la fenêtre et libérer la capture vidéo
    destroyAllWindows();
    cap.release();

    return 0;
}
