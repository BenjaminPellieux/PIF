#include <iostream>
#include "std_msgs/Bool.h"
#include <opencv2/opencv.hpp>
#include <ros/ros.h>


// Structure pour les réglages HSV
typedef struct{
    int low_h = 0, high_h = 179;
    int low_s = 0, high_s = 255;
    int low_v = 0, high_v = 255;
    int threshold_white = 5;  // Ajout du seuil
}HSVSettings;

// Fonction pour ajuster la luminosité de l'image
void adjustBrightness(cv::Mat& image, double alpha, int beta) {
    image.convertTo(image, -1, alpha, beta);
}

int main(int argc, char** argv) {

    //ROS
    HSVSettings hsvSettings;
    ros::init(argc, argv, "environnement");
    ros::NodeHandle nh;
    ros::Publisher pub_obstacle = nh.advertise<std_msgs::Bool>("/Obstacle", 10);
    std_msgs::Bool msg;
    cv::VideoCapture cap("/home/ros/PIF/VISION/DETECTION/Video/Default_Video_Test.mp4");
     // 0 indique le premier périphérique de la webcam, changez-le si vous avez plusieurs caméras

    // Vérifier si la capture vidéo est ouverte
    if (!cap.isOpened()) {
        std::cerr << "Erreur lors de l'ouverture de la webcam." << std::endl;
        return -1;
    }
    // Paramètres de luminosité
    double alpha = 1.5;  // ajustez ce paramètre pour la luminosité (1 = pas de changement)
    int beta = 20;       // ajustez ce paramètre pour la luminosité (0 = pas de changement)

    while (ros::ok()) {
        // Capturer une image depuis la webcam
        cv::Mat src;
        cap >> src;

        // Vérifier si l'image est correctement capturée
        if (src.empty()) {
            std::cerr << "Erreur lors de la capture de l'image depuis la webcam." << std::endl;
            break;
        }

        // Ajuster la luminosité de l'image
        adjustBrightness(src, alpha, beta);

        // Convertir l'image en espace de couleur HSV
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
        cv::Mat bottomRegion = result.rowRange(result.rows * 0.6, result.rows - 1);
        double whitePercentage = (countNonZero(bottomRegion) * 100.0) / bottomRegion.total();

        msg.data = whitePercentage > hsvSettings.threshold_white; 
        pub_obstacle.publish(msg);
        ros::spinOnce();

        // Attendre une petite période et vérifier si une touche est pressée
        if (cv::waitKey(30) >= 0)
            break;
    }

    // Fermer la fenêtre et libérer la capture vidéo
    cv::destroyAllWindows();
    cap.release();

    return 0;
}
