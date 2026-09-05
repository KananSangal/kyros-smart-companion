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
