#include <Adafruit_NeoPixel.h>

// กำหนดพินที่ใช้ (A2) และจำนวนหลอด LED
#define LED_PIN A2
#define NUM_LEDS 16  // จำนวนหลอด LED

// สร้างอ็อบเจ็กต์สำหรับควบคุม NeoPixel
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// ฟังก์ชันสำหรับการตั้งค่า
void setup() {
  strip.begin(); // เริ่มต้น NeoPixel
  strip.show();  // ทำให้ทุก LED ดับตอนเริ่มต้น
}

// ฟังก์ชันสำหรับการวนลูป
void loop() {
  smoothRainbow(10); // ไล่สีแบบนุ่มนวล
}

// ฟังก์ชันไล่สีแบบนุ่มนวล
void smoothRainbow(uint8_t wait) {
  // "j" เป็นตัวแปรวนสำหรับไล่สี
  for (int j = 0; j < 256; j++) { 
    for (int i = 0; i < strip.numPixels(); i++) {
      // คำนวณสีแบบไล่เฉดสำหรับแต่ละ LED
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();  // แสดงผลสีที่ตั้งค่า
    delay(wait);   // รอเวลาเพื่อความนุ่มนวล
  }
}

// ฟังก์ชันสร้างเฉดสีจากวงล้อสี (Color Wheel)
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
