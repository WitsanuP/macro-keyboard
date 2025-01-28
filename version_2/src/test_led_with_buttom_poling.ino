#include <Keyboard.h>
#include <Adafruit_NeoPixel.h>

// กำหนดพินของคอลัมน์และแถว
const int colPins[] = {14, 16, 10}; // พอร์ตคอลัมน์
const int rowPins[] = {15, A0, A1}; // พอร์ตรูป

// กำหนดแผนผังคำของคีย์บอร์ดใน data
const char* data[3][3] = {
  {"gap", "dog", "key"},
  {"sad", "lov", "fuc"},
  {"kuy", "cat", "OK"}
};
const char* key[3][3] = {
  {data[0][0], data[1][0], data[2][0]}, 
  {data[0][1], data[1][1], data[2][1]}, 
  {data[0][2], data[1][2], data[2][2]}
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

unsigned long lastKeyPressTime[3][3];  // เวลาของการกดปุ่มล่าสุดในแต่ละปุ่ม
const unsigned long interval = 300;     // เวลาที่จะรอระหว่างการส่งค่า (100ms)

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
  // เริ่มต้นการตรวจจับการกดปุ่ม
  for (int col = 0; col < 3; col++) {
    // ตั้งค่าคอลัมน์ปัจจุบันเป็น LOW
    digitalWrite(colPins[col], LOW);

    // ตรวจสอบสถานะแถว
    for (int row = 0; row < 3; row++) {
      int buttonState = digitalRead(rowPins[row]);

      // ตรวจจับการกดปุ่ม
      if (buttonState == LOW) { // ปุ่มกด
        int ledIndex = ledMapping[row][col]; // ใช้ตาราง mapping เพื่อหา LED ที่สัมพันธ์กับปุ่ม

        // ตรวจสอบว่าเวลาผ่านไปนานพอที่จะส่งค่าต่อไปสำหรับปุ่มนี้
        if (millis() - lastKeyPressTime[row][col] >= interval) {
          // ส่งคำแทนตัวเลขไปยังคอมพิวเตอร์
          Keyboard.print(key[row][col]);
          Keyboard.write('\n'); // ส่ง Enter หลังจากพิมพ์คำ

          // อัพเดทเวลาเมื่อส่งค่าไปแล้ว
          lastKeyPressTime[row][col] = millis();
        }

        // เปิดไฟ LED ที่สัมพันธ์กับปุ่ม
        leds.clear();
        leds.setPixelColor(ledIndex, leds.Color(0xFF, 0x03, 0xA3)); //pink  Color(255, 0, 0)); // สีแดง
        leds.show();
      } else { // ปุ่มปล่อย
        // ปิดไฟ LED หลังจากปล่อยปุ่ม
        int ledIndex = ledMapping[row][col];
        leds.setPixelColor(ledIndex, leds.Color(0, 0, 0)); // ปิดไฟ LED
        leds.show();
      }
    }

    // ตั้งค่าคอลัมน์กลับเป็น HIGH
    digitalWrite(colPins[col], HIGH);
  }
}
