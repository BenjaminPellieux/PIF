#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdint.h>

cv::Mat grey_img(cv::Mat img){

    cv::Mat graymat;
    cv::cvtColor(img, graymat, cv::COLOR_BGR2GRAY);
    //cv::imshow("Grey Img", graymat);
    std::cout<<"[DEBUG] Grey IMG\n";

    return graymat;
    // cv::imwrite("../Imres/test_threshold    ")
}

bool can_go_forward(cv::Mat img){
    std::cout << img.rows;
    std::cout << "\n";
    std::cout << img.cols;
    std::cout << "\n";

    int largeur = img.cols;
    int hauteur = img.rows;

    int part = 4;
    int taille_part = img.rows/part;

    float ratio_fonce_autorise = 0.05; //ratio de pixels foncés autorisés
    int min_j = 0; //la 1ère colonne observée
    int max_j; //la dernière clonne observée

    //à partir de la 2ème partie de l'image qu'on observe, on ne regarde que le centre
    //la zone observée est réactualisée à chaque partie de l'image
    int b = 0; //compte le nombre de partie ou le robot peut aller

    for (int p = 1; p <= part; p++){
	int f = 0;
	int  c = 0;
	max_j = min_j + largeur;
	for(int i = taille_part*(part-p); i<taille_part*(part-p+1);i++){
		for (int j = min_j; j < max_j; j++){
			if ( (int) img.at<uchar>(i,j) < 60) {//si pixel est foncé
				f++;
			}
			else{
				c++;
			}
		}
    	}
	if (f<taille_part*(part-p+1)*largeur*ratio_fonce_autorise){
		std::cout << "clair\n";
		b++;
	}
	else {
		std::cout << "foncé\n";
		break;
	}
	min_j = min_j + largeur*0.1; //offset a gauche pour la partie des lignes qu'on regarde
	largeur =  largeur*0.8; //nouvelle zone à regarder
	// on passe donc les 10ers%,  on regarde les 80% suivants,  et les 10 derniers % sont ignorés
    }

    if (b>=part*0.5){
	return true;
    }
    else {
	return false;
    }
}


int main(int argc, char** argv) {
    

    // Charger l'image depuis un fichier JPG IMREAD_GRAYSCALE
    cv::Mat image = cv::imread("../Images/ground.jpg");
    cv::Mat img;

    // Vérifier si l'image a été chargée avec succès
    if (!image.data){
        std::cout << "Erreur lors du chargement de l'image." << std::endl;
        return -1; 
    }

    // Afficher l'image dans une fenêtre
    //cv::imshow("Image test", image);
    // Apply the Gaussian Blur filter. 
    // The Size object determines the size of the filter (the "range" of the blur)
    cv::GaussianBlur( image, img, cv::Size( 9, 9 ), 2);
    //cv::imshow("Image lisse", img);

    std::vector<int> compression_params;
    compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);
    cv::Mat greyImg = grey_img(img);
    //cv::imshow("Grey", greyImg);

    bool result = false;
    try
    {
        result = cv::imwrite("image_grise.png", greyImg, compression_params);

    }
    catch (const cv::Exception& ex)
    {
        fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
    }

    //std::cout<<greyImg.empty();
    //std::cout<<"\n";
    
    image = greyImg;

    // Convertir l'image en vecteur de pixels
    cv::Mat data = image.reshape(1, image.rows * image.cols);
    data.convertTo(data, CV_32F);

    // Spécifier le nombre de clusters (k)
    int k = 2;

    // Effectuer la segmentation par k-means
    cv::Mat labels, centers;
    cv::kmeans(data, k, labels, cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 100, 0.8), 3, cv::KMEANS_RANDOM_CENTERS, centers);

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

    bool b = can_go_forward(segmentedGray);
    std::cout << b;
    // Afficher l'image résultante
    cv::imshow("Surfaces approximativement uniformes en niveaux de gris", segmentedGray);
    cv::waitKey(0);
    cv::destroyAllWindows();

    // Attendre une touche pour fermer la fenêtre
    cv::waitKey(0);

    return EXIT_SUCCESS;
}

