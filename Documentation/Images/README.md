# LED and Speaker Control with Button - STM32 Project

This project demonstrates basic GPIO control using an STM32 microcontroller. It controls three LEDs (Red, Green, Blue) and a speaker, with a push button used as user input.

## 🛠️ Hardware Setup

| Component   | GPIO Pin | Label |
|-------------|----------|-------|
| Red LED     | GPIO 13  | D13   |
| Green LED   | GPIO 12  | D12   |
| Blue LED    | GPIO 27  | D27   |
| Speaker     | GPIO 21  | D21   |
| Push Button | GPIO 32  | D32   |

## ⚙️ Features

- Toggle or cycle through LED colors with a push button.
- Play tones or sound effects through the speaker.
- Basic debounce or edge detection for the push button (if implemented).

## 🧰 Tools & Dependencies

- STM32CubeIDE / STM32CubeMX  
- STM32 HAL libraries  
- C (or C++ if using classes)

## 🚀 Getting Started

1. Clone the repository or copy the project files.
2. Open the project in **STM32CubeIDE**.
3. Connect your STM32 board and flash the code.
4. Observe LED behavior and speaker response upon button press.

## 📝 Notes

- You can modify the behavior of the button to do things like:
  - Change which LED is on.
  - Play different tones.
  - Enter sleep mode or toggle modes.
