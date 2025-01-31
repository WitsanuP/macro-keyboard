#include <Keyboard.h>
#include <Adafruit_NeoPixel.h>

const int colPins[] = {14, 16, 10}; 
const int rowPins[] = {15, A0, A1}; 

// ข้อมูล mapping ปุ่ม
const char* data[3][3] = {
  {"copy", "paste", "switch"},
  {"cut", "enter", "undo"},
  {"right", "down", "left"}
};

// Struct สำหรับแมปปิ้ง key combo (รองรับ 3 ปุ่ม)
struct KeyCombo {
  const char* name;
  uint8_t key1;
  uint8_t key2;
  uint8_t key3;
};

// ใช้ array แทน std::map
const KeyCombo keyMapping[] = {
  {"copy", KEY_LEFT_SHIFT, KEY_LEFT_CTRL, KEY_ESC}, // แก้จาก CTRL + C เป็น ALT + CTRL + ESC
  {"paste", KEY_LEFT_CTRL, 'v', 0},
  {"switch", KEY_LEFT_ALT, KEY_TAB, 0},
  {"cut", KEY_LEFT_ALT, 'x', 0},
  {"enter", KEY_LEFT_ALT, KEY_RETURN, 0},
  {"undo", KEY_LEFT_ALT, 'z', 0},
  {"right", KEY_LEFT_ALT, 'l', 0},
  {"down", KEY_LEFT_ALT, 'k', 0},
  {"left", KEY_LEFT_ALT, 'j', 0}
};

// ฟังก์ชันค้นหาปุ่มจาก data[row][col]
KeyCombo findKeyCombo(const char* name) {
  for (int i = 0; i < sizeof(keyMapping) / sizeof(KeyCombo); i++) {
    if (strcmp(name, keyMapping[i].name) == 0) {
      return keyMapping[i]; 
    }
  }
  return {"", 0, 0, 0}; // ไม่เจอ
}

#define LED_PIN A2
#define NUM_LEDS 9
Adafruit_NeoPixel leds(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

const int ledMapping[3][3] = {
  {0, 3, 6}, 
  {1, 4, 7}, 
  {2, 5, 8}  
};

unsigned long lastKeyPressTime[3][3];
const unsigned long interval = 300;

void setup() {
  Keyboard.begin();

  for (int i = 0; i < 3; i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
  }

  for (int i = 0; i < 3; i++) {
    pinMode(rowPins[i], INPUT_PULLUP);
  }

  leds.begin();
  leds.show();
}

void loop() {
  for (int col = 0; col < 3; col++) {
    digitalWrite(colPins[col], LOW);

    for (int row = 0; row < 3; row++) {
      int buttonState = digitalRead(rowPins[row]);

      if (buttonState == LOW) {
        int ledIndex = ledMapping[row][col];

        if (millis() - lastKeyPressTime[row][col] >= interval) {
          KeyCombo key = findKeyCombo(data[row][col]);
          if (key.key1 != 0) Keyboard.press(key.key1);
          if (key.key2 != 0) Keyboard.press(key.key2);
          if (key.key3 != 0) Keyboard.press(key.key3);
          delay(50);
          Keyboard.releaseAll();

          lastKeyPressTime[row][col] = millis();
        }

        leds.clear();
        leds.setPixelColor(ledIndex, leds.Color(0xFF, 0x03, 0xA3)); 
        leds.show();
      } else {
        int ledIndex = ledMapping[row][col];
        leds.setPixelColor(ledIndex, leds.Color(0, 0, 0)); 
        leds.show();
      }
    }

    digitalWrite(colPins[col], HIGH);
  }
}
