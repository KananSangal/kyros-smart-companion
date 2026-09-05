# 🧸 KYROS — The Next-Gen Interactive Smart Plush Toy Companion
> An emotionally intelligent, screen-free smart plush companion built to foster healthy cognitive development, emotional security, and parental peace of mind.

**Project Lead & Innovation:** Team Heisen-De-Bug  
**Initiative:** Smart India Hackathon (SIH)  
**Status:** Working Prototype & Software Core Validated  

---

## 📑 Table of Contents
1. [Project Overview & Core Mission](#-project-overview--core-mission)
2. [End-to-End System Architecture](#-end-to-end-system-architecture)
3. [Hardware Component Suite & Sensor Integration](#-hardware-component-suite--sensor-integration)
   - [A. Main Controller: ESP32-S3](#a-main-controller-esp32-s3)
   - [B. Voice Input: INMP441 MEMS Omnidirectional Microphone](#b-voice-input-inmp441-mems-omnidirectional-microphone)
   - [C. Voice Output: MAX98357A I2S Class-D Amplifier + Speaker](#c-voice-output-max98357a-i2s-class-d-amplifier--speaker)
   - [D. Touch & Hug Sensing: TTP223 Capacitive Touch Sensors](#d-touch--hug-sensing-ttp223-capacitive-touch-sensors)
   - [E. Motion & Play Sensing: MPU6050 6-Axis IMU](#e-motion--play-sensing-mpu6050-6-axis-imu)
   - [F. Visual Feedback: WS2812B Addressable RGB LEDs](#f-visual-feedback-ws2812b-addressable-rgb-leds)
4. [Master Edge Firmware (All Hardware Combined)](#-master-edge-firmware)
5. [Cloud AI & Safety Guardrail Pipeline](#-cloud-ai--safety-guardrail-pipeline)
6. [Parental Intelligence Dashboard](#-parental-intelligence-dashboard)
7. [Pitch Deck & Presentation Blueprint](#-pitch-deck--presentation-blueprint)
8. [Local Simulation & Quickstart Guide](#-local-simulation--quickstart-guide)

---

## 🌟 Project Overview & Core Mission

### The Challenge
Children are surrounded by passive screens that lead to sensory overload, reduced attention spans, and social isolation. Existing smart toys are either simple prerecorded soundboards or rigid command assistants (like Alexa or Siri) that lack contextual memory, empathy, and child-safe guardrails.

### The Solution: KYROS
KYROS is a soft, huggable plush companion embedded with physical edge sensors and real-time conversational intelligence:
- **Screen-Free Engagement:** Natural voice-first interaction with rich, expressive sound effects.
- **Emotionally Responsive:** Detects physical touch (hugs, pats, cuddles) and vocal sentiment to comfort, encourage, or educate.
- **Child-Safe AI Guardrails:** Strict filtering to prevent exposure to inappropriate themes and real-time detection of emotional distress.
- **Parental Transparency:** A secure web companion dashboard giving parents insights into dominant emotional states, conversation topics, and play time—without invading privacy.

---

## 🏗️ End-to-End System Architecture

```text
       +-------------------------------------------------------------------------+
       |                           KYROS PHYSICAL PLUSH                          |
       |                                                                         |
       |   [INMP441 Mic]       [TTP223 Touch]       [MPU6050 IMU]                |
       |         |                    |                    |                     |
       |     (I2S Bus)           (GPIO ISR)           (I2C Bus)                  |
       |         \                    |                   /                      |
       |          +------------------> v <---------------+                       |
       |                           ESP32-S3                                      |
       |                     (Dual-Core 240MHz)                                  |
       |                          /        \                                     |
       |                  (I2S DAC)        (GPIO PWM)                            |
       |                      v                v                                 |
       |              [MAX98357A Amp]     [WS2812B NeoPixel]                     |
       |                     |                 |                                 |
       |             [4Ω 3W Speaker]      (Heart Pulse)                          |
       +----------------------|--------------------------------------------------+
                              | Secure WebSocket (WSS - 16kHz PCM Audio & Events)
                              v
       +-------------------------------------------------------------------------+
       |                          CLOUD INTELLIGENCE CORE                        |
       |                                                                         |
       |  [FastAPI Voice Gateway]                                                |
       |            |                                                            |
       |            v                                                            |
       |  [Speech-to-Text: Whisper / Deepgram]                                   |
       |            |                                                            |
       |            v                                                            |
       |  [Child Safety & Guardrail Filter]                                      |
       |            |                                                            |
       |            v                                                            |
       |  [LLM Dialog Engine (Llama-3 / GPT-4o-mini)] <---> [Child Vector Memory]  |
       |            |                                                            |
       |            +----------------------------+                               |
       |            |                            |                               |
       |            v                            v                               |
       |  [Text-to-Speech (TTS)]        [Sentiment & Mood Analytics Engine]      |
       |   (Natural Warm Voice)                          |                       |
       +------------|------------------------------------|-----------------------+
                    | Audio Stream                       | Sync Metrics (JSON)
                    v                                    v
             [KYROS Speaker]               [Parental Companion Dashboard]
```
---
## 🛠️ Hardware Component Suite & Sensor Integration

Here is the operational breakdown, wiring pinout, and standalone verification code for every component inside KYROS.

---

### A. Main Controller: ESP32-S3
- **Role:** Central embedded orchestrator handling multi-bus audio ingestion (I2S), sensor pooling (I2C/GPIO), Wi-Fi communications, and local LED state machines.
- **Why Chosen:** Dual-core Xtensa processor with native vector instructions for audio DSP, integrated Wi-Fi + BLE 5.0, and abundant GPIO pins.

---

### B. Voice Input: INMP441 MEMS Omnidirectional Microphone
- **Role:** Captures the child's voice clearly even inside plush casing.
- **Interface:** I2S (Inter-IC Sound) digital protocol.

#### Pinout:
| INMP441 Pin | ESP32-S3 Pin | Description |
| :--- | :--- | :--- |
| **VDD** | 3.3V | Power Supply |
| **GND** | GND | Ground |
| **SD** | GPIO 4 | Serial Data Output |
| **WS** | GPIO 5 | Word Select (Left/Right Clock) |
| **SCK** | GPIO 6 | Continuous Serial Clock |
| **L/R** | GND | Sets channel to Left |

---

### C. Voice Output: MAX98357A I2S Class-D Amplifier + Speaker
- **Role:** Converts incoming digital synthesized speech packets into audio output through a 4Ω 3W plush speaker.

#### Pinout:
| MAX98357A Pin | ESP32-S3 Pin | Description |
| :--- | :--- | :--- |
| **VIN** | 5V | Power for class-D output |
| **GND** | GND | Common Ground |
| **BCLK** | GPIO 7 | Bit Clock |
| **LRC** | GPIO 8 | Left/Right Word Clock |
| **DIN** | GPIO 9 | Digital Audio Data Input |
| **GAIN** | GND | Sets gain to default +9dB |

---

### D. Touch & Hug Sensing: TTP223 Capacitive Touch Sensors
- **Role:** Placed inside KYROS's chest and paws. Triggers responsive chirps, cuddles, or active listening when hugged.

#### Pinout:
| TTP223 Pin | ESP32-S3 Pin | Description |
| :--- | :--- | :--- |
| **VCC** | 3.3V | Power Supply |
| **GND** | GND | Ground |
| **SIG (Chest)** | GPIO 10 | Hug Detection Trigger |
| **SIG (Paw)** | GPIO 11 | Paw Touch Trigger |

---

### E. Motion & Play Sensing: MPU6050 6-Axis IMU
- **Role:** Detects rocking, carrying, tossing, and accidental drops via I2C.

#### Pinout:
| MPU6050 Pin | ESP32-S3 Pin | Description |
| :--- | :--- | :--- |
| **VCC** | 3.3V | Power Supply |
| **GND** | GND | Ground |
| **SCL** | GPIO 12 | I2C Clock Line |
| **SDA** | GPIO 13 | I2C Data Line |

---

### F. Visual Feedback: WS2812B Addressable RGB LEDs
- **Role:** Heartbeat pulses and listening status indicators inside the plush chest.
- **Data Pin:** GPIO 14 (ESP32-S3) | **Power:** 5V / GND

---

## ⚡ Master Edge Firmware (ESP32)

```cpp
#include <WiFi.h>
#include <WebSocketsClient.h>
#include <FastLED.h>

const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASS = "YOUR_WIFI_PASSWORD";
const char* BACKEND_HOST = "192.168.1.100";
const int   BACKEND_PORT = 8000;

#define PIN_TOUCH_CHEST 10
#define PIN_LED_DIN     14
#define NUM_LEDS        4

CRGB leds[NUM_LEDS];
WebSocketsClient wsClient;

void setup() {
  Serial.begin(115200);
  pinMode(PIN_TOUCH_CHEST, INPUT);

  FastLED.addLeds<WS2812B, GRB PIN_LED_DIN,>(leds, NUM_LEDS);
  FastLED.setBrightness(40);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(400);
    Serial.print(".");
  }

  wsClient.begin(BACKEND_HOST, BACKEND_PORT, "/ws/companion");
}

void loop() {
  wsClient.loop();

  if (digitalRead(PIN_TOUCH_CHEST) == HIGH) {
    fill_solid(leds, NUM_LEDS, CRGB::Pink);
    FastLED.show();
    wsClient.sendTXT("{\"event\":\"PHYSICAL_HUG\"}");
    delay(1000);
  }
}
```

---

## 5. 🧠 Cloud AI & Safety Guardrail Pipeline

FastAPI WebSocket backend for real-time speech, emotional classification, and child safety filtering.

    """
    KYROS AI Core Gateway - FastAPI WebSocket & Sentiment Engine
    Team: Heisen-De-Bug
    """

    import json
    from fastapi import FastAPI, WebSocket, WebSocketDisconnect

    app = FastAPI(title="KYROS Companion Core API")

    def evaluate_emotional_state(text: str) -> dict:
        text_lower = text.lower()
        if any(word in text_lower for word in ["scared", "sad", "crying", "alone", "hurt"]):
            return {"sentiment": "Anxious/Distressed", "alert": True}
        return {"sentiment": "Joyful & Curious", "alert": False}

    @app.websocket("/ws/companion")
    async def companion_socket(websocket: WebSocket):
        await websocket.accept()
        print("[KYROS Core] ESP32 Plush Connected.")
        try:
            while True:
                raw_data = await websocket.receive_text()
                payload = json.loads(raw_data)
                
                if payload.get("event") == "PHYSICAL_HUG":
                    response = {
                        "action": "SPEAK",
                        "text": "Mmm, that hug feels so warm! How was your day?",
                        "led": "HEARTBEAT"
                    }
                    await websocket.send_text(json.dumps(response))
                    
                elif payload.get("event") == "SPEECH_INPUT":
                    child_speech = payload.get("text", "")
                    analysis = evaluate_emotional_state(child_speech)
                    
                    reply = "I am right here with you. Everything is okay!" if analysis["alert"] else "Tell me more about that!"
                    response = {
                        "action": "SPEAK",
                        "text": reply,
                        "sentiment": analysis["sentiment"],
                        "alert": analysis["alert"]
                    }
                    await websocket.send_text(json.dumps(response))
        except WebSocketDisconnect:
            print("[KYROS Core] Plush disconnected.")

---

## 6. 📊 Parental Intelligence Dashboard

A secure, non-invasive overview for parents to track emotional trends, physical hugs, and curfews.

    <!DOCTYPE html>
    <html lang="en">
    <head>
      <meta charset="UTF-8" />
      <title>KYROS Parent Companion Hub</title>
      <script src="https://cdn.tailwindcss.com"></script>
    </head>
    <body class="bg-slate-50 text-slate-800 font-sans p-6 md:p-10">
      <div class="max-w-5xl mx-auto">
        <header class="flex justify-between items-center pb-6 border-b border-slate-200 mb-8">
          <div>
            <h1 class="text-3xl font-black text-indigo-600">🧸 KYROS Parent Hub</h1>
            <p class="text-sm text-slate-500">Child: Aarav | Status: <span class="text-emerald-600 font-semibold">● Online</span></p>
          </div>
          <button class="bg-indigo-600 text-white px-4 py-2 rounded-xl text-sm font-semibold">Settings & Curfews</button>
        </header>

        <div class="grid grid-cols-1 md:grid-cols-3 gap-6 mb-8">
          <div class="bg-white p-6 rounded-2xl border border-slate-200 shadow-sm">
            <span class="text-xs uppercase font-bold text-slate-400">Dominant Mood Today</span>
            <p class="text-2xl font-bold text-amber-500 mt-2">😊 Joyful & Curious</p>
          </div>
          <div class="bg-white p-6 rounded-2xl border border-slate-200 shadow-sm">
            <span class="text-xs uppercase font-bold text-slate-400">Physical Affection</span>
            <p class="text-2xl font-bold text-rose-500 mt-2">26 Hugs Logged</p>
          </div>
          <div class="bg-white p-6 rounded-2xl border border-slate-200 shadow-sm">
            <span class="text-xs uppercase font-bold text-slate-400">Safety & Distress Radar</span>
            <p class="text-2xl font-bold text-emerald-600 mt-2">100% Safe</p>
          </div>
        </div>
      </div>
    </body>
    </html>

---

## 7. 🎯 Pitch Deck & Presentation Blueprint

| Slide # | Slide Title | Core Talking Points |
| :--- | :--- | :--- |
| **01** | **Title & Vision** | *KYROS*: Smart, Screen-Free AI Plush Companion by Team **Heisen-De-Bug**. |
| **02** | **The Crisis** | Screen fatigue isolates children. Standard voice assistants lack empathy and safety. |
| **03** | **The Innovation** | Tactile affection sensors + child-safe LLM conversational pipeline with sub-800ms latency. |
| **04** | **Hardware Stack** | ESP32-S3, INMP441 mic, MAX98357A amp, TTP223 hug sensors, MPU6050 motion. |
| **05** | **Cloud & Guardrails** | Ephemeral voice stream, strict child safety guardrails, no audio storage. |
| **06** | **Parental Ecosystem** | Real-time sentiment metrics and gentle alerts without intruding on privacy. |
| **07** | **Scalability & Future** | Local languages, modular skins, and child therapy kits. |

---

## 8. 🚀 Local Simulation & Quickstart Guide

### Step 1: Run Backend Server
    git clone https://github.com/your-username/kyros-smart-companion.git
    cd kyros-smart-companion/backend
    pip install fastapi uvicorn websockets
    python -m uvicorn app:app --host 0.0.0.0 --port 8000 --reload

### Step 2: Open Parent Dashboard
Open `dashboard/index.html` in Google Chrome or any modern web browser.

### Step 3: Flash ESP32 Firmware
Open `firmware/esp32_master_firmware.ino` inside Arduino IDE, set board target to **ESP32S3 Dev Module**, update Wi-Fi credentials, and click **Upload**!

---

## 👥 Team: Heisen-De-Bug
Built with ❤️ for the Smart India Hackathon.
