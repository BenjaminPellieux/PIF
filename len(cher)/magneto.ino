#include <ros.h>
#include <std_msgs/Float32.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
  
Adafruit_BNO055 bno = Adafruit_BNO055(55);


ros::NodeHandle nh;
std_msgs::Float32 orientation;
ros::Publisher return_orientation("pif/magneto/data", &orientation);


void setup(void) 
{
  nh.initNode();
  nh.advertise(return_orientation);
  ROS_INFO("Orientation Sensor Test");
  
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    ROS_INFO("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  delay(1000);
    
  bno.setExtCrystalUse(true);

  while (!nh.connected())
    nh.spinOnce();
}

void loop(void) 
{
  double yaw = 0;
  /* Get a new sensor event */
  for (int i = 0; i < 10; i++)
  { 
    sensors_event_t event; 
    bno.getEvent(&event, Adafruit_BNO055::VECTOR_MAGNETOMETER);
    
      /* Display the floating point data */
    double magX = -1000000, magY = -1000000 , magZ = -1000000;
    magX = event.magnetic.x;
    magY = event.magnetic.y;
    magZ = event.magnetic.z;

    yaw += atan2(magY, magX) * (1/3.14159);

    delay(1);
  }
  orientation.data = yaw / 10;

  return_orientation.publish(&orientation);
  nh.spinOnce();
}
