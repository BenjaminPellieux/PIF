#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstdint>

#define SURFMIN 2500
#define SETTINGS_FILE "hsv_settings.xml"

using namespace cv;
using namespace std;

// Structure pour les réglages HSV
struct HsvSettings {
    int8_t low_h, high_h;
    int8_t low_s, high_s;
    int8_t low_v, high_v;
};

HsvSettings hsvSettings;

Mat src, src_hsv, select_pts;
Mat K; // Element structurant (Kernel) pour les opérations morphologiques

bool bouchonFound = false;

// Déclaration des fonctions de rappel
void inRangeDemo(int, void*);
void Low_h(int, void*);
void High_h(int, void*);

void Low_s(int, void*);
void High_s(int, void*);

void Low_v(int, void*);
void High_v(int, void*);

/* --- Blobs --- */
int area_min = 100;
vector<vector<Point>> contours;
vector<Vec4i> hierarchy;

Mat edges;
Mat polygones;

void BlobUpgrade(int, void*);

void saveSettings();
void loadSettings();

int main(int argc, char** argv) {
    // Charger les réglages depuis le fichier
    loadSettings();

    // Initialisation de la capture vidéo
    VideoCapture cap(0); // 0 pour une seule caméra
    if (!cap.isOpened()) {
        return -1;
    }

    // Création des fenêtres
    namedWindow("Image", WINDOW_AUTOSIZE);
    namedWindow("Reglage", WINDOW_AUTOSIZE);
    namedWindow("Seuillage", WINDOW_AUTOSIZE);

    // Création des trackbars pour les réglages des plages de couleurs
    createTrackbar("HUE low", "Reglage", reinterpret_cast<int*>(&hsvSettings.low_h), 179, Low_h);
    createTrackbar("HUE high", "Reglage", reinterpret_cast<int*>(&hsvSettings.high_h), 179, High_h);

    createTrackbar("SATURATION low", "Reglage", reinterpret_cast<int*>(&hsvSettings.low_s), 255, Low_s);
    createTrackbar("SATURATION high", "Reglage", reinterpret_cast<int*>(&hsvSettings.high_s), 255, High_s);

    createTrackbar("VALUE low", "Reglage", reinterpret_cast<int*>(&hsvSettings.low_v), 255, Low_v);
    createTrackbar("VALUE high", "Reglage", reinterpret_cast<int*>(&hsvSettings.high_v), 255, High_v);

    // Initialisation de l'élément structurant (Kernel) pour les opérations morphologiques
    K = getStructuringElement(MORPH_RECT, Size(3, 3));

    // Création des fenêtres pour l'affichage des contours et polygones
    namedWindow("Edges", WINDOW_AUTOSIZE);
    createTrackbar("Surf Min", "Edges", &area_min, SURFMIN, BlobUpgrade);
    setTrackbarMax("Surf Min", "Edges", SURFMIN);
    setTrackbarMin("Surf Min", "Edges", 10);

    // Boucle principale de capture vidéo
    for (;;) {
        // Capture d'une image depuis la caméra
        cap >> src;

        // Affichage de l'image originale
        imshow("Image", src);

        // Conversion de l'image en espace de couleur HSV
        cvtColor(src, src_hsv, COLOR_BGR2HSV);

        // Application de la segmentation (seuillage) en fonction des réglages
        inRangeDemo(0, 0);

        // Recherche des contours dans l'image seuillée
        findContours(select_pts, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_NONE);

        // Création des images de bords et polygones
        edges.create(src.rows, src.cols, CV_8UC3);
        edges.setTo(0);
        polygones.create(src.rows, src.cols, CV_8UC3);
        polygones.setTo(0);

        // Mise à jour de l'affichage des contours et polygones
        BlobUpgrade(0, 0);

        // Sortie de la boucle si une touche est pressée
        if (waitKey(1) >= 0)
            break;
    }

    // Sauvegarder les réglages avant de quitter
    saveSettings();

    waitKey();

    return 0;
}

// Fonction de rappel pour ajuster la valeur de "HUE low" en fonction de "HUE high"
void Low_h(int, void*) {
    if (hsvSettings.low_h > hsvSettings.high_h) {
        hsvSettings.high_h = hsvSettings.low_h;
        setTrackbarPos("HUE high", "Reglage", hsvSettings.high_h);
    }
}

// Fonction de rappel pour ajuster la valeur de "HUE high" en fonction de "HUE low"
void High_h(int, void*) {
    if (hsvSettings.high_h < hsvSettings.low_h) {
        hsvSettings.low_h = hsvSettings.high_h;
        setTrackbarPos("HUE low", "Reglage", hsvSettings.low_h);
    }
}

// Fonction de rappel pour ajuster la valeur de "SATURATION low" en fonction de "SATURATION high"
void Low_s(int, void*) {
    if (hsvSettings.low_s > hsvSettings.high_s) {
        hsvSettings.high_s = hsvSettings.low_s;
        setTrackbarPos("SATURATION high", "Reglage", hsvSettings.high_s);
    }
}

// Fonction de rappel pour ajuster la valeur de "SATURATION high" en fonction de "SATURATION low"
void High_s(int, void*) {
    if (hsvSettings.high_s < hsvSettings.low_s) {
        hsvSettings.low_s = hsvSettings.high_s;
        setTrackbarPos("SATURATION low", "Reglage", hsvSettings.low_s);
    }
}

// Fonction de rappel pour ajuster la valeur de "VALUE low" en fonction de "VALUE high"
void Low_v(int, void*) {
    if (hsvSettings.low_v > hsvSettings.high_v) {
        hsvSettings.high_v = hsvSettings.low_v;
        setTrackbarPos("VALUE high", "Reglage", hsvSettings.high_v);
    }
}

// Fonction de rappel pour ajuster la valeur de "VALUE high" en fonction de "VALUE low"
void High_v(int, void*) {
    if (hsvSettings.high_v < hsvSettings.low_v) {
        hsvSettings.low_v = hsvSettings.high_v;
        setTrackbarPos("VALUE low", "Reglage", hsvSettings.low_v);
    }
}

/* --- Classification --- */

// Fonction de segmentation (seuillage) en fonction des réglages
void inRangeDemo(int, void*) {
    inRange(src_hsv, Scalar(hsvSettings.low_h, hsvSettings.low_s, hsvSettings.low_v),
            Scalar(hsvSettings.high_h, hsvSettings.high_s, hsvSettings.high_v), select_pts);
    morphologyEx(select_pts, select_pts, MORPH_OPEN, K);
    morphologyEx(select_pts, select_pts, MORPH_CLOSE, K);
    imshow("Seuillage", select_pts);
}

/* --- Blob --- */

int prevCellRow = 0;
int prevCellCol = 0;
// Fonction de mise à jour de l'affichage des contours et polygones
void BlobUpgrade(int, void*) {
    vector<Moments> mu(contours.size());
    vector<Point2f> mc(contours.size());
    vector<vector<Point>> app_poly(contours.size());
    vector<Rect> boundRect(contours.size());
    double area;

    edges.setTo(0);
    polygones.setTo(0);
    
    // Parcours de tous les contours détectés
    for (uint16_t nb_ctr = 0; nb_ctr < contours.size(); nb_ctr++) {
        // Ignorer les contours internes
        if (hierarchy[nb_ctr][3] != -1)
            continue;

        // Calcul des moments du contour (m00 = moment air ; m01 = moment selon axe x ; m10 = moment selon axe y)
        mu[nb_ctr] = moments(contours[nb_ctr], false);
        area = mu[nb_ctr].m00;

        if (mu[nb_ctr].m00 >= (double)area_min && mu[nb_ctr].m00 > 0 && mu[nb_ctr].m01 > 0) {
            mc[nb_ctr] = Point2f(mu[nb_ctr].m10 / mu[nb_ctr].m00, mu[nb_ctr].m01 / mu[nb_ctr].m00);
            
             // Calcul des coordonnées de la cellule correspondant à l'objet
            int cellRow = static_cast<int>(mc[nb_ctr].y / (src.rows / 10));
            int cellCol = static_cast<int>(mc[nb_ctr].x / (src.cols / 10));

            // Vérification s'il y a un changement dans les coordonnées
            if (cellRow != prevCellRow || cellCol != prevCellCol) {
                // Affichez les informations sur la cellule
                std::cout << "Objet trouvé à la position : ["
                          << cellRow << ", " << cellCol << "]" << std::endl;

                // Mettez à jour les coordonnées précédentes
                prevCellRow = cellRow;
                prevCellCol = cellCol;
            }

            // Couleur aléatoire pour chaque contour
            Scalar colour(rand() & 0xFF, rand() & 0xFF, rand() & 0xFF);
            Scalar colourCenter(0x00, 0x00, 0xFF);

            // Dessin des contours et du centre sur l'image de bords
            drawContours(edges, contours, nb_ctr, colour, FILLED, 8, hierarchy);
            circle(edges, mc[nb_ctr], 4, colourCenter, -1, 8, 0);

            /* --- Approximation Polygonale --- */
            approxPolyDP(Mat(contours[nb_ctr]), app_poly[nb_ctr], 3, true);

            // Couleur aléatoire pour chaque polygone
            Scalar colourPoly(rand() & 0xFF, rand() & 0xFF, rand() & 0xFF);

            // Dessin des polygones sur l'image des polygones
            drawContours(polygones, app_poly, nb_ctr, colourPoly, 1, 8, vector<Vec4i>(), 0, Point());

            // Calcul du rectangle englobant le polygone
            boundRect[nb_ctr] = boundingRect(app_poly[nb_ctr]);

            // Couleur cyan pour les rectangles englobants
            Scalar colourRect(0x00, 0xFF, 0xFF);

            // Dessin des rectangles englobants sur l'image de bords
            rectangle(edges, boundRect[nb_ctr].tl(), boundRect[nb_ctr].br(), colourRect, 2);

            // Ajout du texte "bouchon" sur l'image à la position du rectangle
            putText(edges, "bouchon", boundRect[nb_ctr].tl(), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 2);
        }
    }
    // Affichage des images de bords et polygones
    imshow("Edges", edges);
    // imshow("Polygones", polygones);
}

// Fonction pour sauvegarder les réglages dans un fichier XML
void saveSettings() {
    FileStorage fs(SETTINGS_FILE, FileStorage::WRITE);
    fs << "low_h" << hsvSettings.low_h;
    fs << "high_h" << hsvSettings.high_h;
    fs << "low_s" << hsvSettings.low_s;
    fs << "high_s" << hsvSettings.high_s;
    fs << "low_v" << hsvSettings.low_v;
    fs << "high_v" << hsvSettings.high_v;
    fs.release();
}

// Fonction pour charger les réglages depuis un fichier XML
void loadSettings() {
    FileStorage fs(SETTINGS_FILE, FileStorage::READ);
    if (fs.isOpened()) {
        fs["low_h"] >> hsvSettings.low_h;
        fs["high_h"] >> hsvSettings.high_h;
        fs["low_s"] >> hsvSettings.low_s;
        fs["high_s"] >> hsvSettings.high_s;
        fs["low_v"] >> hsvSettings.low_v;
        fs["high_v"] >> hsvSettings.high_v;
        fs.release();
    }
}
