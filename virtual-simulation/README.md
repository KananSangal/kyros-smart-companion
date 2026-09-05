# 🧪 KYROS Virtual Hardware Simulation

This directory contains the virtual prototyping environment and circuit simulation logic for the **KYROS** smart plush companion.

---

## 🎯 Purpose of Simulation
- Emulate the **ESP32-S3** microcontroller edge behavior without requiring immediate physical wiring.
- Test touch trigger events (TTP223 capacitive sensors) and simulate hug/gesture detection.
- Validate I2S audio stream routing and visual NeoPixel LED state machines before physical flashing.
- Test WebSocket handshake connections with the local/cloud backend core.

---

## 🛠️ Simulation Stack & Components
- **Microcontroller:** Virtual ESP32-S3 DevKit
- **Sensors Emulated:** Capacitive touch inputs, push-button triggers, and I2C accelerometer vectors
- **Actuators:** Virtual addressable RGB LEDs (WS2812B) and digital I2S buzzer/audio output
- **Environment:** Wokwi / Web-based Edge Simulator

---

## 🚀 How to Run the Simulation
1. Load the simulation files (`sketch.ino` / `diagram.json`) in your simulation environment (e.g., [Wokwi](https://wokwi.com)).
2. Configure the simulated Wi-Fi gateway to route WebSocket events to the local KYROS FastAPI backend (`/ws/companion`).
3. Trigger virtual touch events to inspect LED feedback and incoming cloud voice responses.

---

## 📁 Directory Status
> ⚠️ **Under Active Integration:** The complete simulation source files are being linked and committed here by the simulation lead.
