#include <Wire.h>
#include <Arduino.h>

void setup() {
  Wire.begin(0x44);
  Serial.begin(9600);
}
 
String receivedString = "";

int RxByte = 0;
void loop() {
    if (Serial.available()) {
        char receivedChar = Serial.read();
        receivedString = "";

        // Keep reading until we reach a newline character
        while (receivedChar != '\n') {
            receivedString += receivedChar;
            if (Serial.available()) {
                receivedChar = Serial.read();
            } else {
                break;
            }
        }
            // Print the received string
    Serial.print("Received string: ");
    Serial.println(receivedString);
    }

    delay(500);
    Wire.beginTransmission(0x55);
    Wire.write(receivedString.c_str(), receivedString.length());
    Serial.println("Sent data to slave");
    Wire.endTransmission();

  delay(500);
}