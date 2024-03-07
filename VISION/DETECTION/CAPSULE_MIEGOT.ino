#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

HUSKYLENS huskylens;
SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  huskylens.begin(mySerial);
  Serial.println("HuskyLens is ready.");
}

void loop() {
  if (!huskylens.request()) {
    Serial.println("Failed to request data from HuskyLens, will retry.");
    delay(100);
    return;
  }

  while (huskylens.available()) {
    HUSKYLENSResult result = huskylens.read();
    if (result.command == COMMAND_RETURN_BLOCK) {
      if (result.ID == 4) { 
        Serial.println("Megot de cigarette trouve!");
      } else if (result.ID == 3) { 
        Serial.println("Capsule de biere trouvee!");
      }
    }
  }
  delay(300); 
}
