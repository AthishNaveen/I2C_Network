#include <Wire.h>
#include <Arduino.h>
uint8_t i2cAddress = 0x44; // Default I2C address

String receivedString = ""; // Variable to store the received string

// Function that runs when data is received from the master
void receiveEvent(int bytesReceived) {
  receivedString = ""; // Clear the string

  // Read each byte and append to the receivedString
  while (Wire.available() > 0) {
    char c = Wire.read(); 
    receivedString += c;
  }
  Serial.print("At Interrupt:");
  Serial.println(receivedString);
}


void setup() {
  // Start the I2C Bus as Master
  Wire.begin(0x55); 
  Serial.begin(9600);
  Wire.onReceive(receiveEvent);
}

String message = "";

void loop() {
     if (Serial.available()) {
        char receivedChar = Serial.read();
        message = "";

        // Keep reading until we reach a newline character
        while (receivedChar != '\n') {
            message += receivedChar;
            if (Serial.available()) {
                receivedChar = Serial.read();
            } else {
                break;
            }
        }
            // Print the received string
    Serial.print("Message: ");
    Serial.println(message);
    }

    // Process the message to change I2C address if specific characters are detected
    if (message == "2") {
      i2cAddress = 0x22;
    } else if (message == "3") {
      i2cAddress = 0x33;
    } else if (message == "4") {
      i2cAddress = 0x44;
    } else if (message == "5") {
      i2cAddress = 0x55;
    }


  if (message.length() > 0) {
    Wire.beginTransmission(i2cAddress);
    Wire.write(message.c_str(), message.length());

    Wire.endTransmission();
        Serial.print("Sent to ");
    Serial.print(i2cAddress, HEX);
    Serial.print(":");
    Serial.println(message);
    message = "";
  }

    // Print the received string when fully received
    if (receivedString.length() > 0) {
      Serial.println("Received: " + receivedString);
      receivedString = ""; // Clear the string for the next message
    }


}