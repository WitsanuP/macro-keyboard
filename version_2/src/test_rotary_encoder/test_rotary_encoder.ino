#include <Encoder.h>
#include <HID-Project.h> // ใช้ควบคุม Media Control

#define ROT_A 8     // ขา A (CLK)
#define ROT_B 9     // ขา B (DT)
#define ROT_SW 7    // ขาปุ่มกด (SW)

Encoder myEnc(ROT_A, ROT_B);
long oldPosition = -999;

void setup() {
  pinMode(ROT_A, INPUT_PULLUP);
  pinMode(ROT_B, INPUT_PULLUP);
  pinMode(ROT_SW, INPUT_PULLUP); // เปิด Pull-up สำหรับปุ่มกด

  Consumer.begin(); // เริ่มต้น Media Control
}

void loop() {
  // ตรวจจับการหมุน
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    if (newPosition > oldPosition) {
      Consumer.write(MEDIA_VOLUME_UP); // หมุนเพิ่มเสียง
    } else {
      Consumer.write(MEDIA_VOLUME_DOWN); // หมุนลดเสียง
    }
    oldPosition = newPosition;
  }

  // ตรวจจับการกดปุ่ม (SW)
  if (digitalRead(ROT_SW) == LOW) { // ตรวจจับสถานะกด (LOW = กด)
    delay(50); // Debounce เล็กน้อย
    if (digitalRead(ROT_SW) == LOW) { // ยืนยันว่ากดจริง
      Consumer.write(MEDIA_PLAY_PAUSE); // สั่งหยุด/เล่นเพลง
      while (digitalRead(ROT_SW) == LOW); // รอจนปล่อยปุ่ม
      delay(50); // Debounce หลังปล่อย
    }
  }

  delay(10); // ลด jitter
}
