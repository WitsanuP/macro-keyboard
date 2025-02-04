#include <Adafruit_NeoPixel.h>

// กำหนดพินของคอลัมน์และแถว
const int colPins[] = {14, 16, 10}; // พอร์ตคอลัมน์
const int rowPins[] = {15, A0, A1}; // พอร์ตรูป

// กำหนดพินของ SK6812 และจำนวน LED
#define LED_PIN A2
#define NUM_LEDS 9
Adafruit_NeoPixel leds(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// ตารางการจับคู่ปุ่มกับ LED
const int ledMapping[3][3] = {
  {0, 3, 6}, // ปุ่ม 1, 2, 3 -> LED 1, 4, 7
  {1, 4, 7}, // ปุ่ม 4, 5, 6 -> LED 2, 5, 8
  {2, 5, 8}  // ปุ่ม 7, 8, 9 -> LED 3, 6, 9
};

// สถานะของไฟในแต่ละ LED (เปิดหรือปิด)
bool ledState[NUM_LEDS] = {false, false, false, false, false, false, false, false, false}; // ทุกไฟเริ่มต้นเป็นปิด

void setup() {
  // เริ่มต้น NeoPixel
  leds.begin();
  leds.show(); // ปิดไฟทั้งหมดในตอนเริ่มต้น

  // ตั้งค่าคอลัมน์เป็น OUTPUT และตั้งค่าเริ่มต้นเป็น HIGH
  for (int i = 0; i < 3; i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
  }

  // ตั้งค่าแถวเป็น INPUT_PULLUP
  for (int i = 0; i < 3; i++) {
    pinMode(rowPins[i], INPUT_PULLUP);
  }

  // สุ่มสถานะของ LED ตอนเริ่มเกม
  randomSeed(analogRead(0)); // ใช้ค่าแอนะล็อกสุ่มเพื่อสร้าง seed
  randomizeLEDs();
}

void loop() {
  // วนลูปตรวจจับปุ่มที่ถูกกด
  for (int col = 0; col < 3; col++) {
    digitalWrite(colPins[col], LOW);

    for (int row = 0; row < 3; row++) {
      if (digitalRead(rowPins[row]) == LOW) { // ตรวจจับปุ่มที่ถูกกด
        int ledIndex = ledMapping[row][col];

        // สลับสถานะของ LED ในตำแหน่งนั้นและตำแหน่งที่ติดกัน
        toggleLED(ledIndex);

        if (row > 0) toggleLED(ledMapping[row - 1][col]); // LED ข้างบน
        if (row < 2) toggleLED(ledMapping[row + 1][col]); // LED ข้างล่าง
        if (col > 0) toggleLED(ledMapping[row][col - 1]); // LED ซ้าย
        if (col < 2) toggleLED(ledMapping[row][col + 1]); // LED ขวา

        delay(300); // ดีเลย์เล็กน้อยก่อนตรวจจับปุ่มถัดไป
      }
    }

    digitalWrite(colPins[col], HIGH);
  }

  if (isGameOver()) {
    blinkGreen(3); // กระพริบสีเขียว 3 ครั้ง
    randomizeLEDs(); // สุ่มสถานะใหม่เพื่อเริ่มเกมใหม่
  }
}

// ฟังก์ชันเพื่อสลับสถานะของ LED
void toggleLED(int index) {
  ledState[index] = !ledState[index];
  if (ledState[index]) {
    leds.setPixelColor(index, leds.Color(50, 50, 55));
  } else {
    leds.setPixelColor(index, leds.Color(0, 0, 0));
  }
  leds.show();
}

// ฟังก์ชันตรวจสอบว่าเกมจบหรือยัง
bool isGameOver() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (ledState[i]) {
      return false;
    }
  }
  return true;
}

// ฟังก์ชันสุ่มสถานะของ LED ตอนเริ่มเกม
void randomizeLEDs() {
  for (int i = 0; i < NUM_LEDS; i++) {
    ledState[i] = random(2); // สุ่มค่า 0 หรือ 1
    if (ledState[i]) {
      leds.setPixelColor(i, leds.Color(50, 50, 55)); // เปิดไฟถ้าสุ่มได้ 1
    } else {
      leds.setPixelColor(i, leds.Color(0, 0, 0)); // ปิดไฟถ้าสุ่มได้ 0
    }
  }
  leds.show();
}

// ฟังก์ชันกระพริบไฟสีเขียว 3 ครั้ง
void blinkGreen(int times) {
  for (int t = 0; t < times; t++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds.setPixelColor(i, leds.Color(0, 255, 0)); // สีเขียว
    }
    leds.show();
    delay(300);

    leds.clear();
    leds.show();
    delay(300);
  }
}
