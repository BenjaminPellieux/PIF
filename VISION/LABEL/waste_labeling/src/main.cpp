// Open this file with the VScode plugin platformIO
// use commande:  rosrun rosserial_arduino make_libraries.py .
// In lib folder to get ros.h lib
// unable ros com with arduino  rosrun rosserial_python serial_node.py /dev/ttyACM0 
#include <Arduino.h>
#include <HUSKYLENS.h>
#include "SoftwareSerial.h"
#include <ros.h>
#include <std_msgs/String.h>

#define mySerial Serial3
HUSKYLENS huskylens;
//SoftwareSerial mySerial(10, 11); // RX, TX
ros::NodeHandle  nh;

std_msgs::String str_msg;
ros::Publisher pu_label("Label/id", &str_msg);


void setup() {
  str_msg.data = "NULL";

  mySerial.begin(9600);
  huskylens.begin(mySerial);
  nh.initNode();
  nh.getHardware()->setBaud(57600);
  nh.advertise(pu_label);
}

void loop() {
  if(huskylens.request()){
    str_msg.data = "REQUESTED";
    pu_label.publish(&str_msg);
  }
  
  if (huskylens.available()) {
    HUSKYLENSResult result = huskylens.read();

    if (result.command == COMMAND_RETURN_BLOCK) {
      if (result.ID == 4) {
        str_msg.data = "Megot"; 
        //Serial.println("Megot de cigarette trouve!");
      }
      else if (result.ID == 3) { 
        str_msg.data = "Capsule "; 
        //Serial.println("Capsule de biere trouvee!");           
      }
      else{
        str_msg.data = "NULLOS";
      }
     
    }
  }else{
    str_msg.data = "NAVABLE";
  }
  pu_label.publish( &str_msg );
  nh.spinOnce();
  delay(300); 
}

