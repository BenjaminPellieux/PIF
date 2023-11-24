#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Charger l'image
    cv::Mat image = cv::imread("vision_1.jpg");

    if (image.empty()) {
        std::cerr << "Impossible de charger l'image." << std::endl;
        return -1;
    }

    // Convertir l'image en vecteur de pixels
    cv::Mat data = image.reshape(1, image.rows * image.cols);
    data.convertTo(data, CV_32F);

    // Spécifier le nombre de clusters (k)
    int k = 2;

    // Effectuer la segmentation par k-means
    cv::Mat labels, centers;
    cv::kmeans(data, k, labels, cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 100, 0.2), 3, cv::KMEANS_RANDOM_CENTERS, centers);

    // Convertir les centres des clusters en entiers (niveaux de gris)
    centers.convertTo(centers, CV_8U);

    // Assigner chaque pixel à la couleur du centre du cluster auquel il appartient
    cv::Mat segmented(image.rows, image.cols, CV_8UC3);
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            int clusterIndex = labels.at<int>(i * image.cols + j, 0);
            segmented.at<cv::Vec3b>(i, j) = centers.at<cv::Vec3b>(clusterIndex, 0);
        }
    }

    // Convertir l'image segmentée en niveaux de gris
    cv::Mat segmentedGray;
    cv::cvtColor(segmented, segmentedGray, cv::COLOR_BGR2GRAY);

    // Afficher l'image résultante
    cv::imshow("Surfaces approximativement uniformes en niveaux de gris", segmentedGray);
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}

