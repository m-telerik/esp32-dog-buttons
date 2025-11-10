# esp32-dog-buttons aka Luna's Buttons

DIY implementation of dog's communication buttons using ESP32-C3, allowing Luna, the Black Cavapoo, to "talk" by pressing buttons that trigger sounds and log events.

## 🎯 Project Overview

This project recreates the Fluent Pet button system using affordable components:
- ESP32-C3 microcontroller
- MAX98357A I2S audio amplifier
- Speaker 
- Tactile buttons
- Original Fluent Pet hexagonal housings (repurposed)

When a button is pressed:
1. Audio feedback plays through the speaker
2. Event is logged to n8n workflow
3. Notification sent to Telegram
4. Data stored in database for analysis

## 📦 Hardware Components

| Component | Model/Type | Notes |
|-----------|------------|-------|
| Microcontroller | ESP32-C3 | Any ESP32-C3 dev board |
| Audio Amplifier | MAX98357A | I2S digital amplifier |
| Speaker | 4Ω or 8Ω, 3W | Salvaged from original Fluent Pet pads |
| Buttons | Tactile switches | Standard momentary push buttons |
| Housing | Fluent Pet hexagons | Original housings repurposed |
| Power | USB-C / 5V | Via ESP32-C3 board |

### Pin Connections

```
ESP32-C3 → MAX98357A
├─ GPIO 9  → BCLK (Bit Clock)
├─ GPIO 10 → LRC (Left/Right Clock)
├─ GPIO 8  → DIN (Data In)
├─ 5V      → VIN
└─ GND     → GND

ESP32-C3 → Buttons
└─ GPIO 6  → Button (other leg to GND)

MAX98357A → Speaker
├─ Speaker+ → Speaker wire 1
└─ Speaker- → Speaker wire 2
```

## 🛠️ Software Stack

- **Platform:** PlatformIO
- **Framework:** Arduino (ESP32)
- **IDE:** VS Code
- **Backend:** n8n (self-hosted on Raspberry Pi)
- **Notifications:** Telegram Bot API

## 📋 Prerequisites

### Software
- [VS Code](https://code.visualstudio.com/)
- [PlatformIO Extension](https://platformio.org/install/ide?install=vscode)
- Git

### Hardware Setup
- Breadboard (for prototyping)
- Dupont wires
- Soldering iron (for final assembly)
- USB-C cable
- WiFi network

### n8n Setup
- n8n instance running (Raspberry Pi or cloud)
- Webhook workflow configured
- Telegram bot created


## 📁 Project Structure

```
luna-buttons/
├── src/
│   ├── main.cpp           # Main application code
│   ├── config.h.example   # Configuration template
│   └── config.h           # Your config (gitignored)
├── include/
│   └── audio.h            # Audio playback functions
├── platformio.ini         # PlatformIO configuration
├── .gitignore
└── README.md
```

## 🔧 Configuration


## 📡 n8n Workflow



## 📞 Contact


