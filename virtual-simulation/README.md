# 🌳 Kyros: AI Companion & Parental Control Dashboard

A **black-themed**, interactive React + Tailwind demo for the **Smart India Hackathon 2025**.
"Kyros" is a screen-free AI companion toy that reduces screen addiction and teaches Indian
cultural heritage through a 28-state **Bharat Yatra**. The app pairs an **interactive AI
chat companion** (the toy's "digital twin") with a professional parental analytics console —
all in a glowing orange/green-on-black SIH palette.

> **Demo tip:** browsers mute sound until the page receives a click. Click anywhere once,
> then chat with Kyros, press an activity key, or dispatch a voice note from Family Connect.

---

## 🚀 Run it

```bash
npm install
npm run dev        # http://localhost:5173
npm run build      # production build → dist/
npm run preview    # serve the build
```

Stack: React 18 · Vite 5 · Tailwind 3 · Web Speech API (`SpeechRecognition` +
`speechSynthesis`) · `MediaRecorder` · plain JS `Audio`. No external CDNs/fonts/network —
the dhol/dandiya dance loop is synthesised to a WAV in-browser, so it runs offline and in
sandboxed previews.

## 🖥️ Clearly divided, numbered sections

| # | Left — Hardware Simulator (twin) | # | Right — Parental Dashboard |
|---|---|---|---|
| 01 | **Interactive AI Companion** — a working chat (type or speak) in **11 Indian languages** (Hindi, Bengali, Marathi, Telugu, Tamil, Gujarati, Urdu, Kannada, Odia, Malayalam + English). The language picker drives both the **text replies and the spoken voice** (TTS picks that language) and mic recognition. Runs story/riddle/dance too | 04 | **Screen-Time Monitor** — audio engagement vs screen-time avoided, live clock + rising minutes, CSS weekly chart |
| 02 | **Activity Console** — tactile Story / Riddle / Dance Beats keys (physical `:active` presses) | 05 | **Live Data Stream** — every interaction is recorded in real time |
| 03 | **Bharat Yatra** — 28-state journey rail; tap a pin to ask Kyros about that state | 06 | **Family Connect** — record (MediaRecorder) or quick-demo a voice note and dispatch it to the toy twin |
| — | mic Push-to-Talk with red pulse; fallback to typing when voice is blocked | 07 | **Privacy & Device Management** — DPDP Act 2025 toggles + on-device data map |

## ⚙️ Core state (top-level `App`)

- `isListening` — toy mic active
- `ledStatusText` — chest LED (always returns to `Idle` after actions)
- `unlockedStates` — journey progress, defaults `['Punjab','Tamil Nadu']`
- `audioEngagementMinutes` — real-time engagement counter (demo clock ≈ ×10)
- `parentVoiceNote` — parent `MediaRecorder` blob (or `null`)
- `privacySettings` — `{ cloudRetention:false, ephemeralEdgeMode:true }` (zero-cloud + delete-by-default)
- `events` — live activity stream driving the **Live Data Stream** panel

## 🧩 Spec-named functions

**Toy side:** `toggleMicrophone` · `processChildSpeech` · `speakKyrosResponse` ·
`triggerDanceRhythm` · `simulateIncomingParentMessage`
**Parent side:** `recordParentVoiceNote` · `dispatchMessageToToy` · `togglePrivacyMode`

All audio is gesture-gated; the en-IN voice is picked async via
`speechSynthesis.getVoices()` + `onvoiceschanged`.

## ✅ Validated

- `npm run build` clean
- Real headless-Chrome interaction runs: chat replies, story fully narrates and
  **actually unlocks** the next state, riddle correct-answer unlock, dance start/stop,
  Family Connect demo note dispatch, mic toggle & privacy roundtrip — all with
  **zero page errors**, including multi-ticker sessions. (An earlier black-screen crash —
  a cross-scoped `m is not defined` bug — is fixed and guarded by an ErrorBoundary.)
- Voice fixes: en-IN natural/neural voice preference, a Chrome cancel→speak race guard,
  and a 🐢 slow / ▶ normal / 🐇 fast TTS speed control (verified rates 0.85 / 1.0 / 1.2).
- Mic guidance: clear blocked/permission messages plus a typing fallback (embedded
  previews & insecure contexts can block `getUserMedia` — open the app in its own tab
  over HTTPS for full mic/voice).

## 🗂️ File map

```
src/
  App.jsx                          # state hub · live event stream · split layout
  components/
    ui.jsx                         # Section(num) / Card / Toggle / MiniPill / ChatOrb / WaveGlyph
    toy/ToySimulator.jsx           # chat 01 · activity console 02 · Bharat Yatra 03
    parent/ScreenTimeMonitor.jsx   # 04 real-time monitor
    parent/ActivityFeed.jsx        # 05 live data stream
    parent/FamilyConnect.jsx       # 06 voice-note recorder + dispatch
    parent/PrivacyPanel.jsx        # 07 DPDP compliance
    parent/ParentDashboard.jsx     # right column assembly (04–07)
  data/states.js · stories.js · riddles.js
  utils/audio.js · kyrosBrain.js · format.js
```
