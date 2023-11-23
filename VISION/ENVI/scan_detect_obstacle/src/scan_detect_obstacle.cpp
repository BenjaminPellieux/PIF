/*
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/Odometry.h>
#include <visualization_msgs/Marker.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

#define MIN_DISTANCE 0.2  // Distance minimale pour détecter un obstacle
#define MAX_DISTANCE 5.0  // Distance maximale pour détecter un obstacle

// Déclarez ces deux objets globalement
tf::TransformBroadcaster tf_broadcaster;
tf::TransformListener tf_listener;

ros::Publisher marker_pub;

// Variables pour stocker l'odométrie précédente
nav_msgs::Odometry previous_odom;
bool first_odom_received = false;

// Déclarez odom_msg en tant que variable globale
nav_msgs::Odometry::ConstPtr odom_msg;

void odomCallback(const nav_msgs::Odometry::ConstPtr& odom_msg)
{
    if (!first_odom_received)
    {
        previous_odom = *odom_msg;
        first_odom_received = true;
    }

    // Stockez la valeur d'odom_msg pour une utilisation ultérieure
    ::odom_msg = odom_msg;
}

void laserCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
    // Parcourir les données du LIDAR pour détecter un obstacle
    float min_range = MAX_DISTANCE;
    int min_index = -1;

    for (int i = 0; i < scan->ranges.size(); ++i)
    {
        if (scan->ranges[i] >= MIN_DISTANCE && scan->ranges[i] <= MAX_DISTANCE)
        {
            if (scan->ranges[i] < min_range)
            {
                min_range = scan->ranges[i];
                min_index = i;
            }
        }
    }

    visualization_msgs::Marker marker;
    marker.header.frame_id = "base_laser_link"; // Assurez-vous que c'est le bon cadre de référence du LIDAR
    marker.header.stamp = ros::Time::now();
    marker.ns = "moving_obstacle_marker";
    marker.id = 0;
    marker.type = visualization_msgs::Marker::ARROW;
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.x = 0; // Ajustez la position x, y et z selon votre configuration
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;
    marker.scale.x = 0.1;  // Largeur de la flèche
    marker.scale.y = 0.01; // Épaisseur de la flèche
    marker.scale.z = 0.01; // Hauteur de la flèche
    marker.color.a = 1.0;   // Opacité
    marker.color.r = 1.0;   // Couleur rouge
    marker.color.g = 0.0;   // Couleur verte
    marker.color.b = 0.0;   // Couleur bleue

    if (min_index != -1)
    {
        float angle = scan->angle_min + min_index * scan->angle_increment;

        // Créez une transformation entre le cadre de référence du LIDAR et le cadre de référence global
        tf::Transform transform;
        transform.setOrigin(tf::Vector3(0, 0, 0)); // Les valeurs x, y et z dépendront de votre configuration
        tf::Quaternion q;
        q.setRPY(0, 0, angle); // Utilisez l'angle pour définir l'orientation
        transform.setRotation(q);

        // Publiez la transformation
        tf_broadcaster.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "base_laser_link", "global_frame"));

        // Maintenant, vous pouvez utiliser cette transformation pour obtenir l'orientation dans le cadre de référence global
        tf::StampedTransform orientation_in_global;
        try
        {
            tf_listener.lookupTransform("global_frame", "base_laser_link", ros::Time(0), orientation_in_global);
        }
        catch (tf::TransformException ex)
        {
            ROS_ERROR("%s", ex.what());
            return;
        }

        // Utilisez l'orientation_in_global pour définir l'orientation de votre Marker
        geometry_msgs::Quaternion orientation_msg;
        tf::quaternionTFToMsg(orientation_in_global.getRotation(), orientation_msg);
        marker.pose.orientation = orientation_msg;

        // Comparez avec l'odométrie précédente pour détecter le mouvement
        float delta_x = odom_msg->pose.pose.position.x - previous_odom.pose.pose.position.x;
        float delta_y = odom_msg->pose.pose.position.y - previous_odom.pose.pose.position.y;
        float delta_distance = sqrt(delta_x * delta_x + delta_y * delta_y);

        if (delta_distance > 0.01) // Ajustez cette valeur selon votre besoin de sensibilité au mouvement
        {
            // Obstacle en mouvement détecté
            marker_pub.publish(marker);
        }
    }

    // Stockez l'odométrie actuelle pour la prochaine itération
    previous_odom = *odom_msg;
}

int main(int argc, char** argv)
{
    std::cout << "done !\n";
    ros::init(argc, argv, "scan_detect_obstacle");
    ros::NodeHandle nh;

    ros::Subscriber laser_sub = nh.subscribe("/scan", 1, laserCallback);
    ros::Subscriber odom_sub = nh.subscribe("/odometry/filtered", 1, odomCallback);
    marker_pub = nh.advertise<visualization_msgs::Marker>("/moving_obstacle_marker", 1);

    ros::spin();

    return 0;
}
*/
#include <stdlib.h>
#include <stdio.h>
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <visualization_msgs/Marker.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <tf/transform_datatypes.h>

#define MIN_DISTANCE 0.2  // Distance minimale pour détecter un obstacle
#define MAX_DISTANCE 5.0  // Distance maximale pour détecter un obstacle

// Déclarez ces deux objets globalement
tf::TransformBroadcaster tf_broadcaster;
tf::TransformListener tf_listener;

ros::Publisher marker_pub;

void laserCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
    // Parcourir les données du LIDAR pour détecter un obstacle
    float min_range = MAX_DISTANCE;
    int min_index = -1;

    for (int i = 0; i < scan->ranges.size(); ++i)
    {
        if (scan->ranges[i] >= MIN_DISTANCE && scan->ranges[i] <= MAX_DISTANCE)
        {
            if (scan->ranges[i] < min_range)
            {
                min_range = scan->ranges[i];
                min_index = i;
            }
        }
    }

    visualization_msgs::Marker marker;
    marker.header.frame_id = "base_laser_link"; // Assurez-vous que c'est le bon cadre de référence du LIDAR
    marker.header.stamp = ros::Time::now();
    marker.ns = "obstacle_marker";
    marker.id = 0;
    marker.type = visualization_msgs::Marker::ARROW;
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.x = 0; // Ajustez la position x, y et z selon votre configuration
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;
    marker.scale.x = 0.1;  // Largeur de la flèche
    marker.scale.y = 0.01; // Épaisseur de la flèche
    marker.scale.z = 0.01; // Hauteur de la flèche
    marker.color.a = 1.0;   // Opacité
    marker.color.r = 1.0;   // Couleur rouge
    marker.color.g = 0.0;   // Couleur verte
    marker.color.b = 0.0;   // Couleur bleue

    if (min_index != -1)
{
    float angle = scan->angle_min + min_index * scan->angle_increment;

    // Créez une transformation entre le cadre de référence du LIDAR et le cadre de référence global
    tf::Transform transform;
    transform.setOrigin(tf::Vector3(0, 0, 0)); // Les valeurs x, y et z dépendront de votre configuration
    tf::Quaternion q;
    q.setRPY(0, 0, angle); // Utilisez l'angle pour définir l'orientation
    transform.setRotation(q);

    // Publiez la transformation
    tf_broadcaster.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "base_laser_link", "global_frame"));

    // Maintenant, vous pouvez utiliser cette transformation pour obtenir l'orientation dans le cadre de référence global
    tf::StampedTransform orientation_in_global;
    try
    {
        tf_listener.lookupTransform("global_frame", "base_laser_link", ros::Time(0), orientation_in_global);
    }
    catch (tf::TransformException ex)
    {
        ROS_ERROR("%s", ex.what());
        return;
    }

    // Utilisez l'orientation_in_global pour définir l'orientation de votre Marker
    tf::quaternionTFToMsg(orientation_in_global.getRotation(), marker.pose.orientation);
}
else
{
    // Aucun obstacle détecté, orientation par défaut
    tf::quaternionTFToMsg(tf::createQuaternionFromRPY(0, 0, 0), marker.pose.orientation);
}

    marker_pub.publish(marker);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "obstacle_detection_node");
    ros::NodeHandle nh;

    ros::Subscriber laser_sub = nh.subscribe("/scan", 1, laserCallback);
    marker_pub = nh.advertise<visualization_msgs::Marker>("/obstacle_marker", 1);

    ros::spin();

    return 0;
}
