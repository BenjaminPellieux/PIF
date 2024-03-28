// Open this file with the VScode plugin platformIO
// use commande:  rosrun rosserial_arduino make_libraries.py .
// rosrun rosserial_python serial_node.py /dev/ttyACM0 _baud:=57600
// In lib folder to get ros.h lib
// unable ros com with arduino  rosrun rosserial_python serial_node.py /dev/ttyACM0 
#include <Arduino.h>
#include <HUSKYLENS.h>
#include "SoftwareSerial.h"
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>

#define mySerial Serial3
<<<<<<< HEAD
HUSKYLENS huskylens;
//SoftwareSerial mySerial(10, 11); // RX, TX
ros::NodeHandle  nh;

=======
#define RELAY_ALIM 2
#define RELAY_ASPI 3

HUSKYLENS huskylens;
//SoftwareSerial mySerial(10, 11); // RX, TX

ros::NodeHandle  nh;
>>>>>>> 32636d384730adeb8598ad0ba859e502432bed64
std_msgs::String str_msg;
std_msgs::Bool bool_msg;
ros::Publisher pu_label("Label/id", &str_msg);
ros::Publisher pu_aspi("Aspi/Status", &bool_msg);
bool foundRelevantObject;
int my_delay; 

void setup() {
  str_msg.data = "NULL";
<<<<<<< HEAD

  mySerial.begin(9600);
  huskylens.begin(mySerial);
  nh.initNode();
  nh.getHardware()->setBaud(57600);
  nh.advertise(pu_label);
}
=======
  bool_msg.data = false; 
  foundRelevantObject = false;

  mySerial.begin(9600);
  huskylens.begin(mySerial);
  //Serial.println("HuskyLens is ready.");
  nh.initNode();
  nh.getHardware()->setBaud(57600);
  nh.advertise(pu_label);
  nh.advertise(pu_aspi);
  // Enable PIN mode for relay
  pinMode(RELAY_ALIM, OUTPUT);
  pinMode(RELAY_ASPI, OUTPUT);
>>>>>>> 32636d384730adeb8598ad0ba859e502432bed64

  // Init relay a HIGH (off)
  digitalWrite(RELAY_ALIM, HIGH);
  digitalWrite(RELAY_ASPI, HIGH);

}
void loop() {
<<<<<<< HEAD
  if(huskylens.request()){
    str_msg.data = "REQUESTED";
    pu_label.publish(&str_msg);
  }
  
  if (huskylens.available()) {
=======
  if (!huskylens.request()) {
    //Serial.println("Failed to request data from HuskyLens, will retry.");
      str_msg.data = "REQUESTED";
      pu_label.publish(&str_msg);
  }

   // Indicateur pour savoir si un objet pertinent a été trouvé

  if(huskylens.available()) {
>>>>>>> 32636d384730adeb8598ad0ba859e502432bed64
    HUSKYLENSResult result = huskylens.read();

    if(result.command) {
      if (result.ID == 4) {
<<<<<<< HEAD
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
=======
        str_msg.data = "MEG";
        Serial.println("Megot de cigarette trouve!");
        foundRelevantObject = true;
      }
      else if(result.ID == 3){
          str_msg.data = "CAP";
          Serial.println("Capsule de biere trouvee!");
          foundRelevantObject = true;
      }
      else{
          foundRelevantObject = false;
          str_msg.data = "NULL";

        }
    }

    if (!foundRelevantObject) {
      bool_msg.data = false;
      digitalWrite(RELAY_ASPI, HIGH);
      digitalWrite(RELAY_ALIM, HIGH);
      my_delay = 10;
    } else {
      bool_msg.data = true;
      digitalWrite(RELAY_ALIM, LOW);
      digitalWrite(RELAY_ASPI, LOW);
      my_delay = 30;
    }
  }else{
    str_msg.data = "NABLE";
  }
>>>>>>> 32636d384730adeb8598ad0ba859e502432bed64

  pu_label.publish(&str_msg);
  pu_aspi.publish(&bool_msg);
  nh.spinOnce();
  delay(my_delay);

   // Peut-être ajuster ce délai en fonction des exigences de performance et de réactivité de votre application
}
