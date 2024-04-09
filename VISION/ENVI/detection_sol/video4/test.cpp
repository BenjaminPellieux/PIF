#include <iostream>
//#include "std_msgs/UInt16.h"
#include <opencv2/opencv.hpp>
struct HSVSettings {
    int low_h = 0, high_h = 179;
    int low_s = 0, high_s = 255;
    int low_v = 0, high_v = 122;
    int threshold_white = 5;
};

HSVSettings hsvSettings;

void adjustBrightness(cv::Mat& image, double alpha, int beta) {
    image.convertTo(image, -1, alpha, beta);
}

int main() {
    // Initialiser la capture vidéo depuis un fichier
    cv::VideoCapture cap;
    cap.open("/home/ros/PIF/PIF/VISION/DETECTION/Video/test.mp4");

    // Vérifier si la capture vidéo est ouverte
    if (!cap.isOpened()) {
        std::cerr << "Erreur lors de l'ouverture de la vidéo." << std::endl;
        return -1;
    }

    // Création des fenêtres
    cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Seuillage", cv::WINDOW_AUTOSIZE);
    // Paramètres de luminosité
    double alpha = 0.65;  
    int beta = 20;       

    while (true) {
        // Capturer une frame depuis la vidéo
        cv::Mat src;
        cap >> src;

        // Vérifier si la frame est correctement capturée
        if (src.empty()) {
            std::cerr << "Erreur lors de la capture de la frame depuis la vidéo." << std::endl;
            break;
        }

	
        
	
        // Ajuster la luminosité de la frame
        adjustBrightness(src, alpha, beta);


        // Ajuster automatiquement les paramètres de luminosité
        
        // Convertir la frame en espace de couleur HSV
        cv::Mat hsv;
        cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);
        

        // Appliquer un masque en utilisant les valeurs HSV ajustées
        cv::Mat mask;
        cv::inRange(hsv, cv::Scalar(hsvSettings.low_h, hsvSettings.low_s, hsvSettings.low_v),
                    cv::Scalar(hsvSettings.high_h, hsvSettings.high_s, hsvSettings.high_v), mask);

        // Appliquer l'érosion pour éliminer le bruit
        cv::Mat erosion;
        cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(10, 10));
        cv::erode(mask, erosion, element);

        // Appliquer le flou gaussien
        cv::Mat result;
        cv::GaussianBlur(erosion, result, cv::Size(5, 5), 4);

        // Déterminer si le véhicule peut avancer ou non
        cv::Mat bottomRegion = result.rowRange(result.rows * 0.70, result.rows - 1);
        //cv::threshold(bottomRegion, bottomRegion, 0, 255, cv::THRESH_BINARY);

        
        
        
        double whitePercentage = (cv::countNonZero(bottomRegion) * 100.0) / bottomRegion.total();

        // Diviser la frame en deux parties gauche et droite
        //cv::Mat leftRegion = result.colRange(0, result.cols * 0.1);
        
        //cv::Mat rightRegion = result.colRange(result.cols * 0.5, result.cols - 1);

        // Calculer le pourcentage de pixels blancs dans chaque partie
        //double leftWhitePercentage = (cv::countNonZero(leftRegion) * 100.0) / leftRegion.total();
        //double rightWhitePercentage = (cv::countNonZero(rightRegion) * 100.0) / rightRegion.total();
	
        //std_msg::UInt16 result;
        //result.data = 0;
        uint16_t r = 0;
        for(int i = 0; i < 16; i++ ){
                cv::Mat Region = result.colRange(result.cols * (i/16.0), result.cols * ((i+1.0)/16.0));
                //printf("r : %f, %f\n", result.cols * (i/16.0), result.cols * ((i+1.0)/16.0));
                double RegionWhitePercentage = (cv::countNonZero(Region) * 100.0) / Region.total();
                //std::cout << RegionWhitePercentage << std::endl;
                
                if(RegionWhitePercentage <= hsvSettings.threshold_white){ //on peut avancer
                        //result.data = result.data | (0x0001 << i);
                        r = r | (0x0001 << i);
                        
                }
        }
        
        //std::cout << r << std::endl;
        printf("r : %x\n",r);
        /*uint16_t var =0x0000;
        var = var | (0x0001 << i)
        //var => 0x0001
        var = var | 0x0010
        //var => 0x0011 */
	
        // Afficher le résultat
        cv::imshow("Image", src);
        cv::imshow("Seuillage", result);

        // Faire avancer ou non le véhicule PIF en fonction du pourcentage de pixels blancs
        /*if (whitePercentage > hsvSettings.threshold_white) {
        		if (leftWhitePercentage > hsvSettings.threshold_white) {
            	std::cout << "Obstacle détecté à gauche.";
        		}
        		
        		if (rightWhitePercentage > hsvSettings.threshold_white) {
           	std::cout << "Obstacle détecté à droite.";
            	
        		}
        		std::cout << std::endl;
        } else {
            std::cout << "Aucun obstacle détecté, avancer." << std::endl;
            // Ajouter ici le code pour commander l'avancement du véhicule
        }*/


        // Attendre une petite période et vérifier si une touche est pressée
        if (cv::waitKey(30) >= 0)
            break;
    }

    // Fermer la fenêtre et libérer la capture vidéo
    cv::destroyAllWindows();
    cap.release();

    return 0;
}
