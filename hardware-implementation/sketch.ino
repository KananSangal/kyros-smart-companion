#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ESP32 GPIO Pins
const int BUTTON_PIN = 4;
const int BUZZER_PIN = 18;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

  // ESP32 default I2C pins: SDA=21, SCL=22
  Wire.begin(21, 22);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while(true); 
  }

  showHappyFace();
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    showCuddleFace();
    playHappyChime();
    delay(400);
  } else {
    showHappyFace();
  }
  delay(50);
}

void showHappyFace() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(30, 15);
  display.print("KYROS");
  display.setCursor(20, 38);
  display.print("(^ _ ^)");
  display.display();
}

void showCuddleFace() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(15, 15);
  display.print("HUG ME!");
  display.setCursor(15, 38);
  display.print("(* > < *)");
  display.display();
}

void playHappyChime() {
  tone(BUZZER_PIN, 523, 100); // Note C5
  delay(120);
  tone(BUZZER_PIN, 659, 150); // Note E5
  delay(150);
  noTone(BUZZER_PIN);
}
