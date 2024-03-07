#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define SURFMIN 2500
#define SETTINGS_FILE "hsv_settings.xml"

using namespace cv;
using namespace std;

// Structure pour les réglages HSV
struct HsvSettings {
    uint8_t low_h, high_h;
    uint8_t low_s, high_s;
    uint8_t low_v, high_v;
};

HsvSettings hsvSettings;

Mat src, src_hsv, select_pts;

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
    createTrackbar("HUE low", "Reglage", &hsvSettings.low_h, 179, Low_h);
    createTrackbar("HUE high", "Reglage", &hsvSettings.high_h, 179, High_h);

    createTrackbar("SATURATION low", "Reglage", &hsvSettings.low_s, 255, Low_s);
    createTrackbar("SATURATION high", "Reglage", &hsvSettings.high_s, 255, High_s);

    createTrackbar("VALUE low", "Reglage", &hsvSettings.low_v, 255, Low_v);
    createTrackbar("VALUE high", "Reglage", &hsvSettings.high_v, 255, High_v);

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
    morphologyEx(select_pts, select_pts, MORPH_OPEN, Mat());
    morphologyEx(select_pts, select_pts, MORPH_CLOSE, Mat());
    imshow("Seuillage", select_pts);
}

// Fonction de mise à jour de l'affichage des contours et polygones
void BlobUpgrade(int, void*) {
    vector<Moments> mu(contours.size());
    vector<Point2f> mc(contours.size());

    edges.setTo(0);

    // Parcours de tous les contours détectés
    for (size_t nb_ctr = 0; nb_ctr < contours.size(); nb_ctr++) {
        // Ignorer les contours internes
        if (hierarchy[nb_ctr][3] != -1)
            continue;

        // Calcul des moments du contour
        mu[nb_ctr] = moments(contours[nb_ctr], false);

        // Si la superficie du contour est supérieure à la limite minimale
        if (mu[nb_ctr].m00 >= (double)area_min) {
            mc[nb_ctr] = Point2f(mu[nb_ctr].m10 / mu[nb_ctr].m00, mu[nb_ctr].m01 / mu[nb_ctr].m00);

            // Affichage des images de bords et polygones
            rectangle(edges, boundingRect(contours[nb_ctr]), Scalar(0x00, 0xFF, 0xFF), 2);
            putText(edges, "bouchon", boundingRect(contours[nb_ctr]).tl(), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 2);
        }
    }

    imshow("Edges", edges);
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
