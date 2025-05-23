# LED and Speaker Control with Button - ESP32 Project

This project demonstrates basic GPIO control using an ESP32 microcontroller. It controls three LEDs (Red, Green, Blue) and a speaker, with a push button used as user input.

## 🛠️ Hardware Setup

| Component        | GPIO Pin | Label |
|------------------|----------|-------|
| Red LED          | GPIO 13  | D13   |
| Green LED        | GPIO 12  | D12   |
| Blue LED         | GPIO 27  | D27   |
| Speaker          | GPIO 21  | D21   |
| Push Button      | GPIO 32  | D32   |
| OLED Chip Select | GPIO 17  | D17   |
| OLED Data Cmd    | GPIO 4   | A5    |
| OLED Reset       | GPIO 16  | D16   |
| OLED SCK         | GPIO 5   | SCK   |
| OLED SDA/MOSI    | GPIO 18  | MOSI  |


## ⚙️ Features

- Toggle or cycle through LED colors with a push button.
- Play tones or sound effects through the speaker.
- Basic debounce or edge detection for the push button (if implemented).
- Display colors and text on OLED display

Note*
While putting in the case I realized the green cable was too short so I tried to force it in and accidently unplugged that port. Therefore the green color will no longer work so only red and blue.

Code should still work fine.
