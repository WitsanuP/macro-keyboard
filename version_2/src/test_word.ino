#include <Keyboard.h>

// กำหนดพินของคอลัมน์และแถว
const int colPins[] = {14, 16, 10}; // พอร์ตคอลัมน์
const int rowPins[] = {15, A0, A1}; // พอร์ตรูป

// กำหนดแผนผังคำของคีย์บอร์ด
const char* keys[3][3] = {
  {"gap", "dog", "key"},
  {"sad", "lov", "fuc"},
  {"kuy", "cat", "OK"}
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
}

void loop() {
  // วนลูปตรวจจับปุ่มที่ถูกกด
  for (int col = 0; col < 3; col++) {
    // ตั้งค่าคอลัมน์ปัจจุบันเป็น LOW
    digitalWrite(colPins[col], LOW);

    // ตรวจสอบสถานะแถว
    for (int row = 0; row < 3; row++) {
      if (digitalRead(rowPins[row]) == LOW) { // ตรวจจับปุ่มที่ถูกกด
        Keyboard.print(keys[row][col]); // ส่งคำแทนตัวเลขไปยังคอมพิวเตอร์
        Keyboard.write('\n'); // ส่ง Enter หลังจากพิมพ์คำ
        delay(200); // ดีเลย์ป้องกันการกดซ้ำ
      }
    }

    // ตั้งค่าคอลัมน์กลับเป็น HIGH
    digitalWrite(colPins[col], HIGH);
  }
}
