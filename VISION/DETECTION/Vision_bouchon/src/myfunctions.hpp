#pragma once

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define SETTINGS_FILE "hsv_settings.xml"

using namespace cv;
using namespace std;

// Structure pour les réglages HSV
struct HsvSettings {
    uint8_t low_h, high_h;
    uint8_t low_s, high_s;
    uint8_t low_v, high_v;
};

// Variables globales
extern HsvSettings hsvSettings;
extern Mat src, src_hsv, select_pts;
extern bool bouchonFound;
extern vector<vector<Point>> contours;
extern vector<Vec4i> hierarchy;
extern Mat edges;
extern int area_min;

// Déclaration des fonctions de rappel
void inRangeDemo(int, void*);
void Low_h(int, void*);
void High_h(int, void*);
void Low_s(int, void*);
void High_s(int, void*);
void Low_v(int, void*);
void High_v(int, void*);
void BlobUpgrade(int, void*);
void saveSettings();
void loadSettings();
