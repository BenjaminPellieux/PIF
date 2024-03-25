// Open this file with the VScode plugin platformIO

// use commande:  rosrun rosserial_arduino make_libraries.py .
// In lib folder to get ros.h lib

#include <HUSKYLENS.h>
#include "SoftwareSerial.h"
#include <ros.h>
#include <std_msgs/String.h>


#define RELAY_ALIM 2
#define RELAY_ASPI 3

HUSKYLENS huskylens;
SoftwareSerial mySerial(10, 11); // RX, TX
ros::NodeHandle  nh;


/*
void messageCb( const std_msgs::Empty& toggle_msg){
  // message advertise
}*/

/*
ros::Subscriber<std_msgs::Empty> sub("toggle_led", messageCb );
*/


std_msgs::String str_msg;
ros::Publisher pu_label("Label/id", &str_msg);


void setup() {
  str_msg.data = "NULL";
  
  Serial.begin(9600);
  mySerial.begin(9600);
  huskylens.begin(mySerial);
  Serial.println("HuskyLens is ready.");
  nh.initNode();
  nh.advertise(pu_label);
  // Enable PIN mode for relay
  pinMode(RELAY_ALIM, OUTPUT);
  pinMode(RELAY_ASPI, OUTPUT);

  // Init relay a HIGH (off)
  digitalWrite(RELAY_ALIM, HIGH);
  digitalWrite(RELAY_ASPI, HIGH);

}

void loop() {
  Serial.println("LOOP.");
  if (!huskylens.request()) {
    Serial.println("Failed to request data from HuskyLens, will retry.");
    delay(100);
    return;
  }

  while (huskylens.available()) {
    HUSKYLENSResult result = huskylens.read();

    if (result.command == COMMAND_RETURN_BLOCK) {
      if (result.ID == 4) {
       str_msg.data = "MEG"; 
        Serial.println("Megot de cigarette trouve!");
      }
      else if (result.ID == 3) { 
        str_msg.data = "CAP"; 
        Serial.println("Capsule de biere trouvee!");           
      }
      else{
        str_msg.data = "NULL";
      }
      pu_label.publish(&str_msg);
      nh.spinOnce();
    }
    if (str_msg.data != "NULL"){
      digitalWrite(RELAY_ALIM, LOW);
      digitalWrite(RELAY_ASPI, LOW);
    }else{  
      digitalWrite(RELAY_ALIM, HIGH);
      digitalWrite(RELAY_ASPI, HIGH);
    } 

  }
  delay(300); 
}

