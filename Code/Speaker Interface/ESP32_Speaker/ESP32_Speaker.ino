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

// // Define a struct to store the note name and frequency
// struct Note {
//   const char* name;  // Name of the note
//   int frequency;     // Frequency of the note in Hz
// };

// // Array of Note structs with name and frequency
// Note notes[] = {
//   {"C4", 262}, 
//   {"C#4", 277}, 
//   {"D4", 294}, 
//   {"D#4", 311}, 
//   {"E4", 330}, 
//   {"F4", 349}, 
//   {"F#4", 370}, 
//   {"G4", 392}, 
//   {"G#4", 415}, 
//   {"A4", 440}, 
//   {"A#4", 466}, 
//   {"B4", 494}, 
//   {"C5", 523}, 
//   {"C#5", 554}, 
//   {"D5", 587}, 
//   {"D#5", 622}, 
//   {"E5", 659}, 
//   {"F5", 698}, 
//   {"F#5", 740}, 
//   {"G5", 784}
// };

// // Pin connected to the buzzer or speaker
// const int speakerPin = 21;

// void setup() {
//   // Set up the speaker pin as an output
//   pinMode(speakerPin, OUTPUT);
// }

// void loop() {
//   // Iterate through all the notes
//   for (int i = 0; i < 20; i++) {
//     // Print the note name to the Serial Monitor
//     Serial.print("Playing: ");
//     Serial.println(notes[i].name);
    
//     // Generate the tone for the current note
//     tone(speakerPin, notes[i].frequency, 400);  // 400 ms per note
//     delay(500); // Wait for the note to finish before playing the next
//   }

//   // Optional: Pause for a moment after the full loop
//   delay(1000);  // Pause for 1 second before restarting the loop
// }

/*
 * Happy Birthday Melody for Arduino
 * Author: Anthony Le
 * Date: 2025-04-04
 * Description: This program plays the "Happy Birthday" song on a buzzer using predefined note frequencies.
 * The frequencies are based on the standard pitch notation (A4 = 440 Hz).
 * Notes are represented by their names, and each note's corresponding frequency is mapped in the code.
 */

// Define a struct to store the note name and frequency
struct Note {
  const char* name;  // Name of the note (e.g., C4, D4, etc.)
  int frequency;     // Frequency of the note in Hz (standard pitch notation)
};

// Array of Note structs with name and frequency
Note notes[] = {
  {"C4", 262},    // C4 (Middle C) = 262 Hz
  {"C#4", 277},   // C#4 = 277 Hz
  {"D4", 294},    // D4 = 294 Hz
  {"D#4", 311},   // D#4 = 311 Hz
  {"E4", 330},    // E4 = 330 Hz
  {"F4", 349},    // F4 = 349 Hz
  {"F#4", 370},   // F#4 = 370 Hz
  {"G4", 392},    // G4 = 392 Hz
  {"G#4", 415},   // G#4 = 415 Hz
  {"A4", 440},    // A4 (Standard Pitch) = 440 Hz
  {"A#4", 466},   // A#4 = 466 Hz
  {"B4", 494},    // B4 = 494 Hz
  {"C5", 523},    // C5 = 523 Hz
  {"C#5", 554},   // C#5 = 554 Hz
  {"D5", 587},    // D5 = 587 Hz
  {"D#5", 622},   // D#5 = 622 Hz
  {"E5", 659},    // E5 = 659 Hz
  {"F5", 698},    // F5 = 698 Hz
  {"F#5", 740},   // F#5 = 740 Hz
  {"G5", 784}     // G5 = 784 Hz
};

// Pin connected to the buzzer or speaker
const int speakerPin = 21;

// Function to play a note
void playNote(int frequency, int duration) {
  tone(speakerPin, frequency, duration);  // Generate a tone with the given frequency
  delay(duration + 50);  // Wait for the note to finish and add a slight pause
}

// Function to map note names to frequencies
int getNoteFrequency(const char* noteName) {
  // Loop through all the notes in the array and find the matching name
  for (int i = 0; i < sizeof(notes) / sizeof(notes[0]); i++) {
    if (strcmp(noteName, notes[i].name) == 0) {
      return notes[i].frequency;  // Return the corresponding frequency
    }
  }
  return 0;  // Return 0 if the note is not found
}

// Function to play "Happy Birthday"
void playHappyBirthday() {
  // Happy Birthday melody using note names
  const char* melody[] = {
    "C4", "C4", "D4", "C4", "F4", "E4", 
    "C4", "C4", "D4", "C4", "G4", "F4", 
    "C4", "C4", "C4", "A4", "F4", "E4", 
    "D4", "B4", "B4", "A4", "F4", "E4", "C4"
  };

  int noteDuration = 400;  // Duration for each note (in ms)

  // Play each note in the melody array
  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
    int frequency = getNoteFrequency(melody[i]);
    if (frequency != 0) {
      playNote(frequency, noteDuration);  // Play the note
    } else {
      delay(noteDuration);  // Rest (no sound)
    }
  }
}

void setup() {
  // Set up the speaker pin as an output
  pinMode(speakerPin, OUTPUT);
  Serial.begin(115200);
  Serial.println("Playing Happy Birthday!");
}

void loop() {
  // Play Happy Birthday
  playHappyBirthday();
  
  // Optional: Pause for a moment before playing the song again
  delay(10000);  // Pause for 2 seconds before replaying the song
}

