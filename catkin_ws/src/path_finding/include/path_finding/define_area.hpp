#include <ros/ros.h>
#include <unistd.h>
#include <geometry_msgs/Polygon.h>
#include <geometry_msgs/PolygonStamped.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PointStamped.h>
#include <path_finding/GridArray.h>
#include <path_finding/GridStamped.h>


#define DETECT_RANGE 12.0


class DefineArea {
private:
    ros::Publisher grid_pub,
                   origin_pub,
                   next_tile_pub;
    ros::Subscriber area_sub;

    float nbr_subGrid_x, nbr_subGrid_y;

    void create_grid(geometry_msgs::Polygon);
    void set_origin(geometry_msgs::Polygon);
public:
    bool area_recieved;
    path_finding::GridStamped grid;
    geometry_msgs::Point origin,
                         next_tile;

    DefineArea(ros::NodeHandle);
    geometry_msgs::Point choose_next_tile(geometry_msgs::Point);
    void areaCallback(const geometry_msgs::PolygonStamped::ConstPtr &);
};
