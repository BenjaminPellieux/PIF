/*#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/PointCloud.h>
#include <geometry_msgs/Point32.h>
#include <tf/transform_listener.h>
#include <pcl_ros/transforms.h>
#include <pcl_conversions/pcl_conversions.h>

#define BUFFER_SIZE 1000 // Taille du buffer, ajustez selon vos besoins
#define ODOM_FRAME  "odom"
#define SCAN_FRAME  "laser_mount_link"

ros::Publisher point_cloud_pub;
nav_msgs::Odometry global_odom;
nav_msgs::Odometry previous_odom;
pcl::PointCloud point_cloud_buffer; // Buffer de nuages de points

void updatePointCloudBuffer(const sensor_msgs::LaserScan::ConstPtr& scan)
{
    double delta_x = global_odom.pose.pose.position.x - previous_odom.pose.pose.position.x;
    double delta_y = global_odom.pose.pose.position.y - previous_odom.pose.pose.position.y;
    double delta_z = global_odom.pose.pose.position.z - previous_odom.pose.pose.position.z;

    // Calcul de la différence de rotation
    tf::Quaternion q1(previous_odom.pose.pose.orientation.x, previous_odom.pose.pose.orientation.y,
                      previous_odom.pose.pose.orientation.z, previous_odom.pose.pose.orientation.w);

    tf::Quaternion q2(global_odom.pose.pose.orientation.x, global_odom.pose.pose.orientation.y,
                      global_odom.pose.pose.orientation.z, global_odom.pose.pose.orientation.w);
    tf::Quaternion delta_q = q2 * q1.inverse();

    // Transformation des points du nuage de points
    tf::Transform transform(delta_q, tf::Vector3(delta_x, delta_y, delta_z));

    pcl_ros::transformPointCloud(SCAN_FRAME, transform, point_cloud_buffer);

    // Ajouter un nouveau nuage de points
    for (int i = 0; i < scan->ranges.size(); ++i)
    {
        geometry_msgs::Point32 point;
        point.x = scan->ranges[i] * cos(scan->angle_min + i * scan->angle_increment);
        point.y = scan->ranges[i] * sin(scan->angle_min + i * scan->angle_increment);
        point.z = 0.0; // L'information de la hauteur peut ne pas être disponible dans tous les scans
        point_cloud_buffer.points.push_back(point);
    }

    // Supprimer le plus ancien nuage de points si le buffer dépasse la taille souhaitée
    while (point_cloud_buffer.size() > BUFFER_SIZE)
    {
        point_cloud_buffer.pop_front();
    }

    // Publier le nuage de points final
    point_cloud_pub.publish(point_cloud_buffer);

    previous_odom = global_odom;
}

void odomCallback(const nav_msgs::Odometry::ConstPtr& odom)
{
    global_odom = *odom;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "scan_fade_node");
    ros::NodeHandle nh;

    point_cloud_pub = nh.advertise<sensor_msgs::PointCloud>("/point_cloud", 1);
    ros::Subscriber odom_sub = nh.subscribe("/odometry/filtered", 1, odomCallback);
    ros::Subscriber laser_sub = nh.subscribe("/scan", 1, updatePointCloudBuffer);

    tf::TransformListener tf_listener; // Ajouter une instance du transformateur ici

    ros::spin();

    return 0;
}*/
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/PointCloud.h>
#include <geometry_msgs/Point32.h>
#include <tf/transform_listener.h>
#include <pcl_ros/transforms.h>
#include <pcl_conversions/pcl_conversions.h>

#define BUFFER_SIZE 1000 // Taille du buffer, ajustez selon vos besoins
#define ODOM_FRAME  "odom"
#define SCAN_FRAME  "laser_mount_link"

ros::Publisher point_cloud_pub;
nav_msgs::Odometry global_odom;
nav_msgs::Odometry previous_odom;
sensor_msgs::PointCloud point_cloud_buffer; // Utilisation de sensor_msgs::PointCloud

void updatePointCloudBuffer(const sensor_msgs::LaserScan::ConstPtr& scan)
{
    double delta_x = global_odom.pose.pose.position.x - previous_odom.pose.pose.position.x;
    double delta_y = global_odom.pose.pose.position.y - previous_odom.pose.pose.position.y;
    double delta_z = global_odom.pose.pose.position.z - previous_odom.pose.pose.position.z;

    // Calcul de la différence de rotation
    tf::Quaternion q1(previous_odom.pose.pose.orientation.x, previous_odom.pose.pose.orientation.y,
                      previous_odom.pose.pose.orientation.z, previous_odom.pose.pose.orientation.w);

    tf::Quaternion q2(global_odom.pose.pose.orientation.x, global_odom.pose.pose.orientation.y,
                      global_odom.pose.pose.orientation.z, global_odom.pose.pose.orientation.w);
    tf::Quaternion delta_q = q2 * q1.inverse();

    // Transformation des points du nuage de points
    tf::Transform transform(delta_q, tf::Vector3(delta_x, delta_y, delta_z));
    

pcl::PointCloud pcl_cloud;
pcl::fromROSMsg(point_cloud_buffer, pcl_cloud);

// Transformer le nuage de points dans le cadre de référence global
    pcl_ros::transformPointCloud(SCAN_FRAME, transform, point_cloud_buffer, point_cloud_buffer);
    pcl::toROSMsg(*pcl_cloud, point_cloud_buffer);
    
    // Ajouter un nouveau nuage de points
    for (int i = 0; i < scan->ranges.size(); ++i)
    {
        geometry_msgs::Point32 point;
        point.x = scan->ranges[i] * cos(scan->angle_min + i * scan->angle_increment);
        point.y = scan->ranges[i] * sin(scan->angle_min + i * scan->angle_increment);
        point.z = 0.0; // L'information de la hauteur peut ne pas être disponible dans tous les scans
        point_cloud_buffer.points.push_back(point);
    }

    

    // Supprimer le plus ancien nuage de points si le buffer dépasse la taille souhaitée
    while (point_cloud_buffer.points.size() > BUFFER_SIZE)
    {
        point_cloud_buffer.points.pop_front();
    }

    // Publier le nuage de points final
    point_cloud_pub.publish(point_cloud_buffer);

    previous_odom = global_odom;
}

void odomCallback(const nav_msgs::Odometry::ConstPtr& odom)
{
    global_odom = *odom;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "scan_fade_node");
    ros::NodeHandle nh;

    point_cloud_pub = nh.advertise<sensor_msgs::PointCloud>("/point_cloud", 1);
    ros::Subscriber odom_sub = nh.subscribe("/odometry/filtered", 1, odomCallback);
    ros::Subscriber laser_sub = nh.subscribe("/scan", 1, updatePointCloudBuffer);

    tf::TransformListener tf_listener; // Ajouter une instance du transformateur ici

    ros::spin();

    return 0;
}

