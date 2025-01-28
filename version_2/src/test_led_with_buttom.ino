#include <Keyboard.h>
#include <Adafruit_NeoPixel.h>

// กำหนดพินของคอลัมน์และแถว
const int colPins[] = {14, 16, 10}; // พอร์ตคอลัมน์
const int rowPins[] = {15, A0, A1}; // พอร์ตรูป

// กำหนดแผนผังคำของคีย์บอร์ด
const char* keys[3][3] = {
  {"gap", "dog", "key"},
  {"sad", "lov", "fuc"},
  {"kuy", "cat", "OK"}
};

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

void setup() {
  // เริ่มต้น Keyboard library
  Keyboard.begin();

  // ตั้งค่าคอลัมน์เป็น OUTPUT และตั้งค่าเริ่มต้นเป็น HIGH
  for (int i = 0; i < 3; i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
  }

  // ตั้งค่าแถวเป็น INPUT_PULLUP
  for (int i = 0; i < 3; i++) {
    pinMode(rowPins[i], INPUT_PULLUP);
  }

  // เริ่มต้น NeoPixel
  leds.begin();
  leds.show(); // ปิดไฟทั้งหมดในตอนเริ่มต้น
}

void loop() {
  // วนลูปตรวจจับปุ่มที่ถูกกด
  for (int col = 0; col < 3; col++) {
    // ตั้งค่าคอลัมน์ปัจจุบันเป็น LOW
    digitalWrite(colPins[col], LOW);

    // ตรวจสอบสถานะแถว
    for (int row = 0; row < 3; row++) {
      if (digitalRead(rowPins[row]) == LOW) { // ตรวจจับปุ่มที่ถูกกด
        int ledIndex = ledMapping[row][col]; // ใช้ตาราง mapping เพื่อหา LED ที่สัมพันธ์กับปุ่ม

        // ส่งคำแทนตัวเลขไปยังคอมพิวเตอร์
        Keyboard.print(keys[row][col]);
        Keyboard.write('\n'); // ส่ง Enter หลังจากพิมพ์คำ

        // เปิดไฟ LED ที่สัมพันธ์กับปุ่ม
        leds.clear();
        leds.setPixelColor(ledIndex, leds.Color(255, 0, 0)); // สีแดง
        leds.show();

        delay(300); // ดีเลย์ก่อนปิดไฟ

        // ปิดไฟ LED
        leds.clear();
        leds.show();
      }
    }

    // ตั้งค่าคอลัมน์กลับเป็น HIGH
    digitalWrite(colPins[col], HIGH);
  }
}
