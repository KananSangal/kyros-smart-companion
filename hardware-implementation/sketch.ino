#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

const int BUTTON_PIN = 2; // Touch sensor input
const int BUZZER_PIN = 8; // Audio feedback output

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
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
  // Do simple tones cute sound banane ke liye
  tone(BUZZER_PIN, 523, 100); // Note C5
  delay(120);
  tone(BUZZER_PIN, 659, 150); // Note E5
  delay(150);
  noTone(BUZZER_PIN);
}
