/*
  RGB LED Control for ESP32
  ==========================
  This program demonstrates controlling an RGB LED connected to an ESP32 board. 
  It includes functions for displaying specific colors, fading through colors smoothly, 
  and basic RGB control. The program uses PWM to control the intensity of the LED colors.

  Hardware Setup:
  - Red LED connected to GPIO 13 D13
  - Green LED connected to GPIO 12 D12
  - Blue LED connected to GPIO 27 D27

  Functions:
  - toUpperCase(String &str): Converts a string to uppercase.
  - clearColor(): Turns off all LEDs.
  - displayColor(String color): Displays the selected color on the RGB LED.
  - fadeThroughColors(): Fades smoothly through different color transitions (Red, Green, Blue, and White).
  - RGB_LED_SELECT(int RED_VALUE, int GREEN_VALUE, int BLUE_VALUE): Allows manual control of RGB values.
  
  Author: [Anthony Le]
  Date: [04/03/2025]
*/

#include <stdio.h>
#include <ctype.h>

#define RED_GPIO_PORT 13
#define GREEN_GPIO_PORT 12
#define BLUE_GPIO_PORT 27
#define SEC 1000
#define LED_DELAY 0.02 * SEC
#define MIN_BRIGHTNESS 10 // Minimum brightness to avoid turning off completely
#define ARRAY_SIZE 3
#define MAX_RGB_VALUE 255
#define MIN_RGB_VALUE 0
#define LED_OFF MIN_RGB_VALUE

void toUpperCase(String &str) {
  for (int i = 0; i < str.length(); i++) {
    str[i] = toupper(str[i]);  // Apply toupper() to each character
  }
}

void clearColor(){
  // Turn off all LEDs initially
  analogWrite(RED_GPIO_PORT, LED_OFF);
  analogWrite(GREEN_GPIO_PORT, LED_OFF);
  analogWrite(BLUE_GPIO_PORT, LED_OFF);
}

void displayColor(String color) {
  // Print the selected color to the Serial Monitor
  delay(500);
  toUpperCase(color);
  Serial.print("Displaying color: ");
  Serial.println(color);

  // Display the requested color using analogWrite (PWM)
  if (color == "RED") {
    analogWrite(RED_GPIO_PORT, MAX_RGB_VALUE);  // Full intensity
    analogWrite(GREEN_GPIO_PORT, LED_OFF);
    analogWrite(BLUE_GPIO_PORT, LED_OFF);
  } else if (color == "GREEN") {
    analogWrite(RED_GPIO_PORT, LED_OFF);
    analogWrite(GREEN_GPIO_PORT, MAX_RGB_VALUE);  // Full intensity
    analogWrite(BLUE_GPIO_PORT, LED_OFF);
  } else if (color == "YELLOW") {
    analogWrite(RED_GPIO_PORT, MAX_RGB_VALUE);  // Full intensity
    analogWrite(GREEN_GPIO_PORT, MAX_RGB_VALUE);  // Full intensity
    analogWrite(BLUE_GPIO_PORT, LED_OFF);
  } else if (color == "BLUE") {
    analogWrite(RED_GPIO_PORT, LED_OFF);
    analogWrite(GREEN_GPIO_PORT, LED_OFF);
    analogWrite(BLUE_GPIO_PORT, MAX_RGB_VALUE);  // Full intensity
  } else if (color == "PURPLE") {
    analogWrite(RED_GPIO_PORT, MAX_RGB_VALUE);  // Full intensity
    analogWrite(GREEN_GPIO_PORT, LED_OFF);
    analogWrite(BLUE_GPIO_PORT, MAX_RGB_VALUE);  // Full intensity
  } else if (color == "TEAL") {
    analogWrite(RED_GPIO_PORT, LED_OFF);
    analogWrite(GREEN_GPIO_PORT, MAX_RGB_VALUE);  // Full intensity
    analogWrite(BLUE_GPIO_PORT, MAX_RGB_VALUE);  // Full intensity
  } else if (color == "WHITE") {
    analogWrite(RED_GPIO_PORT, MAX_RGB_VALUE);  // Full intensity
    analogWrite(GREEN_GPIO_PORT, MAX_RGB_VALUE);  // Full intensity
    analogWrite(BLUE_GPIO_PORT, MAX_RGB_VALUE);  // Full intensity
  }
}

void fadeThroughColors() {
  // Fade through the colors smoothly
  
  // Red to Green fade
  for (int i = MIN_BRIGHTNESS; i <= MAX_RGB_VALUE; i++) {
    analogWrite(RED_GPIO_PORT, MAX_RGB_VALUE - i);  // Decrease Red
    analogWrite(GREEN_GPIO_PORT, i);      // Increase Green
    analogWrite(BLUE_GPIO_PORT, MIN_BRIGHTNESS);  // Blue at minimum brightness
    delay(LED_DELAY);  // Adjust the fade speed
  }

  // Green to Blue fade
  for (int i = MIN_BRIGHTNESS; i <= MAX_RGB_VALUE; i++) {
    analogWrite(RED_GPIO_PORT, MIN_BRIGHTNESS);  // Red at minimum brightness
    analogWrite(GREEN_GPIO_PORT, MAX_RGB_VALUE - i);      // Decrease Green
    analogWrite(BLUE_GPIO_PORT, i);             // Increase Blue
    delay(LED_DELAY);  // Adjust the fade speed
  }

  // Blue to Red fade
  for (int i = MIN_BRIGHTNESS; i <= MAX_RGB_VALUE; i++) {
    analogWrite(RED_GPIO_PORT, i);        // Increase Red
    analogWrite(GREEN_GPIO_PORT, MIN_BRIGHTNESS);  // Green at minimum brightness
    analogWrite(BLUE_GPIO_PORT, MAX_RGB_VALUE - i); // Decrease Blue
    delay(LED_DELAY);  // Adjust the fade speed
  }

  // Red, Green, Blue combined (White)
  for (int i = MIN_BRIGHTNESS; i <= MAX_RGB_VALUE; i++) {
    analogWrite(RED_GPIO_PORT, i);        // Increase Red
    analogWrite(GREEN_GPIO_PORT, i);      // Increase Green
    analogWrite(BLUE_GPIO_PORT, i);       // Increase Blue
    delay(LED_DELAY);  // Adjust the fade speed
  }

  // Fade from White to Red, Green, Blue smoothly
  for (int i = MAX_RGB_VALUE; i >= MIN_BRIGHTNESS; i--) {
    analogWrite(RED_GPIO_PORT, i);        // Decrease Red
    analogWrite(GREEN_GPIO_PORT, i);      // Decrease Green
    analogWrite(BLUE_GPIO_PORT, i);       // Decrease Blue
    delay(LED_DELAY);  // Adjust the fade speed
  }
}

// void colorFlash(int RGB_Value) {
//      // Fade from White to Red, Green, Blue smoothly
//      if(RGB_Value >)
//     analogWrite(RED_GPIO_PORT, i);        // Decrease Red
//     analogWrite(GREEN_GPIO_PORT, i);      // Decrease Green
//     analogWrite(BLUE_GPIO_PORT, i);       // Decrease Blue
//     delay(LED_DELAY);  // Adjust the fade speed
//   }
// }

void RGB_LED_SELECT(int RED_VALUE, int GREEN_VALUE, int BLUE_VALUE) {
  analogWrite(RED_GPIO_PORT, RED_VALUE);        // Decrease Red
  analogWrite(GREEN_GPIO_PORT, GREEN_VALUE);      // Decrease Green
  analogWrite(BLUE_GPIO_PORT, BLUE_VALUE);       // Decrease Blue
  delay(LED_DELAY);  // Adjust the fade speed
}
int values[ARRAY_SIZE] = {0, 0, 0};  // Initialize RGB values to whatever custom number you want

void setup() {
  // Start serial communication
  Serial.begin(115200);  // Adjust baud rate as necessary
  
  // Set GPIOs as output
  pinMode(RED_GPIO_PORT, OUTPUT);
  pinMode(GREEN_GPIO_PORT, OUTPUT);
  pinMode(BLUE_GPIO_PORT, OUTPUT);

}

void loop() {
    //RGB_LED_SELECT(values[0], values[1], values[2]);
    //displayColor("YELLOW");
    fadeThroughColors();
}