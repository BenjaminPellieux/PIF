#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/PointCloud.h>
#include <tf/transform_listener.h>
  
#define BUFFER_SIZE 10 // Taille du buffer, ajustez selon vos besoins

ros::Publisher *point_cloud_pub_ptr;


std::deque<sensor_msgs::PointCloud> point_cloud_buffer; // Buffer de nuages de points
tf::TransformListener *tf_listener_ptr;

void updatePointCloudBuffer(const sensor_msgs::LaserScan::ConstPtr& scan)
{
    sensor_msgs::PointCloud point_cloud;
    // Remplissez les données du nuage de points à partir du scan Lidar
    // ...

    // Transformez le nuage de points dans le cadre de référence global
    sensor_msgs::PointCloud transformed_point_cloud;
    tf_listener_ptr->waitForTransform("odom", scan->header.frame_id, ros::Time(0), ros::Duration(1.0));
    tf_listener_ptr->transformPointCloud("odom", ros::Time(0), point_cloud, scan->header.frame_id, transformed_point_cloud);

    // Ajoutez le nuage de points transformé au buffer
    point_cloud_buffer.push_back(transformed_point_cloud);

    // Si le buffer dépasse la taille souhaitée, supprimez les éléments les plus anciens
    while (point_cloud_buffer.size() > BUFFER_SIZE)
    {
        point_cloud_buffer.pop_front();
    }

    // Concaténez les nuages de points du buffer pour former un seul nuage de points
    sensor_msgs::PointCloud final_point_cloud;
    for (const auto& pc : point_cloud_buffer)
    {
        final_point_cloud.points.insert(final_point_cloud.points.end(), pc.points.begin(), pc.points.end());
    }

    // Publiez le nuage de points final
    point_cloud_pub_ptr->publish(final_point_cloud);
}

void odomCallback(const nav_msgs::Odometry::ConstPtr& odom)
{
    // Vous pouvez faire quelque chose avec les données d'odométrie si nécessaire
    // ...
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "scan_fade_node");
    ros::NodeHandle nh;
    
    point_cloud_pub_ptr = new ros::Publisher();
    *point_cloud_pub_ptr = nh.advertise<sensor_msgs::PointCloud>("/point_cloud", 1);
    ros::Subscriber laser_sub = nh.subscribe("/scan", 1, updatePointCloudBuffer);
    ros::Subscriber odom_sub = nh.subscribe("/odometry/filtered", 1, odomCallback);
    tf_listener_ptr = new tf::TransformListener();
    

    ros::spin();

    return 0;
}
