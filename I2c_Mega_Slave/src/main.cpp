#include <Wire.h>
#include <Arduino.h>

int num = 99;
// Include the required Wire library for I2C<br>#include <Wire.h>
int LED = 13;
int x = 0;

void sendEvent(){
 Serial.println("request raised");
  Wire.write(num);
}

void setup() {
  // Define the LED pin as Output
  pinMode (LED, OUTPUT);
  // Start the I2C Bus as Slave on address 9
  Wire.begin(0x55); 

   Wire.onRequest(sendEvent);
  Serial.begin(9600);
}

void loop() {
  delay(1000);
  num = num + 1;

}