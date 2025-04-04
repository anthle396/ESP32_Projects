// /*
//  * Happy Birthday Melody for Arduino
//  * Author: Anthony Le
//  * Date: 2025-04-04
//  * Description: This program plays the "Happy Birthday" song on a buzzer using predefined note frequencies.
//  * The frequencies are based on the standard pitch notation (A4 = 440 Hz).
//  * Notes are represented by their names, and each note's corresponding frequency is mapped in the code.
//  */

// // Define a struct to store the note name and frequency
// struct Note {
//   const char* name;  // Name of the note (e.g., C4, D4, etc.)
//   int frequency;     // Frequency of the note in Hz (standard pitch notation)
// };

// // Array of Note structs with name and frequency
// Note notes[] = {
//   {"C4", 262},    // C4 (Middle C) = 262 Hz
//   {"C#4", 277},   // C#4 = 277 Hz
//   {"D4", 294},    // D4 = 294 Hz
//   {"D#4", 311},   // D#4 = 311 Hz
//   {"E4", 330},    // E4 = 330 Hz
//   {"F4", 349},    // F4 = 349 Hz
//   {"F#4", 370},   // F#4 = 370 Hz
//   {"G4", 392},    // G4 = 392 Hz
//   {"G#4", 415},   // G#4 = 415 Hz
//   {"A4", 440},    // A4 (Standard Pitch) = 440 Hz
//   {"A#4", 466},   // A#4 = 466 Hz
//   {"B4", 494},    // B4 = 494 Hz
//   {"C5", 523},    // C5 = 523 Hz
//   {"C#5", 554},   // C#5 = 554 Hz
//   {"D5", 587},    // D5 = 587 Hz
//   {"D#5", 622},   // D#5 = 622 Hz
//   {"E5", 659},    // E5 = 659 Hz
//   {"F5", 698},    // F5 = 698 Hz
//   {"F#5", 740},   // F#5 = 740 Hz
//   {"G5", 784},    // G5 = 784 Hz
//   {"NONE", 0}     // Nothing
// };

// // Pin connected to the buzzer or speaker
// const int speakerPin = 21;

// // Function to play a note
// void playNote(int frequency, int duration) {
//   tone(speakerPin, frequency, duration);  // Generate a tone with the given frequency
//   delay(duration + 50);  // Wait for the note to finish and add a slight pause
// }

// // Function to map note names to frequencies
// int getNoteFrequency(const char* noteName) {
//   // Loop through all the notes in the array and find the matching name
//   for (int i = 0; i < sizeof(notes) / sizeof(notes[0]); i++) {
//     if (strcmp(noteName, notes[i].name) == 0) {
//       return notes[i].frequency;  // Return the corresponding frequency
//     }
//   }
//   return 0;  // Return 0 if the note is not found
// }

// // Function to play "Happy Birthday"
// void playHappyBirthday() {
//   // Happy Birthday melody using note names
//   const char* melody[] = {
//     "C4", "NONE", "C4", "NONE", "D4", "NONE", "D4", "F4", "E4", 
//     "NONE", "C4", "D4", "C4", "G4", "F4", 
//     "C4", "C4", "C4", "A4", "F4", "E4", 
//     "D4", "B4", "B4", "A4", "F4", "E4", "C4"
//   };

//   int noteDuration = 400;  // Duration for each note (in ms)

//   // Play each note in the melody array
//   for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
//     int frequency = getNoteFrequency(melody[i]);
//     if (frequency != 0) {
//       playNote(frequency, noteDuration);  // Play the note
//     } else {
//       delay(noteDuration);  // Rest (no sound)
//     }
//   }
// }

// void setup() {
//   // Set up the speaker pin as an output
//   pinMode(speakerPin, OUTPUT);
//   Serial.begin(115200);
//   Serial.println("Playing Happy Birthday!");
// }

// void loop() {
//   // Play Happy Birthday
//   playHappyBirthday();
  
//   // Optional: Pause for a moment before playing the song again
//   delay(10000);  // Pause for 2 seconds before replaying the song
// }
/*
 * Can't Take My Eyes Off You Melody for Arduino
 * Author: Anthony Le
 * Date: 2025-04-04
 * Description: This program plays a melody on a buzzer using predefined note frequencies.
 * The frequencies are based on the standard pitch notation (A4 = 440 Hz).
 * Notes are represented using an enum mapping each note to its corresponding frequency.
 */

// Define an enum for note frequencies, avoiding pin name conflicts
enum Note {
  // C0_ = 16,   C0S_ = 17,  D0_ = 18,  D0S_ = 19,  E0_ = 21, // Tone function cannot go lower than 32 Hz
  // F0_ = 22,   F0S_ = 23,  G0_ = 25,  G0S_ = 26,  A0_ = 28,
  // A0S_ = 29,  B0_ = 31,
  C1_ = 33,   C1S_ = 35,  D1_ = 37,  D1S_ = 39,  E1_ = 41,
  F1_ = 44,   F1S_ = 46,  G1_ = 49,  G1S_ = 52,  A1_ = 55,
  A1S_ = 58,  B1_ = 62,
  C2_ = 65,   C2S_ = 69,  D2_ = 73,  D2S_ = 78,  E2_ = 82,
  F2_ = 87,   F2S_ = 93,  G2_ = 98,  G2S_ = 104, A2_ = 110,
  A2S_ = 117, B2_ = 123,
  C3_ = 131,  C3S_ = 139, D3_ = 147, D3S_ = 156, E3_ = 165,
  F3_ = 175,  F3S_ = 185, G3_ = 196, G3S_ = 208, A3_ = 220,
  A3S_ = 233, B3_ = 247,
  C4_ = 262,  C4S_ = 277, D4_ = 294, D4S_ = 311, E4_ = 330,
  F4_ = 349,  F4S_ = 370, G4_ = 392, G4S_ = 415, A4_ = 440,
  A4S_ = 466, B4_ = 494,
  C5_ = 523,  C5S_ = 554, D5_ = 587, D5S_ = 622, E5_ = 659,
  F5_ = 698,  F5S_ = 740, G5_ = 784, G5S_ = 831, A5_ = 880,
  A5S_ = 932, B5_ = 988,
  C6_ = 1047, C6S_ = 1109, D6_ = 1175, D6S_ = 1245, E6_ = 1319,
  F6_ = 1397, F6S_ = 1480, G6_ = 1568, G6S_ = 1661, A6_ = 1760,
  A6S_ = 1865, B6_ = 1976,
  C7_ = 2093, C7S_ = 2217, D7_ = 2349, D7S_ = 2489, E7_ = 2637,
  F7_ = 2794, F7S_ = 2960, G7_ = 3136, G7S_ = 3322, A7_ = 3520,
  A7S_ = 3729, B7_ = 3951,
  C8_ = 4186, C8S_ = 4435, D8_ = 4699, D8S_ = 4978,
  NONE = 0
};

// Pin connected to the buzzer or speaker
const int speakerPin = 21;

// Function to play a note
void playNote(Note note, int duration) {
  if (note != NONE) {
    tone(speakerPin, note, duration);  // Generate a tone with the given frequency
  }
  delay(duration + 50);  // Wait for the note to finish and add a slight pause
}

// Function to play a user-specified note
void playUserNote() {
  Serial.println("Enter a note (e.g., C4_, D4_, A4_, etc.):");
  while (!Serial.available()); // Wait for user input

  String input = Serial.readStringUntil('\n');
  input.trim(); // Remove any whitespace or newlines

  Note selectedNote = NONE;

  // Use switch statement for note mapping
  if (input.length() > 0) {
    switch (input[0]) {
      case 'C':
        if (input == "C4_") selectedNote = C4_;
        else if (input == "C4S_") selectedNote = C4S_;
        else if (input == "C5_") selectedNote = C5_;
        else if (input == "C5S_") selectedNote = C5S_;
        else if (input == "C6_") selectedNote = C6_;
        break;
      case 'D':
        if (input == "D4_") selectedNote = D4_;
        else if (input == "D4S_") selectedNote = D4S_;
        else if (input == "D5_") selectedNote = D5_;
        else if (input == "D5S_") selectedNote = D5S_;
        else if (input == "D6_") selectedNote = D6_;
        break;
      case 'E':
        if (input == "E4_") selectedNote = E4_;
        else if (input == "E5_") selectedNote = E5_;
        else if (input == "E6_") selectedNote = E6_;
        break;
      case 'F':
        if (input == "F4_") selectedNote = F4_;
        else if (input == "F4S_") selectedNote = F4S_;
        else if (input == "F5_") selectedNote = F5_;
        else if (input == "F5S_") selectedNote = F5S_;
        else if (input == "F6_") selectedNote = F6_;
        break;
      case 'G':
        if (input == "G4_") selectedNote = G4_;
        else if (input == "G4S_") selectedNote = G4S_;
        else if (input == "G5_") selectedNote = G5_;
        else if (input == "G5S_") selectedNote = G5S_;
        break;
      case 'A':
        if (input == "A4_") selectedNote = A4_;
        else if (input == "A4S_") selectedNote = A4S_;
        else if (input == "A5_") selectedNote = A5_;
        break;
      case 'B':
        if (input == "B4_") selectedNote = B4_;
        else if (input == "B5_") selectedNote = B5_;
        break;
    }
  }

  if (selectedNote != NONE) {
    Serial.println("Playing: " + input);
    playNote(selectedNote, 500);
  } else {
    Serial.println("Invalid note. Try again.");
  }
}

void setup() {
  pinMode(speakerPin, OUTPUT);
  Serial.begin(115200);
  Serial.println("Playing 'Can't Take My Eyes Off You'!");
}

void loop() {
  //playCantTakeMyEyesOffYou();
  delay(1000);  // Pause before replaying the song
  playUserNote(); // Allow user to input a note
}



