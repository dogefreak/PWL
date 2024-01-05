#include <SoftwareSerial.h>

// Pin configurations
const int buttonPin = 12;  // Button pin with pull-up resistor
const int hc12TX = 10;    // HC-12 TX pin
const int hc12RX = 11;    // HC-12 RX pin

// Variables
int buttonState = HIGH;    // Current state of the button
int lastButtonState = HIGH;  // Previous state of the button
unsigned long lastDebounceTime = 0;  // Last time the button was debounced
unsigned long debounceDelay = 50;    // Debounce time in milliseconds

SoftwareSerial hc12(hc12TX, hc12RX);  // Create a SoftwareSerial object for HC-12

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  hc12.begin(9600);  // HC-12 default baud rate
  Serial.begin(9600);
}

void loop() {
  // Read the state of the button
  int reading = digitalRead(buttonPin);

  // Perform debounce
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Update the button state if the debounce delay has passed
    if (reading != buttonState) {
      buttonState = reading;

      // If the button is pressed (LOW), transmit a serial signal
      if (buttonState == LOW) {
        Serial.println("Button pressed & MSG SENT");
        hc12.write("SIEBEN");;  // Transmit data via HC-12
        // delay(1000);  // Delay to avoid repeated transmissions
      }
    }
  }

  // Save the current button state for the next iteration
  lastButtonState = reading;
}
