#include "zone.hpp"

       
        void Zone::gpsCallback(const sensor_msgs::NavSatFix::ConstPtr& msg) {
            // Callback appelée lors de la réception de messages GPS

            // Obtient les coordonnées GPS
            global_latitude = msg->latitude;
            global_longitude = msg->longitude;

            // Utilisez les coordonnées comme nécessaire (par exemple, les stocker dans des variables globales)
            ROS_INFO("Coordonnées GPS : Latitude = %f, Longitude = %f", global_latitude, global_longitude);
        }



        // Fonction pour calculer le produit vectoriel de deux vecteurs
        double Zone::crossProduct(Point A, Point B, Point C) {
            return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
        }

        // Fonction pour vérifier si un point est à l'intérieur d'un quadrilatère
        bool Zone::isInsideQuadrilateral(Point A, Point B, Point C, Point D, Point P) {
            // Calculer les produits vectoriels pour chaque côté du quadrilatère
            double crossABP = crossProduct(A, B, P);
            double crossBCP = crossProduct(B, C, P);
            double crossCDP = crossProduct(C, D, P);
            double crossDAP = crossProduct(D, A, P);

            // Vérifier si le point est à l'intérieur du quadrilatère
            if ((crossABP >= 0 && crossBCP >= 0 && crossCDP >= 0 && crossDAP >= 0) ||
                (crossABP <= 0 && crossBCP <= 0 && crossCDP <= 0 && crossDAP <= 0)) {
                return true;
            } else {
                return false;
            }
        }
    


void Zone::ZoneCallback(const geometry_msgs::PointStamped & msg){

    switch (Area.header.frame_id){

    case "P1":
        My_Zone.P1 = {Area.point.x, Area.point.y};
        break;
    case "P2":
        My_Zone.P2 = {Area.point.x, Area.point.y};
        break;
    case "P3":
        My_Zone.P3 = {Area.point.x, Area.point.y};
        break;
    case "P4":
        My_Zone.P4 = {Area.point.x, Area.point.y};
        break;
    }


}
int main() {
    double tab[4][3]
    
    // while (1){}
        // lire le topic /Area/Point (Les points de la zone)
        // lire le topic /NavSat/fix (Position GPS du robot)
        // Si data dans Area/Point  
            // cree nouvel objet Zone 
            // defninir P1,P2,P3
    My_Zone();

    return EXIT_SUCCES;
}
