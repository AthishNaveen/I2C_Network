#include <Wire.h>
#include <Arduino.h>

void setup() {
  // Start the I2C Bus as Master
  Wire.begin(); 
  Serial.begin(9600);
}


int RxByte = 0;
void loop() {

Wire.requestFrom(0x55, 1);
  while(Wire.available()) {  // Read Received Datat From Slave Device
    RxByte = Wire.read();
  }

  Serial.print("Received Data from slave= ");
  Serial.println(RxByte);
  
  delay(500);
}