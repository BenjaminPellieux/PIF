#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
#include <unistd.h>
#include <cstdlib>
#include <ros/ros.h>


// struct Waste{

//     public:
//         cv::Rect rec;
//         int object_id;

//         static bool compareY(Waste &a, Waste &b) { return a.rec.y < b.rec.y; }

// } typedef Waste;



void change_origin(cv::Rect* closest_rect, int img_y, int mid_width ){
    closest_rect->y = img_y - closest_rect->y;
    closest_rect->x -= mid_width;
}

int main() {
    // Ouvrir le flux vidéo
    cv::VideoCapture cap("Video/Default_Video_Test.mp4");
    if(!cap.isOpened()) {
        std::cout << "Erreur: Impossible d'ouvrir la vidéo." << std::endl;
        return -1;
    }

    cv::Mat frame, image_blurred, hsv, mask_others, mask_majority_color, kernel;
    std::vector<std::vector<cv::Point>> contours;

    cv::Scalar lower_sat, upper_sat;
    int mid_height = 0;
    int mid_width = 0;
        
    int most_frequent_sat = 0;
    int sat_range = 30; // Vous pouvez ajuster cette plage selon vos besoins

    while(true) {
        // Lire une nouvelle frame
        bool bSuccess = cap.read(frame);
        if (!bSuccess) {
            std::cout << "Fin de la vidéo" << std::endl;
            break;
        }
        mid_height = frame.rows / 2;
        mid_width = frame.cols / 2;
        // Appliquer un filtre gaussien pour lisser l'image
        cv::GaussianBlur(frame, image_blurred, cv::Size(9, 9), 3, 3);

        // Convertir l'image en espace couleur HSV
        cv::cvtColor(image_blurred, hsv, cv::COLOR_BGR2HSV);

        // Calculer l'histogramme de la saturation (S)
        int histSize[] = { 256 };
        float s_ranges[] = { 0, 256 };
        const float* ranges[] = { s_ranges };
        int channels[] = { 1 }; // Utilisation du canal de saturation
        cv::Mat hist_sat;
        cv::calcHist(&hsv, 1, channels, cv::Mat(), hist_sat, 1, histSize, ranges, true, false);

        // Trouver la saturation la plus fréquente
        double maxVal = 0;
        cv::Point maxLoc;
        cv::minMaxLoc(hist_sat, 0, &maxVal, 0, &maxLoc);

        // La saturation la plus fréquente sera l'indice de la valeur maximale
        most_frequent_sat = maxLoc.y;

        // Déterminer les seuils pour isoler la couleur majoritaire basée sur la saturation
        lower_sat = cv::Scalar(0, std::max(most_frequent_sat - sat_range, 0), 20);
        upper_sat = cv::Scalar(180, std::min(most_frequent_sat + sat_range, 255), 255);

        // Créer un masque pour les couleurs qui ne sont pas dans la plage de la couleur majoritaire basée sur la saturation
        cv::inRange(hsv, lower_sat, upper_sat, mask_majority_color);
        mask_others = ~mask_majority_color;

        // Optionnel: appliquer des opérations morphologiques pour nettoyer le masque
        kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(15, 15));
        cv::morphologyEx(mask_others, mask_others, cv::MORPH_OPEN, kernel);
        cv::morphologyEx(mask_others, mask_others, cv::MORPH_CLOSE, kernel);

        // Trouver les contours dans le masque des autres couleurs
        cv::findContours(mask_others.clone(), contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
        int count = 1;
        cv::Rect max_y_rect;
        max_y_rect.y=0;

        for (size_t i = 0; i < contours.size(); i++) {
            double area = cv::contourArea(contours[i]);
            cv::Rect rect = cv::boundingRect(contours[i]);
            if ((rect.y >= mid_height) && ((area > 70) && (area < 1000))){ // Filtre basé sur la taille de l'objet
                std::cout<<"DEBUG count" <<count<<'\n';
                std::cout << "[LOG] Forme " << count << " area: " << area << "\n";
                cv::rectangle(frame, rect.tl(), rect.br(), cv::Scalar(0, 255, 0), 2);
                if (rect.y > max_y_rect.y){
                    max_y_rect = rect;
                }
                // Afficher le numéro et l'aire sur l'image
                std::string text = "#" + std::to_string(count) + " Area: " + std::to_string(static_cast<int>(area));
                cv::Point textOrg(rect.x, rect.y - 10); // Position du texte au-dessus du rectangle
                cv::putText(frame, text, textOrg, cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 250, 0), 1);
                cv::line(frame, {mid_width, 0}, {mid_width, frame.rows}, cv::Scalar(255, 0, 0));  // ligne vertical
                cv::line(frame, {0, mid_height}, {frame.cols, mid_height}, cv::Scalar(0, 0, 255)); // ligne orizonthale
                count++; // Incrémenter le compteur de formes
            }
        }
        change_origin(&max_y_rect, frame.rows, mid_width); 
        std::cout<<"Closest pos x: "<<max_y_rect.x<<" y: "<<max_y_rect.y<<"\n"; 
        // std::sort(Waste_list.begin(), Waste_list.end(), Waste::compareY);
        cv::imshow("Detection de l'element", frame);
        cv::imshow("Masque des autres couleurs", mask_others);

        // Attendre 30ms ou qu'une touche soit pressée
        if (cv::waitKey(30) >= 0) break;
    }

    // Libérer le flux vidéo et détruire toutes les fenêtres
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
