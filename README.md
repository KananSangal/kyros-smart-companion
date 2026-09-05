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
