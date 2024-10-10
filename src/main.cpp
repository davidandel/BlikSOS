#include <Arduino.h>

int ledPin = 2;

int dotTime = 150;
int dashTime = 300;
int symbolGap = 50;
int letterGap = 400;
int wordGap = 800;

int morseLengths[26] = {2, 4, 4, 3, 1, 4, 3, 4, 2, 4, 3, 4, 2, 2, 3, 4, 4, 3, 3, 1, 3, 4, 3, 4, 4, 4};

int morseTable[26][4] = {
  {0, 1}, {1, 0, 0, 0}, {1, 0, 1, 0}, {1, 0, 0}, {0}, {0, 0, 1, 0}, {1, 1, 0}, {0, 0, 0, 0},
  {0, 0}, {0, 1, 1, 1}, {1, 0, 1}, {0, 1, 0, 0}, {1, 1}, {1, 0}, {1, 1, 1}, {0, 1, 1, 0},
  {1, 1, 0, 1}, {0, 1, 0}, {0, 0, 0}, {1}, {0, 0, 1}, {0, 0, 0, 1}, {0, 1, 1}, {1, 0, 0, 1},
  {1, 0, 1, 1}, {1, 1, 0, 0}
};

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Zadej písmeno:");
}

void sendMorse(int code[], int length) {
  for (int i = 0; i < length; i++) {
    if (code[i] == 0) {
      digitalWrite(ledPin, HIGH);   // Dot
      delay(dotTime);
    } else {
      digitalWrite(ledPin, HIGH);   // Dash
      delay(dashTime);
    }
    digitalWrite(ledPin, LOW);
    delay(symbolGap);
  }
}

void translateText(String text) {
  text.toUpperCase();
  for (int i = 0; i < text.length(); i++) {
    if (text[i] == ' ') {
      delay(wordGap);
    } else {
      int idx = text[i] - 'A';
      sendMorse(morseTable[idx], morseLengths[idx]);
      delay(letterGap);
    }
  }
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readString();
    translateText(input);
  }
}
