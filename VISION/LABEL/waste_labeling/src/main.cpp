// Open this file with the VScode plugin platformIO

// use commande:  rosrun rosserial_arduino make_libraries.py .
// In lib folder to get ros.h lib

#include <HUSKYLENS.h>
#include "SoftwareSerial.h"
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>


#define RELAY_ALIM 2
#define RELAY_ASPI 3

HUSKYLENS huskylens;
SoftwareSerial mySerial(10, 11); // RX, TX

ros::NodeHandle  nh;
std_msgs::String str_msg;
std_msgs::Bool bool_msg;
ros::Publisher pu_label("Label/id", &str_msg);
ros::Publisher pu_aspi("Aspi/Status", &bool_msg);
bool foundRelevantObject;

void setup() {
  str_msg.data = "NULL";
  bool_msg.data = false; 
  foundRelevantObject = false;

  Serial.begin(9600);
  mySerial.begin(9600);
  huskylens.begin(mySerial);
  //Serial.println("HuskyLens is ready.");
  nh.initNode();
  nh.advertise(pu_label);
  nh.advertise(pu_aspi);
  // Enable PIN mode for relay
  pinMode(RELAY_ALIM, OUTPUT);
  pinMode(RELAY_ASPI, OUTPUT);

  // Init relay a HIGH (off)
  digitalWrite(RELAY_ALIM, HIGH);
  digitalWrite(RELAY_ASPI, HIGH);

}
void loop() {
  if (!huskylens.request()) {
    //Serial.println("Failed to request data from HuskyLens, will retry.");
    delay(100); 
    return;
  }

   // Indicateur pour savoir si un objet pertinent a été trouvé

  if(huskylens.available()) {
    HUSKYLENSResult result = huskylens.read();

    if(result.command) {
      if (result.ID == 4) {
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
    } else {
      bool_msg.data = true;
      digitalWrite(RELAY_ALIM, LOW);
      digitalWrite(RELAY_ASPI, LOW);
    }

    pu_label.publish(&str_msg);
    pu_aspi.publish(&bool_msg);
    nh.spinOnce();
    delay(3);
  }
   // Peut-être ajuster ce délai en fonction des exigences de performance et de réactivité de votre application
}
