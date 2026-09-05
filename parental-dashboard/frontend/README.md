# Kyros Parental Companion — Web Dashboard

Central control, analytics and remote-voice hub for the **Kyros AI plush companion** (ESP32-S3 / Raspberry Pi) built for Smart India Hackathon 2026 to curb screen addiction and foster Indian cultural heritage.

**Demo login:** `parent@kyros.in` / `kyros2026`

## Architecture

```
┌────────────┐  HTTPS/SSE   ┌──────────────────────────────┐  SQL   ┌────────────┐
│  Browser   │◄────────────►│  Next.js 16 (App Router)     │◄──────►│ PostgreSQL │
│  Dashboard │              │  /api/v1/*  route handlers    │Drizzle │            │
└────────────┘              │  /api/v1/stream (SSE push)    │        └────────────┘
                            └───────────▲──────────────────┘
        heartbeat / cmd poll / acks     │  (or via backend/ FastAPI WS bridge)
                            ┌───────────┴──────────────────┐
                            │  ESP32-S3 plush (or built-in │
                            │  simulator on /dashboard)    │
                            └──────────────────────────────┘
```

* **Frontend** – Next.js App Router, TypeScript, Tailwind, Recharts, Lucide, Web Audio / MediaRecorder.
* **Backend** – Next.js route handlers (`src/app/api/v1/**`) + Drizzle ORM + PostgreSQL. JWT sessions in HttpOnly cookies (`jose`), scrypt password hashing.
* **Real-time** – Server-Sent Events (`/api/v1/stream`) push hardware status + voice-note state to every open dashboard; the toy uses heartbeat POSTs + a command queue. `backend/` contains the optional FastAPI WebSocket bridge (`/ws/toy/{toy_id}`, `/ws/dashboard/{parent_id}`) with a dual-client `ConnectionManager` and a Bhashini ASR/NMT/TTS wrapper.

## Modules

| Module | UI | API |
|---|---|---|
| 1 · Telemetry & Hardware Control | `/dashboard` — battery gauge, thermal alert, last sync, lock switch, Play/Study/Bedtime mode, volume | `GET/POST /api/v1/hardware/status`, `POST/GET/PATCH /api/v1/hardware/command` |
| 2 · Bharat Yatra (28 states) | `/bharat-yatra` — SVG India map, glowing unlocked nodes, quest prerequisites, Knowledge Explorer modal | `GET /api/v1/progress`, `GET /api/v1/culture/state/{stateId}` |
| 3 · Analytics | `/dashboard` — screen-free vs screen-time bars/trend (days/weeks/months), 4-pillar donut | `GET /api/v1/analytics/engagement?range=`, `GET /api/v1/analytics/category-split` |
| 4 · Voice Studio | `/voice-studio` — MediaRecorder + live waveform, 5 voice FX filters rendered in-browser, preview, queue with Queued → Synced → Played | `GET/POST /api/v1/parent/voice-note`, `GET/DELETE …/{id}/audio`, `POST …/{id}/ack` |
| 5 · Privacy Centre (DPDP 2023) | `/privacy-center` — searchable transcripts, per-log purge, retention sweep, red-alert *Erase all* | `GET/DELETE /api/v1/privacy/logs`, `POST /api/v1/privacy/retention-sweep`, `POST /api/v1/privacy/purge-all` |

`POST /api/v1/toy/simulate` drives the ESP32 simulator (heartbeat, offline, low battery, thermal spike, play session, acks, quest completion).

## Run locally

```bash
cp .env.example .env         # set DATABASE_URL / JWT_SECRET
npm install
npx drizzle-kit push         # create tables
npm run dev                  # http://localhost:3000  (demo data seeds on first request)
```

Optional hardware bridge:

```bash
cd backend && pip install -r requirements.txt && uvicorn main:app --port 8000
```

## Device contract (ESP32 firmware)

```jsonc
// heartbeat every 10s → POST /api/v1/hardware/status  (or WS frame {"type":"heartbeat",...})
{ "toy_id": "KYROS-ESP32-7A2F", "battery_level": 78, "temperature_c": 34, "wifi_rssi": -52 }

// drain commands → GET /api/v1/hardware/command?toy_id=…   then PATCH {"cmd_ids":[…]}
{ "frames": [ { "cmd_id": 12, "type": "set_mode", "payload": { "mode": "sleep", "wake_word_enabled": false } } ] }

// voice note lifecycle → POST /api/v1/parent/voice-note/{id}/ack  {"event":"downloaded"|"played"}
```
