#include "path_finding/odometry.hpp"

#include <ros/ros.h>
#include <unistd.h>
#include <geometry_msgs/Polygon.h>
#include <geometry_msgs/PolygonStamped.h>
#include <geometry_msgs/Point.h>
#include <path_finding/GridArray.h>
#include <path_finding/GridStamped.h>


#define DETECT_RANGE 5.0


class DefineArea : public Odometry {
private:
    double nbr_subGrid_x, nbr_subGrid_y;
    ros::Subscriber area_sub;

    void create_grid(geometry_msgs::Polygon);
    void set_origin(geometry_msgs::Polygon);
    Local_Pose pos_in_grid(Local_Pose);
public:
    bool area_recieved;
    Local_Pose next_tile,
               pose_grid,
               first_tile;
    path_finding::GridStamped grid;

    DefineArea(ros::NodeHandle);
    bool choose_next_tile();
    Local_Pose get_next_tile_pose();

    void areaCallback(const geometry_msgs::PolygonStamped::ConstPtr &);
};
