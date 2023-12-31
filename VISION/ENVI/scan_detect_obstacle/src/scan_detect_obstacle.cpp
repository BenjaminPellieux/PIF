
#include <stdlib.h>
#include <stdio.h>
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <visualization_msgs/Marker.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <tf/transform_datatypes.h>

#define MIN_DISTANCE 0.5  // Distance minimale pour détecter un obstacle M
#define MAX_DISTANCE 2.0  // Distance maximale pour détecter un obstacle
#define MIN_SIZE_OBSTACLE	5	//nbr
#define MIN_SIZE_HOLE	0.3	//M (for pathfinding)
#define ANGLE_MIN	45	//°	
    tf::TransformBroadcaster *tf_broadcaster_ptr;
    tf::TransformListener *tf_listener_ptr;
    ros::Publisher *marker_pub_ptr;

void laserCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{

    int min_index = -1;
    int obstacle_count = 0;
    float closest_obstacle_dist = MAX_DISTANCE;
    
    printf("size : %d\n", scan->ranges.size());
    printf("angle min : %d\n", scan->angle_min);
    
    for (int i = 0; i < scan->ranges.size(); ++i)
    {
        if (((scan->ranges[i - 1] - MIN_SIZE_HOLE) >= scan->ranges[i] ) &&
             ((scan->ranges[i - 1] + MIN_SIZE_HOLE) <= scan->ranges[i])) {
            if (i > 0) {
                //TODO (for pathfinding : ways possibles, closed/open obstacles if differences betwin two points too large)
            }    
        }
        
        
        if (scan->ranges[i] >= MIN_DISTANCE && scan->ranges[i] <= MAX_DISTANCE)
        {
            obstacle_count++;
            if (closest_obstacle_dist > scan->ranges[i]) {
                closest_obstacle_dist = scan->ranges[i];
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
    marker.scale.x = scan->ranges[min_index];  // Largeur de la flèche
    marker.scale.y = 0.01; // Épaisseur de la flèche
    marker.scale.z = 0.01; // Hauteur de la flèche
    marker.color.a = 1.0;   // Opacité
    marker.color.r = 1.0;   // Couleur rouge
    marker.color.g = 0.0;   // Couleur verte
    marker.color.b = 0.0;   // Couleur bleue

    if (obstacle_count)
{
    float angle = ((float)scan->angle_increment * (float)min_index) + (ANGLE_MIN * 0.017453);
    std::cout << "obstacle found ! Angle : " << angle << "\n";
    std::cout << "Angle n : " << min_index << "\n";
    // Créez une transformation entre le cadre de référence du LIDAR et le cadre de référence global
    tf::Transform transform;
    transform.setOrigin(tf::Vector3(0, 0, 0)); // Les valeurs x, y et z dépendront de votre configuration
    tf::Quaternion q;
    q.setRPY(0, 0, angle); // Utilisez l'angle pour définir l'orientation
    transform.setRotation(q);

    // Publiez la transformation
    tf_broadcaster_ptr->sendTransform(tf::StampedTransform(transform, ros::Time::now(), "base_laser_link", "global_frame"));

    // Maintenant, vous pouvez utiliser cette transformation pour obtenir l'orientation dans le cadre de référence global
    tf::StampedTransform orientation_in_global;
    try
    {
        tf_listener_ptr->lookupTransform("global_frame", "laser", ros::Time(0), orientation_in_global);
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

    marker_pub_ptr->publish(marker);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "obstacle_detection_node");
    ros::start();
    
    ros::NodeHandle nh;
    

    
    tf_broadcaster_ptr = new tf::TransformBroadcaster();
    tf_listener_ptr = new tf::TransformListener();
    
    marker_pub_ptr = new ros::Publisher();
    ros::Subscriber laser_sub = nh.subscribe("/scan", 1, laserCallback);
    *marker_pub_ptr = nh.advertise<visualization_msgs::Marker>("/obstacle_marker", 1);
    

    ros::spin();
    ros::shutdown();
    
    delete tf_broadcaster_ptr;
    delete tf_listener_ptr;
    return 0;
}
