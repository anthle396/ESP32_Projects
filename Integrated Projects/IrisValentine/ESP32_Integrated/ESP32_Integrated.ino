/*
 * Project: ESP32 RGB LED Controller + TFT Display + Buzzer (Note Player)
 * Author: Anthony Le
 * Description:
 *    - Controls an RGB LED using PWM and displays colors
 *    - Fades through RGB colors smoothly
 *    - Plays musical notes through a buzzer
 *    - Displays output on TFT screen
 *    - Button press triggers events (using interrupt)
 * 
 * Hardware Connections:
 *    - RGB LED: GPIO 12 (Green), GPIO 13 (Red), GPIO 27 (Blue)
 *    - Speaker: GPIO 21
 *    - Button: GPIO 32
 *    - TFT Display: CS=17, DC=4, RST=16
 * 
 *    Note: the green led doesn't work since I accidently yanked it but the code works fine.
 * Libraries:
 *    - SPI.h, Adafruit_GFX.h, TFT_ILI9163C.h
 * 
 * Last Modified: 04/28/2025
 */

#include <SPI.h>                 
#include <Adafruit_GFX.h>        
#include <TFT_ILI9163C.h> 
#include <stdio.h>
#include <ctype.h>

// ============================ Pin Definitions ============================
#define BUTTON_PIN        32    // Button GPIO
#define RED_GPIO_PORT     13    // Red LED GPIO
#define GREEN_GPIO_PORT   12    // Green LED GPIO
#define BLUE_GPIO_PORT    27    // Blue LED GPIO
#define SPEAKER_PIN       21    // Speaker GPIO

// TFT Display Pins
#define __CS              17    
#define __DC              4    
#define __RST             16    

// ============================ Constants ============================
#define DEBOUNCE_TIME     500  // Button debounce time (ms)
#define TIME              2     // Generic delay time (s)
#define SEC               1000  // 1 second (ms)
#define LED_DELAY         (0.02 * SEC) // LED fade delay
#define MIN_BRIGHTNESS    10    // Minimum brightness
#define ARRAY_SIZE        3     
#define MAX_RGB_VALUE     255   
#define MIN_RGB_VALUE     0     
#define LED_OFF           MIN_RGB_VALUE

// Color Definitions (16-bit RGB)
#define BLACK             0x0000
#define BLUE              0x001F
#define RED               0xF800
#define GREEN             0x07E0
#define CYAN              0x07FF
#define MAGENTA           0xF81F
#define YELLOW            0xFFE0
#define WHITE             0xFFFF
// ============================ Enumerations ============================
// Musical note frequencies
enum Note {
  C0_ = 16,     C0S_ = 17,     D0_ = 18,     D0S_ = 19,     E0_ = 20,
  F0_ = 21,     F0S_ = 23,     G0_ = 24,     G0S_ = 25,     A0_ = 27,
  A0S_ = 29,     B0_ = 30,
  
  C1_ = 33,     C1S_ = 35,     D1_ = 37,     D1S_ = 39,     E1_ = 41,
  F1_ = 44,     F1S_ = 46,     G1_ = 49,     G1S_ = 52,     A1_ = 55,
  A1S_ = 58,     B1_ = 62,

  C2_ = 65,     C2S_ = 69,     D2_ = 73,     D2S_ = 78,     E2_ = 82,
  F2_ = 87,     F2S_ = 93,     G2_ = 98,     G2S_ = 104,    A2_ = 110,
  A2S_ = 117,    B2_ = 123,

  C3_ = 130,    C3S_ = 138,    D3_ = 146,    D3S_ = 155,    E3_ = 164,
  F3_ = 174,    F3S_ = 185,    G3_ = 196,    G3S_ = 208,    A3_ = 220,
  A3S_ = 233,    B3_ = 247,

  C4_ = 262,    C4S_ = 277,    D4_ = 294,    D4S_ = 311,    E4_ = 330,
  F4_ = 349,    F4S_ = 370,    G4_ = 392,    G4S_ = 415,    A4_ = 440,
  A4S_ = 466,    B4_ = 494,

  C5_ = 523,    C5S_ = 554,    D5_ = 587,    D5S_ = 622,    E5_ = 659,
  F5_ = 698,    F5S_ = 740,    G5_ = 784,    G5S_ = 831,    A5_ = 880,
  A5S_ = 932,    B5_ = 988,

  C6_ = 1047,   C6S_ = 1109,   D6_ = 1175,   D6S_ = 1245,   E6_ = 1319,
  F6_ = 1397,   F6S_ = 1480,   G6_ = 1568,   G6S_ = 1661,   A6_ = 1760,
  A6S_ = 1865,   B6_ = 1976,

  C7_ = 2093,   C7S_ = 2218,   D7_ = 2349,   D7S_ = 2489,   E7_ = 2637,
  F7_ = 2794,   F7S_ = 2960,   G7_ = 3136,   G7S_ = 3322,   A7_ = 3520,
  A7S_ = 3729,   B7_ = 3951,

  C8_ = 4186,   C8S_ = 4435,   D8_ = 4699,   D8S_ = 4978,   E8_ = 5274,
  F8_ = 5588,   F8S_ = 5920,   G8_ = 6272,   G8S_ = 6645,   A8_ = 7040,
  A8S_ = 7458,   B8_ = 7902,

  REST = 0
};

// ============================ Function Prototypes ============================
void playNote(Note note, int duration);
Note parseNote(String input);
void playSong(Note* song, int songLength);
void IRAM_ATTR buttonISR();
void toUpperCase(String &str);
void clearColor();
void displayColor(String color);
void fadeThroughColors();
void RGB_LED_SELECT(int RED_VALUE, int GREEN_VALUE, int BLUE_VALUE);

// ============================ Global Variables ============================
volatile bool buttonPressed = false;  // Button flag
TFT_ILI9163C tft(__CS, __DC, __RST);  // TFT display object
int values[ARRAY_SIZE] = {0, 0, 0};   // RGB values array
const int speakerPin = 21;            // Speaker pin

// Interrupt service routine for the button press
void IRAM_ATTR buttonISR() {
  // Set the flag to true when the button is pressed
  buttonPressed = true;
}

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
  } else if (color == "MAGENTA") {
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

void RGB_LED_SELECT(int RED_VALUE, int GREEN_VALUE, int BLUE_VALUE) {
  analogWrite(RED_GPIO_PORT, RED_VALUE);        // Decrease Red
  analogWrite(GREEN_GPIO_PORT, GREEN_VALUE);      // Decrease Green
  analogWrite(BLUE_GPIO_PORT, BLUE_VALUE);       // Decrease Blue
  delay(LED_DELAY);  // Adjust the fade speed
}


void playNote(Note note, int duration) {
  if (note != REST) {
    tone(speakerPin, note, duration);
  }
  delay(duration + 50);
}

Note parseNote(String input) {
  input.toUpperCase();

  // C notes
  if (input == "C0") return C0_;
  if (input == "C0#") return C0S_;
  if (input == "C1") return C1_;
  if (input == "C1#") return C1S_;
  if (input == "C2") return C2_;
  if (input == "C2#") return C2S_;
  if (input == "C3") return C3_;
  if (input == "C3#") return C3S_;
  if (input == "C4") return C4_;
  if (input == "C4#") return C4S_;
  if (input == "C5") return C5_;
  if (input == "C5#") return C5S_;
  if (input == "C6") return C6_;
  if (input == "C6#") return C6S_;
  if (input == "C7") return C7_;
  if (input == "C7#") return C7S_;
  if (input == "C8") return C8_;

  // D notes
  if (input == "D0") return D0_;
  if (input == "D0#") return D0S_;
  if (input == "D1") return D1_;
  if (input == "D1#") return D1S_;
  if (input == "D2") return D2_;
  if (input == "D2#") return D2S_;
  if (input == "D3") return D3_;
  if (input == "D3#") return D3S_;
  if (input == "D4") return D4_;
  if (input == "D4#") return D4S_;
  if (input == "D5") return D5_;
  if (input == "D5#") return D5S_;
  if (input == "D6") return D6_;
  if (input == "D6#") return D6S_;
  if (input == "D7") return D7_;
  if (input == "D7#") return D7S_;
  if (input == "D8") return D8_;

  // E notes
  if (input == "E0") return E0_;
  if (input == "E1") return E1_;
  if (input == "E2") return E2_;
  if (input == "E3") return E3_;
  if (input == "E4") return E4_;
  if (input == "E5") return E5_;
  if (input == "E6") return E6_;
  if (input == "E7") return E7_;
  if (input == "E8") return E8_;

  // F notes
  if (input == "F0") return F0_;
  if (input == "F0#") return F0S_;
  if (input == "F1") return F1_;
  if (input == "F1#") return F1S_;
  if (input == "F2") return F2_;
  if (input == "F2#") return F2S_;
  if (input == "F3") return F3_;
  if (input == "F3#") return F3S_;
  if (input == "F4") return F4_;
  if (input == "F4#") return F4S_;
  if (input == "F5") return F5_;
  if (input == "F5#") return F5S_;
  if (input == "F6") return F6_;
  if (input == "F6#") return F6S_;
  if (input == "F7") return F7_;
  if (input == "F7#") return F7S_;
  if (input == "F8") return F8_;

  // G notes
  if (input == "G0") return G0_;
  if (input == "G0#") return G0S_;
  if (input == "G1") return G1_;
  if (input == "G1#") return G1S_;
  if (input == "G2") return G2_;
  if (input == "G2#") return G2S_;
  if (input == "G3") return G3_;
  if (input == "G3#") return G3S_;
  if (input == "G4") return G4_;
  if (input == "G4#") return G4S_;
  if (input == "G5") return G5_;
  if (input == "G5#") return G5S_;
  if (input == "G6") return G6_;
  if (input == "G6#") return G6S_;
  if (input == "G7") return G7_;
  if (input == "G7#") return G7S_;
  if (input == "G8") return G8_;

  // A notes
  if (input == "A0") return A0_;
  if (input == "A0#") return A0S_;
  if (input == "A1") return A1_;
  if (input == "A1#") return A1S_;
  if (input == "A2") return A2_;
  if (input == "A2#") return A2S_;
  if (input == "A3") return A3_;
  if (input == "A3#") return A3S_;
  if (input == "A4") return A4_;
  if (input == "A4#") return A4S_;
  if (input == "A5") return A5_;
  if (input == "A5#") return A5S_;
  if (input == "A6") return A6_;
  if (input == "A6#") return A6S_;
  if (input == "A7") return A7_;
  if (input == "A7#") return A7S_;
  if (input == "A8") return A8_;

  // B notes
  if (input == "B0") return B0_;
  if (input == "B1") return B1_;
  if (input == "B2") return B2_;
  if (input == "B3") return B3_;
  if (input == "B4") return B4_;
  if (input == "B5") return B5_;
  if (input == "B6") return B6_;
  if (input == "B7") return B7_;
  if (input == "B8") return B8_;

  return REST;
}

// SONG
Note melody[] = {
  // Intro: 
  C4_, C4S_, C4_, C4S_, C4_, C4S_, 
  E4_, D4S_, C4S_,
  C4_, C4S_, C4_, C4S_, C4_, C4S_, 
  E4_, D4S_, C4S_, 
  C4_, C4S_, C4_, C4S_, E4_, 

  // Chorus: "I love you baby"
  G5S_, G5S_, G5S_, G5S_, C5S_, 
  // "And if it's quite alright "
  D5S_, E5_, F5S_, G5S_, G5S_,  F5S_,
  // "I need you, Baby"
  E5_, D5S_, E5_, F5S_, F5S_,
  // "To warm the lonely nights"
  E5_, D5S_, E5_, F5S_, F5S_, E5_,

  // "I love you baby..."
  E5_, D5S_, C5S_, E5_, A4_,
  // "Trust in me why I say"
  E5_, E5_, D5S_, C5S_, D5S_, D5S_,
  
  // "Oh pretty baby" 
  G5S_, G5S_, G5S_, G5S_, C5S_, 
  // "Dont bring me down I pray"
  D5S_, E5_, F5S_, G5S_, G5S_, B5_,
  
  // "Oh pretty baby,"
  G5S_, F5S_, E5_, F5S_, B4_, 

  // "now that I found you, stay" 
  C5S_, D5S_, E5_, F5S_, F5S_, E5_,
  
  // "And let me love you, baby"
  E5_, D5S_, C5S_, E5_, F5S_, C5S_, D5S_,
  // "Let me love you"
  E5_, C5S_, E5_, F5S_, F5_
};

float noteDurations[] = {
  // Intro: 
  2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 
  2.5, 2.5, 2.5,
  2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 
  2.5, 2.5, 2.5, 
  2.5, 2.5, 2.5, 2.5, 2.5,  

  // Chorus: "I love you baby"
  2.5, 2.5, 2.5, 2.5, 2.5, 
  // "And if it's quite alright "
  2.5, 2.5, 2.5, 2.5, 2.5, 2.5,
  // "I need you, Baby"
  2.5, 2.5, 2.5, 2.5, 2.5,
  // "To warm the lonely nights"
  2.5, 2.5, 2.5, 2.5, 2.5, 2.5,

  // "I love you baby..."
  2.5, 2.5, 2.5, 2.5, 2.5,
  // "Trust in me why I say"
  2.5, 2.5, 2.5, 2.5, 2.5, 2.5,

  // "Oh pretty baby" 
  2.5, 2.5, 2.5, 2.5, 2.5,
  // "Dont bring me down I pray"
  2.5, 2.5, 2.5, 2.5, 2.5, 2.5,

  // "Oh pretty baby,"
  2.5, 2.5, 2.5, 2.5, 2.5,

  // "now that I found you, stay" 
  2.5, 2.5, 2.5, 2.5, 2.5, 2.5,

  // "And let me love you, baby"
  2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5,
  // "Let me love you"
  2.5, 2.5, 2.5, 2.5, 2.5
};


void PlayThis(void) {
  int length = sizeof(melody) / sizeof(melody[0]);
  for (int i = 0; i < length; i++) {
    float duration = 1000.0 / noteDurations[i];
    if (melody[i] == REST) {
      delay(duration);  // Rest: just wait
    } else {
      tone(speakerPin, melody[i], duration);
      delay(duration * 1.3);  // Add a bit of spacing between notes
      noTone(speakerPin);    // Stop the tone before the next
    }
  }
}

// void PlayTest(void){
//   static String inputBuffer = "";
//   while (Serial.available()) {
//     char c = Serial.read();
//     if (c == '\n' || c == '\r') {
//       if (inputBuffer.length() > 0) {
//         Note n = parseNote(inputBuffer);
//         if (n != REST) {
//           playNote(n, 500);
//           Serial.print("Playing note: ");
//           Serial.println(inputBuffer);
//         } else {
//           Serial.print("Invalid input: ");
//           Serial.println(inputBuffer);
//         }
//         inputBuffer = "";  // clear for next input
//       }
//     } else {
//       inputBuffer += c;
//     }
//   }
// }

// /**
//  * @brief Displays a specified color on the TFT screen.
//  * 
//  * @param colorName Name of the color to display (e.g., "Red").
//  * @param bgColor Background color to fill the screen.
//  * @param textColor Text color to use for the label.
//  */
// void displayColor(const char* colorName, uint16_t bgColor, uint16_t textColor) {
//   Serial.printf("%s.\n", colorName); // Print color name to Serial Monitor
//   tft.fillScreen(bgColor);           // Fill the screen with the specified background color
//   tft.setTextColor(textColor);       // Set the text color
//   tft.setCursor(10, 30);             // Position the cursor for text display
//   tft.println(colorName);            // Print the color name on the screen
//   delay(TIME * 1000);                // Pause for the specified duration
// }

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Configure the button pin as input with internal pull-down resistor
  pinMode(BUTTON_PIN, INPUT_PULLDOWN);
  pinMode(speakerPin, OUTPUT);

  Serial.println("Booting up Display Program...\n");
  // Serial.print("CS = ");
  // Serial.print(__CS);
  // Serial.println(" Pin\n");

  // Serial.print("A0 = ");
  // Serial.print(__DC);
  // Serial.println(" Pin\n");

  // Serial.print("RST = ");
  // Serial.print(__RST);
  // Serial.println(" Pin\n");

  // Initialize the TFT display
  tft.begin();
  tft.setRotation(2);          // Adjust the screen orientation
  tft.setTextSize(2);          // Set the text size to medium
  tft.setCursor(10, 30);       // Set cursor position (x=10, y=30)
  tft.fillScreen(BLACK);       // Set the initial background color to black
  tft.setTextColor(WHITE);     // Set the text color to white
  tft.println("Booting \n Up...\n"); // Print "Hello World" on the TFT screen
  
  // Display "Hello World" message
  
  delay(5000);
  
  // Attach an interrupt to the button pin
  // The interrupt will trigger on a FALLING edge (button press)
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);
}

void loop() {
  // Check if the button was pressed 
  // Serial.println("Awaiting Button Input");
  
  tft.setRotation(2);          // Adjust the screen orientation
  tft.setTextSize(2);          // Set the text size to medium
  tft.setCursor(10, 10);       // Set cursor position (x=10, y=30)
  tft.fillScreen(BLACK);       // Set the initial background color to black
  tft.setTextColor(YELLOW);     // Set the text color to white
  tft.println("WAIT! \n Look At \n The \n Cool \n Heart \n <-----\n");
  delay(2000);
  fadeThroughColors();
  if(buttonPressed) {
    buttonPressed = false;
  }
  tft.fillScreen(BLACK);       // Set the initial background color to black
  tft.setTextColor(GREEN);     // Set the text color to white
  tft.setRotation(2);          // Adjust the screen orientation
  tft.setTextSize(2);          // Set the text size to medium
  tft.setCursor(10, 20);       // Set cursor position (x=10, y=30)
  tft.println("Press The \n Button \n To \n Continue\n ...\n");

  while(!buttonPressed){
    // do nothing until button pressed
    if (buttonPressed){
      break;
    }
  }

  if (buttonPressed) {
    displayColor("PURPLE");
    // Print message when button is pressed
    Serial.println("Button Pressed");
    tft.fillScreen(BLACK);       // Set the initial background color to black
    tft.setTextColor(RED);     // Set the text color to white
    tft.setRotation(2);          // Adjust the screen orientation
    tft.setTextSize(2);          // Set the text size to medium
    tft.setCursor(10, 30);       // Set cursor position (x=10, y=30)
    tft.println(" \n Loving \n Iris \n Please \n Hold...\n");
    
    delay(500);
    
    tft.fillScreen(BLACK);       // Set the initial background color to black
    tft.setTextColor(MAGENTA);     // Set the text color to white
    tft.setRotation(2);          // Adjust the screen orientation
    tft.setTextSize(2);          // Set the text size to medium
    tft.setCursor(10, 30);       // Set cursor position (x=10, y=30)
    tft.println(" Loving \n Iris \n Please \n Hold...\n");
    delay(500);

    tft.fillScreen(BLACK);       // Set the initial background color to black
    tft.setTextColor(BLUE);     // Set the text color to white
    tft.setRotation(2);          // Adjust the screen orientation
    tft.setTextSize(2);          // Set the text size to medium
    tft.setCursor(10, 30);       // Set cursor position (x=10, y=30)
    tft.println("Loving \n Iris \n Please \n Hold...\n");
    delay(500);

    tft.fillScreen(BLACK);       // Set the initial background color to black
    tft.setTextColor(CYAN);     // Set the text color to white
    tft.setRotation(2);          // Adjust the screen orientation
    tft.setTextSize(2);          // Set the text size to medium
    tft.setCursor(10, 30);       // Set cursor position (x=10, y=30)
    tft.println("Loving \n Iris \n Please \n Hold...\n");
    delay(500);

    tft.fillScreen(BLACK);       // Set the initial background color to black
    tft.setTextColor(GREEN);     // Set the text color to white
    tft.setRotation(2);          // Adjust the screen orientation
    tft.setTextSize(2);          // Set the text size to medium
    tft.setCursor(10, 30);       // Set cursor position (x=10, y=30)
    tft.println("Loving \n Iris \n Please \n Hold...\n");
    delay(500);
    // Debounce the button: wait for the specified debounce time
    delay(DEBOUNCE_TIME);
    PlayThis();

    

    // Reset the flag
    buttonPressed = false;

    tft.fillScreen(BLACK);       // Set the initial background color to black
    tft.setTextColor(WHITE);     // Set the text color to white
    tft.setRotation(2);          // Adjust the screen orientation
    tft.setTextSize(1);          // Set the text size to medium
    tft.setCursor(10, 30);       // Set cursor position (x=10, y=30)
    tft.println("Happy 2 \n Year \n Anniversary \n Iris! \n");
    delay(10000);

    tft.fillScreen(BLACK);       // Set the initial background color to black
    tft.setTextColor(WHITE);     // Set the text color to white
    tft.setRotation(2);          // Adjust the screen orientation
    tft.setTextSize(1);          // Set the text size to medium
    tft.setCursor(10, 30);       // Set cursor position (x=10, y=30)
    tft.println("Here's to many \n more years of \n loving you \n endlessly! \n");
    delay(10000);
    clearColor();
  }

  tft.fillScreen(BLACK);       // Set the initial background color to black
  tft.setTextColor(WHITE);     // Set the text color to white
  tft.setRotation(2);          // Adjust the screen orientation
  tft.setTextSize(2);          // Set the text size to medium
  tft.setCursor(10, 30);       // Set cursor position (x=10, y=30)
  tft.println("Press \n to Reset. \n");
  delay(10000);
  if (buttonPressed){
      buttonPressed = false;
  }

  while(!buttonPressed)
  {
    if (buttonPressed){
      buttonPressed = false;
    }
  }
  buttonPressed = false;
  // Other program logic can go here
}
