// #include <Arduino.h>
// #include "Note_Frequencies.h"  // Include your frequencies struct

// const int speakerPin = 21;  // Define the pin connected to your speaker

// void setup() {
//     Serial.begin(115200);
//     pinMode(speakerPin, OUTPUT);
//     // Play the NONE frequency (no sound)
//     analogWrite(speakerPin, 0);
// }

// void loop() {
//   printf("Playing Audio\n");
//   delay(5000);

//   // Play the C1 note (32.7032 Hz)
//     //analogWrite(speakerPin, 127);
//     delay(500);  // Wait for 1 second
//     //analogWrite(speakerPin, 200);
//     delay(1000);  // Wait for 1 second
//     analogWrite(speakerPin, 0);
//     delay(5000);
// }

// const int pwmPin = 21;  // PWM output pin
// const int frequency = 1000;  // Frequency of the sine wave in Hz
// const int amplitude = 128;   // Half of the max value (255) for the sine wave amplitude
// const int offset = 128;      // Center point (half of 255)
// const int samples = 255;     // Number of samples per cycle

// void setup() {
//   pinMode(pwmPin, OUTPUT);  // Set the pin as an output
// }

// void loop() {
//   for (int i = 0; i < samples; i++) {
//     // Calculate the sine wave value
//     float sineValue = sin(TWO_PI * i / samples);
    
//     // Map the sine value to the range of 0-255 for analogWrite
//     int pwmValue = (int)(sineValue * amplitude + offset);
    
//     // Output the PWM value
//     analogWrite(pwmPin, pwmValue);

//     // Delay to control the frequency of the sine wave
//     delayMicroseconds(1000000 / frequency / samples);  // Calculate delay based on the frequency
//   }
// }

// Define a struct to store the note name and frequency
struct Note {
  const char* name;  // Name of the note
  int frequency;     // Frequency of the note in Hz
};

// Array of Note structs with name and frequency
Note notes[] = {
  {"C4", 262}, 
  {"C#4", 277}, 
  {"D4", 294}, 
  {"D#4", 311}, 
  {"E4", 330}, 
  {"F4", 349}, 
  {"F#4", 370}, 
  {"G4", 392}, 
  {"G#4", 415}, 
  {"A4", 440}, 
  {"A#4", 466}, 
  {"B4", 494}, 
  {"C5", 523}, 
  {"C#5", 554}, 
  {"D5", 587}, 
  {"D#5", 622}, 
  {"E5", 659}, 
  {"F5", 698}, 
  {"F#5", 740}, 
  {"G5", 784}
};

// Pin connected to the buzzer or speaker
const int speakerPin = 21;

void setup() {
  // Set up the speaker pin as an output
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  // Iterate through all the notes
  for (int i = 0; i < 20; i++) {
    // Print the note name to the Serial Monitor
    Serial.print("Playing: ");
    Serial.println(notes[i].name);
    
    // Generate the tone for the current note
    tone(speakerPin, notes[i].frequency, 400);  // 400 ms per note
    delay(500); // Wait for the note to finish before playing the next
  }

  // Optional: Pause for a moment after the full loop
  delay(1000);  // Pause for 1 second before restarting the loop
}

