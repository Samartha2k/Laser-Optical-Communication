# 🔦 Laser Optical Communication System
> Wireless text transmission over a laser beam using Arduino — no Wi-Fi, no Bluetooth, just light.

**By Samarth Agrawal & Shaunak Joshi** | CBSE National Science Exhibition Project

---

## 📖 What is this?

This project implements a **free-space optical (FSO) communication system** using a laser diode and an LDR (Light Dependent Resistor). Text typed into the Serial Monitor on the transmitter side is encoded as timed laser pulses, which the receiver Arduino decodes and displays character-by-character on an I2C LCD screen.

The core concept is **pulse-duration encoding** — each character maps to a unique laser-on duration (multiples of 4ms), making the system completely self-contained with no radio frequencies involved.

---

## 🧰 Hardware Required

| Component | Quantity |
|---|---|
| Arduino Uno | 2 |
| Laser Diode Module | 1 |
| LDR (Light Dependent Resistor) | 1 |
| I2C LCD Display (16x2) | 1 |
| IR Sensor Module | 1 |
| Resistor (10kΩ for LDR pull-down) | 1 |
| Breadboard | 2 |
| Jumper Wires | As needed |
| USB Cable | 2 |
| Power Source for transmitter (battery / 12V adapter) | 1 |

---

## 📁 Repository Structure

```
laser-optical-communication/
├── transmitter/
│   └── new_transmiter_optical_communication.ino
├── receiver/
│   └── new_reciever_optical_communication.ino
├── utils/
│   └── threshold_checking_code.ino
└── README.md
```

---

## ⚡ How It Works

### Encoding (Transmitter)
Each character is mapped to a position number (1–53):

| Range | Characters | Positions |
|---|---|---|
| A–Z | Alphabets (case-insensitive) | 1–26 |
| 0–9 | Digits | 27–36 |
| ` `, `.`, `-`, `=`, `+`, `>`, `<`, `/`, `?`, `*`, `&`, `^`, `%`, `$`, `#`, `@`, `!` | Symbols | 37–53 |

The transmit delay in milliseconds = `position × 4`

**Example:** `"HI"` → H is 8th letter → laser ON for **32ms**, then I is 9th → laser ON for **36ms**

### Decoding (Receiver)
The LDR detects laser pulses. The receiver measures how long the pulse lasts, rounds to the nearest 4ms, divides by 4 to get the position, then maps it back to the character.

### Display Clear (IR Sensor)
Wave your hand in front of the IR sensor to clear the LCD and reset the decoded message buffer — ready for a fresh transmission.

---

## 🔌 Wiring

### Transmitter Arduino
| Component | Arduino Pin |
|---|---|
| Laser Diode (+) | Pin 9 |
| Laser Diode (–) | GND |

### Receiver Arduino
| Component | Arduino Pin |
|---|---|
| LDR (with pull-down resistor) | A1 |
| IR Sensor OUT | Pin 2 |
| I2C LCD SDA | A4 |
| I2C LCD SCL | A5 |
| I2C LCD VCC | 5V |
| I2C LCD GND | GND |

---

## 🛠️ Setup & Upload

### 1. Install Required Library
In Arduino IDE, go to **Sketch → Include Library → Manage Libraries** and install:
```
LiquidCrystal_I2C
```

### 2. Find Your LDR Threshold (do this first!)
Upload `utils/threshold_checking_code.ino` to the **receiver Arduino** and open the Serial Monitor.

- Note the LDR value **without** the laser aimed at it (ambient light) → this is your **LOW**
- Aim the laser directly at the center of the LDR → note the **HIGH** value
- Set `threshold = (LOW + HIGH) / 2` in the receiver code

> Example: ambient = 100, laser = 300 → threshold = **200**

### 3. Upload Transmitter Code
Upload `transmitter/new_transmiter_optical_communication.ino` to the **transmitter Arduino**.

### 4. Upload Receiver Code
Update the `threshold` value in `receiver/new_reciever_optical_communication.ino`, then upload to the **receiver Arduino**.

### 5. Power Up
- Connect receiver Arduino to your laptop via USB
- Power the transmitter Arduino via battery or 12V adapter
- Align the laser so its beam hits the LDR directly

---

## 🚀 Usage

1. Open Serial Monitor on the **receiver** Arduino — LCD should show `Receiving...`
2. Open Serial Monitor on the **transmitter** Arduino
3. Type your message (e.g., `HELLO WORLD`) and hit Enter
4. Watch it appear on the LCD, character by character
5. Wave your hand over the IR sensor to clear the display before the next message

---

## ⚠️ Troubleshooting

| Problem | Fix |
|---|---|
| LCD backlight not on | Check I2C wiring (SDA→A4, SCL→A5) and I2C address (try `0x3F` if `0x27` doesn't work) |
| Receiver not detecting pulses | Re-run threshold calibration; adjust LDR alignment |
| Garbled characters | Increase inter-character gap or recalibrate threshold |
| IR sensor not clearing display | Check IR sensor OUT → Pin 2, ensure it's pulled HIGH normally |
| Upload fails | Verify correct board selected in IDE, correct COM port |

---

## 🌍 Real-World Applications

- **Free-Space Optical Communication (FSO)** — used where RF is impractical or prohibited
- **Satellite communication** — inter-satellite laser links (e.g., SpaceX Starlink uses FSO between satellites)
- **Secure short-range communication** — laser beam is highly directional and hard to intercept
- **Interplanetary communication** — NASA's LLCD and LCRD missions use similar optical principles

---

## 📐 Scientific Principle

Light travels at **300,000,000 m/s** — the fastest phenomenon in the universe. By modulating a laser beam (switching it ON/OFF in precise timed patterns), we encode data into light itself. The receiver measures the duration of each pulse to reconstruct the original data — the same fundamental principle behind fiber optics and deep-space laser comms.

---

## 📜 License

MIT License — free to use, modify, and build upon. Attribution appreciated!

---

## 🙌 Acknowledgements

Built for the **CBSE National Science Exhibition**. Inspired by the growing field of free-space optical communication and its role in next-generation space missions.
