/*
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 *  The server will set a GPIO pin depending on the request
 *    http://server_ip/gpio/0 will set the GPIO2 low,
 *    http://server_ip/gpio/1 will set the GPIO2 high
 *  server_ip is the IP address of the ESP8266 module, will be 
 *  printed to Serial when the module is connected.
 */
#include <Wire.h>

unsigned int EEPROMBank = 0x50; // Base address of 1st EEPROM chip
unsigned int EEPROMAddress = 0; // Sets the start EEPROM address
unsigned int EEPROMValue = 0; // EEPROM value
byte Dummy;

#define SCLPin D5 // I2C SCL Pin
#define SDAPin D4 // I2C SDA Pin

void setup() {
 Wire.begin(SDAPin, SCLPin); // Initialize 2-Wire bus
 pinMode(D4, INPUT); // I Need to validate this line
 pinMode(D5, INPUT); // I Need to validate this line
 Serial.begin(115200); // Initialize serial port
 while(!Serial); // wait for serial
 delay(3000); // Waits 3 seconds
 Serial.println("Serial start"); // Sends preamble and Cr+Lf
 delay(3000); // Waits 3 seconds
}

void loop(){
writei2c(44); 
Serial.println("i2c send"); // Sends preamble and Cr+Lf
delay(1000);
}

void writei2c(int deviceaddress) {
 Wire.beginTransmission(deviceaddress);
 Wire.write(0x55);
 Wire.endTransmission();
 delay(5);
}

