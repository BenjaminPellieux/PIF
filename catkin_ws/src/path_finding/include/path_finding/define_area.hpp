#include <ros/ros.h>
#include <unistd.h>
#include <geometry_msgs/Polygon.h>
#include <geometry_msgs/PolygonStamped.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PointStamped.h>
#include <path_finding/GridArray.h>
#include <path_finding/GridStamped.h>

using namespace std;


#define DETECT_RANGE 12.0


class DefineArea {
private:
    geometry_msgs::Polygon area;
    path_finding::GridStamped grid;
    float nbr_subGrid_x, nbr_subGrid_y;
    ros::Publisher grid_pub,
                   origin_pub,
                   next_tile_pub;

    void create_grid();
    void set_origin();
public:
    DefineArea(ros::NodeHandle);
    void choose_next_tile(const geometry_msgs::PointStamped::ConstPtr &);
    void areaCallback(const geometry_msgs::PolygonStamped::ConstPtr &);
};
