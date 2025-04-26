/*
 * ESP32 Speaker
 * Author: Anthony Le
 * Updated: 2025-04-21
 * Description: This version plays notes from Serial input, supporting both naturals (A-G) and sharps (A#–G#).
 */

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


const int speakerPin = 21;

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
  E4_, D4S_, C4S_, REST,
  C4_, C4S_, C4_, C4S_, C4_, C4S_, 
  E4_, D4S_, C4S_, REST,
  C4_, C4S_, C4_, C4S_, E4_, REST,

  // Chorus: "I love you baby"
  G5S_, G5S_, G5S_, G5S_, C5S_, 
  // "And if it's quite alright "
  C5S_, D5S_, E5_, F5S_, G5S_, G5S_,
  // "I need you, Baby"
  F5S_, E5_, D5S_, E5_,
  // "To warm the lonely nights"
  F5S_, F5S_, E5_, D5S_, E5_, F5S_, F5S_, E5_,

  // "I love you baby..."
  E5_, E5_, G5S_, G5S_, C5S_,
  // "Trust in me why I say"
  C5S_, D5S_, E5_, F5S_, G5S_, G5S_,

  // --- Work In Progress down here ---
  // "Oh pretty baby" 
  F5S_, E5_, D5S_, E5_,
  // "Dont bring me down I pray"
  F5S_, F5S_, E5_, D5S_, E5_, F5S_, F5S_, E5_,

  // "Oh pretty baby, now that I found you, stay" 
  E5_, E5_, G5S_, G5S_, C5S_,
  C5S_, D5S_, E5_, F5S_, G5S_, G5S_,

  // "And let me love you, baby"
  F5S_, E5_, D5S_, E5_,
  // "Let me love you"
  F5S_, F5S_, E5_, D5S_, E5_, REST
};

float noteDurations[] = {
  // Intro durations
  2.5, 3, 2.5, 3, 3, 2.5, 
  3, 2.5, 2.5, 2.5, 
  3, 2.5, 3, 2.5, 3, 3, 2.5, 
  3, 2.5, 2.5, 2.5, 
  2.5, 2.5, 2.5, 2.5, 1.5, 2.5, 

  // Chorus: "I love you baby..."
  2, 2, 2, 2, 2, 
  // "And if it's quite alright "
  2, 2, 2, 2, 2, 2, 
  // "I need you, Baby"
  2, 2, 2, 2,
  // "To warm the lonely nights"
  2, 2, 2, 2, 2, 2, 2, 2,

  // "I love you baby..."
  2, 2, 2, 2, 2,
  // "Trust in me why I say"
  2, 2, 2, 2, 2, 2,

  // "Oh pretty baby" 
  2, 2, 2, 2,
  // "Dont bring me down I pray"
  2, 2, 2, 2, 2, 2, 2, 2,

  // "Oh pretty baby, now that I found you, stay" 
  2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 2,

  // "And let me love you, baby"
  2, 2, 2, 2,
  // "Let me love you"
  2, 2, 2, 2, 2, 4
};


void PlayThis() {
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

void PlayTest(void){
  static String inputBuffer = "";
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {
      if (inputBuffer.length() > 0) {
        Note n = parseNote(inputBuffer);
        if (n != REST) {
          playNote(n, 500);
          Serial.print("Playing note: ");
          Serial.println(inputBuffer);
        } else {
          Serial.print("Invalid input: ");
          Serial.println(inputBuffer);
        }
        inputBuffer = "";  // clear for next input
      }
    } else {
      inputBuffer += c;
    }
  }
}

void setup() {
  pinMode(speakerPin, OUTPUT);
  Serial.begin(115200);
  Serial.println("Type notes (A-G or A#–G#) to play. Press ENTER after each.");
}

void loop() {
  PlayThis();
  while(1) {
    // Does Nothing
  }
}

