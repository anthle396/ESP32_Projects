/*
 * ESP32 Speaker
 * Author: Anthony Le
 * Date: 2025-04-04
 * Description: This program plays a melody on a buzzer using predefined note frequencies.
 * The frequencies are based on the standard pitch notation (A4 = 440 Hz).
 * Notes are represented using an enum mapping each note to its corresponding frequency.
 */

// Define an enum for note frequencies, avoiding pin name conflicts
enum Note {
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

// Notes for the song (based on your melody)
Note melody[] = {
  C4_, C4_, C4_, C4_, D4_, E4_, E4_, D4_,
  E4_, F4_, E4_, D4_, C4_, D4_, E4_, F4_,
  G4_, G4_, F4_, E4_, D4_, C4_, G4_, G4_,
  F4_, E4_, D4_, C4_, C4_, D4_, E4_, F4_,
  G4_, A4_, A4_, G4_, F4_, E4_, D4_, C4_
};

int noteDurations[] = {
  500, 500, 500, 500, 500, 500, 500, 500, // First phrase
  500, 500, 500, 500, 500, 500, 500, 500, // Second phrase
  500, 500, 500, 500, 500, 500, 500, 500, // Third phrase
  500, 500, 500, 500, 500, 500, 500, 500  // Fourth phrase
};

// Function to play a note
void playNote(Note note, int duration) {
  if (note != NONE) {
    tone(speakerPin, note, duration);  // Generate a tone with the given frequency
  }
  delay(duration + 50);  // Wait for the note to finish and add a slight pause
}

void setup() {
  pinMode(speakerPin, OUTPUT);
  Serial.begin(115200);
  Serial.println("Playing 'Can't Take My Eyes Off You'!");
}

void loop() {
  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
    playNote(melody[i], noteDurations[i]);
  }
  delay(1000);  // Pause before replaying the song
}
