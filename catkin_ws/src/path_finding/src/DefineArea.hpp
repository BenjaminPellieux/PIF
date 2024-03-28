#include <ros/ros.h>
#include <unistd.h>
#include <geometry_msgs/Polygon.h>
#include <geometry_msgs/PolygonStamped.h>
#include <geometry_msgs/Point32.h>

#define DETECT_RANGE 12.0

struct Grid {
    geometry_msgs::Point32 sub_area[4];
    bool done;
};


// DÉCLARATION DES VARIABLES =====================================================================================


// PROTOTYPES ====================================================================================================
class DefineArea {
    private:


    public:
        geometry_msgs::Polygon area;
        float nbr_subGrid_x, nbr_subGrid_y;
        ros::Subscriber area_sub;
        Grid grid[1000][1000];
        geometry_msgs::Point32 origin;
        geometry_msgs::Point32 next_tile;


        DefineArea();
        void create_grid();
        void set_origin();
        void choose_next_tile(int, int);
        void areaCallback(const geometry_msgs::PolygonStamped::ConstPtr&);
};
