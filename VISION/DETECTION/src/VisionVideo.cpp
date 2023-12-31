#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <cstdlib>

#define CAM_SOL_ANGLE = 60;


int main() {
    // Ouvrir le flux vidéo
    cv::VideoCapture cap("../Video/Default_Video_Test.mp4");
    if(!cap.isOpened()) {
        std::cout << "Erreur: Impossible d'ouvrir la vidéo." << std::endl;
        return -1;
    }


	
    cv::Mat frame, image_blurred, hsv, mask_others, mask_majority_color, kernel;
    std::vector<std::vector<cv::Point>> contours;
    cv::Scalar lower_hue, upper_hue;
    int most_frequent_hue = 0;
    int hue_range = 70;

    while(true) {
        // Lire une nouvelle frame
        bool bSuccess = cap.read(frame);
        if (!bSuccess) {
            std::cout << "Fin de la vidéo" << std::endl;
            break;
        }

        // Appliquer un filtre gaussien pour lisser l'image
        cv::GaussianBlur(frame, image_blurred, cv::Size(9, 9), 3, 3);

        // Convertir l'image en espace couleur HSV
        cv::cvtColor(image_blurred, hsv, cv::COLOR_BGR2HSV);

		// Calculer l'histogramme de la teinte (H)
		// Nombre de bins pour la teinte
		int histSize[] = { 180 };
		float h_ranges[] = { 0, 180 };
		const float* ranges[] = { h_ranges };
		int channels[] = { 0 };
		cv::Mat hist_hue;
		cv::calcHist(&hsv, 1, channels, cv::Mat(), hist_hue, 1, histSize, ranges, true, false);

			// Trouver la teinte la plus fréquente
		double minVal; // Si vous n'avez pas besoin du minimum, cette variable peut rester non utilisée.
		double maxVal = 0;
		cv::Point minLoc; // Utilisé pour stocker la position du minimum
		cv::Point maxLoc; // Utilisé pour stocker la position du maximum
			// Appel correct à minMaxLoc
		cv::minMaxLoc(hist_hue, 0, &maxVal, &minLoc, &maxLoc);

			// La teinte la plus fréquente sera l'indice de la valeur maximale
		most_frequent_hue = maxLoc.x; // ou maxLoc.x selon l'orientation de l'histogramme

			// Déterminer les seuils pour isoler la couleur majoritaire
		cv::Scalar lower_hue(most_frequent_hue - hue_range, 20, 20);
		cv::Scalar upper_hue(most_frequent_hue + hue_range, 255, 255);

		// Créer un masque pour les couleurs qui ne sont pas dans la plage de la couleur majoritaire
		cv::inRange(hsv, lower_hue, upper_hue, mask_majority_color);
		mask_others = ~mask_majority_color;
		// Appliquer le masque à l'image d'origine

		// Optionnel: appliquer des opérations morphologiques pour nettoyer le masque
		kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(15, 15));
		cv::morphologyEx(mask_others, mask_others, cv::MORPH_OPEN, kernel);
		cv::morphologyEx(mask_others, mask_others, cv::MORPH_CLOSE, kernel);
		// Trouver les contours dans le masque des autres couleurs
		
		std::vector<std::vector<cv::Point>> contours;
		cv::findContours(mask_others.clone(), contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
		int count = 1;

		for (size_t i = 0; i < contours.size(); i++) {
			double area = cv::contourArea(contours[i]);
			if ((area > 100) && (area < 1000)){ // Filtre basé sur la taille de l'objet
			cv::Rect rect = cv::boundingRect(contours[i]);
			std::cout << "[LOG] Forme " << count << " area: " << area << "\n";
			cv::rectangle(frame, rect.tl(), rect.br(), cv::Scalar(0, 255, 0), 2);

			// Afficher le numéro et l'aire sur l'image
			std::string text = "#" + std::to_string(count) + " Area: " + std::to_string(static_cast<int>(area));
			cv::Point textOrg(rect.x, rect.y - 10); // Position du texte au-dessus du rectangle
			cv::putText(frame, text, textOrg, cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 250, 0), 1);

			count++; // Incrémenter le compteur de formes
			}
		}
		cv::line(frame, cv::Point(0, frame.rows/2), cv::Point(frame.cols, frame.rows/2), cv::Scalar(250, 0, 0), 2);

		cv::imshow("Detection de l'element", frame);

		cv::imshow("Masque des autres couleurs", mask_others);
		//cv::imshow("Blurred image", );

		// Attendre 30ms ou qu'une touche soit pressée
		if (cv::waitKey(30) >= 0) break;
		}

    // Libérer le flux vidéo et détruire toutes les fenêtres
    cap.release();
    cv::destroyAllWindows();

    return 0;
}