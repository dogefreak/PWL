#include <SoftwareSerial.h>

const int hc12TX = 10;    // HC-12 TX pin
const int hc12RX = 11;    // HC-12 RX pin
const int relayPin = 12;   // Relay control pin

SoftwareSerial HC12(hc12TX, hc12RX);  // Create a SoftwareSerial object for HC-12

void turnOnRelay() {
  Serial.println("Turning ON Relay");
  digitalWrite(relayPin, LOW);  // Turn ON the relay
  delay(1000);  // Wait for 1 second
  digitalWrite(relayPin, HIGH);   // Turn OFF the relay
  Serial.println("Turning OFF Relay");
}

void setup() {
  Serial.begin(9600);
  HC12.begin(9600);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);  // Initialize relay to OFF state
}

void loop() {
  if(HC12.available()){
    String input = HC12.readString();
    Serial.println(HC12.readString());
    // delay(1000);
    if (input == "SIEBEN") {
      turnOnRelay();
    } 
  }
}
