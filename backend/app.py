"""
KYROS AI Core Gateway - FastAPI WebSocket & Safety Guardrails
Team: Heisen-De-Bug
"""

import json
from fastapi import FastAPI, WebSocket, WebSocketDisconnect

app = FastAPI(title="KYROS Companion Core API")

def evaluate_emotional_state(text: str) -> dict:
    """Classifies sentiment and detects any distress trigger."""
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
