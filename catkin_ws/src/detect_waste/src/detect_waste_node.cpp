#include "detect_waste.hpp"

WasteDetection::WasteDetection(VideoSender &videoSender) : videoSender_(videoSender)
{
    this->closest_rect.y = 0;
    this->detect_pub = nh.advertise<geometry_msgs::Point>("/pif/waste/pos", 1000);
    this->vector_waste = nh.advertise<geometry_msgs::QuaternionStamped>("/pif/waste/geometry", 10000);
    this->moving_status = nh.subscribe("/pif/moving", 10, &WasteDetection::obstacleCallback, this);
    std::cout << "DEBUG START Detect waste" << std::endl;
    // this->cap.open("/home/ros/PIF/VISION/DETECTION/Video/Default_Video_Test.mp4");
    this->cap.open(0);
    if (!cap.isOpened())
    {
        std::cout << "Erreur: Impossible d'ouvrir la vidéo." << std::endl;
        exit(-1);
    }
    run();
}

void WasteDetection::obstacleCallback(const std_msgs::Bool &msg)
{
    this->obstacle_app = msg.data;
}

void WasteDetection::detect_obstacle()
{
    std::cout << "Je detecte les obstacles\n";
}

void WasteDetection::detect_waste()
{
    std::cout << "Je detecte les dechet\n";
    cv::Mat image_blurred, hsv, mask_others, mask_majority_color, kernel;
    std::vector<std::vector<cv::Point>> contours;

    cv::GaussianBlur(this->frame, image_blurred, cv::Size(9, 9), 3, 3); // Appliquer un filtre gaussien pour lisser l'image
    cv::cvtColor(image_blurred, hsv, cv::COLOR_BGR2HSV);                // Convertir l'image en espace couleur HSV

    // Calculer l'histogramme de la saturation (S)
    int histSize[] = {256};
    float s_ranges[] = {0, 256};
    const float *ranges[] = {s_ranges};
    int channels[] = {1}; // Utilisation du canal de saturation
    cv::Mat hist_sat;
    cv::calcHist(&hsv, 1, channels, cv::Mat(), hist_sat, 1, histSize, ranges, true, false);

    // Trouver la saturation la plus fréquente
    double maxVal = 0;
    cv::Point maxLoc;
    cv::minMaxLoc(hist_sat, 0, &maxVal, 0, &maxLoc);

    // La saturation la plus fréquente sera l'indice de la valeur maximale
    // Déterminer les seuils pour isoler la couleur majoritaire basée sur la saturation
    // Créer un masque pour les couleurs qui ne sont pas dans la plage de la couleur majoritaire basée sur la saturation
    cv::inRange(hsv, cv::Scalar(0, std::max(maxLoc.y - SAT_RANGE, 0), 20),
                cv::Scalar(180, std::min(maxLoc.y + SAT_RANGE, 255), 255), mask_majority_color);
    mask_others = ~mask_majority_color;

    // Optionnel: appliquer des opérations morphologiques pour nettoyer le masque
    kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(15, 15));
    cv::morphologyEx(mask_others, mask_others, cv::MORPH_OPEN, kernel);
    cv::morphologyEx(mask_others, mask_others, cv::MORPH_CLOSE, kernel);

    // Trouver les contours dans le masque des autres couleurs
    cv::findContours(mask_others.clone(), contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    this->count_area = 1;
    this->closest_rect.y = 0;
    for (size_t i = 0; i < contours.size(); i++)
    {
        double area = cv::contourArea(contours[i]);
        cv::Rect rect = cv::boundingRect(contours[i]);
        if ((rect.y >= this->mid_height) && ((area > MIN_AREA) && (area < MAX_AREA)))
        { // Filtre basé sur la taille de l'objet

            if (rect.y > closest_rect.y)
            {
                this->closest_rect = rect;
            }

            if (DEBUG)
            {
                // Affichage de debug
                // std::cout<<"DEBUG count_area" <<this->count_area<<'\n';
                // std::cout << "[LOG] Forme " << this->count_area << " area: " << area << "\n";
                cv::rectangle(this->frame, rect.tl(), rect.br(), cv::Scalar(0, 255, 0), 2);
                std::string text = "#" + std::to_string(this->count_area) + " Area: " + std::to_string(static_cast<int>(area));
                cv::Point textOrg(rect.x, rect.y - 10);
                cv::putText(this->frame, text, textOrg, cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 250, 0), 1);
                cv::line(this->frame, {this->mid_width, 0}, {this->mid_width, frame.rows}, cv::Scalar(255, 0, 0));                               // ligne vertical
                cv::line(this->frame, {0, this->mid_height}, {frame.cols, this->mid_height}, cv::Scalar(0, 0, 255));                             // ligne orizonthale
                cv::line(this->frame, {this->mid_width, this->frame.rows}, {this->closest_rect.x, this->closest_rect.y}, cv::Scalar(0, 250, 0)); // ligne orizonthale
            }
            this->count_area++;
        }
    }
    change_origin();
    // std::cout<<"Closest pos x: "<<closest_rect.x<<" y: "<<closest_rect.y<<"\n";
    geometry_msgs::Point msg;
    msg.x = this->closest_rect.x;
    msg.y = this->closest_rect.y;

    this->vector_waste.publish(calc_geometry_msgs());
    this->detect_pub.publish(msg);
}

void WasteDetection::run()
{

    while (ros::ok())
    {

        bool bSuccess = cap.read(this->frame);
        if (!bSuccess)
        {
            std::cout << "Fin de la vidéo" << std::endl;
            cap.release();
            break;
        }
        this->mid_height = this->frame.rows / 2;
        this->mid_width = this->frame.cols / 2;

        if (this->obstacle_app)
        {
            detect_obstacle();
        }
        else
        {
            detect_waste();
        }
        videoSender_.send(this->frame);
        ros::spinOnce();
    }
}

void WasteDetection::change_origin()
{
    this->closest_rect.y = this->frame.rows - this->closest_rect.y;
    this->closest_rect.x -= this->mid_width;
}

geometry_msgs::QuaternionStamped WasteDetection::calc_geometry_msgs()
{
    double theta = std::atan2(this->closest_rect.x, this->closest_rect.y);

    geometry_msgs::QuaternionStamped msgs;

    msgs.header.stamp = ros::Time::now();
    msgs.header.frame_id = "QuatWaste";
    msgs.quaternion.x = 0.0;
    msgs.quaternion.y = 0.0;
    msgs.quaternion.z = std::sin(theta / 2.0);
    msgs.quaternion.w = 1.0; // std::cos(theta / 2.0);
    return msgs;
}

int main(int argc, char **argv)
{
    // Ouvrir le flux vidéo
    ros::init(argc, argv, "detect_waste");
    VideoSender sender(IP_SERV, PORT_SERV);
    WasteDetection detection = WasteDetection(sender);
    // Libérer le flux vidéo et détruire toutes les fenêtres

    return 0;
}
