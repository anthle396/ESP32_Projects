/*
  Button Interrupt ESP32 with Debouncing
  =======================================
  This program demonstrates the use of an interrupt to detect button presses and
  prints "Message received" to the serial monitor each time the button is pressed.
  
  The program includes debouncing code to ensure that only one interrupt is triggered
  for a button press, even if the button's state fluctuates due to mechanical bounce.

  Hardware Setup:
  - Button connected to GPIO pin 2
  - External pull-down resistor used to ensure the button's default state is LOW

  Author: Anthony Le
  Date: 04/03/2025
*/

#define BUTTON_PIN 32  // Button connected to GPIO pin 21
#define DEBOUNCE_TIME 5000  // Debounce time in milliseconds

volatile bool buttonPressed = false;  // Flag to indicate button press

// Interrupt service routine for the button press
void IRAM_ATTR buttonISR() {
  // Set the flag to true when the button is pressed
  buttonPressed = true;
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Configure the button pin as input with internal pull-down resistor
  pinMode(BUTTON_PIN, INPUT_PULLDOWN);

  // Attach an interrupt to the button pin
  // The interrupt will trigger on a FALLING edge (button press)
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);
}

void loop() {
  // Check if the button was pressed 
  Serial.println("Awaiting Button Input");
  delay(5000);
  if (buttonPressed) {
    // Print message when button is pressed
    Serial.println("Message received");

    // Debounce the button: wait for the specified debounce time
    delay(DEBOUNCE_TIME);

    // Reset the flag
    buttonPressed = false;
  }

  // Other program logic can go here
}
