#include <Adafruit_NeoPixel.h>

// กำหนดพินที่ใช้ (A2) และจำนวนหลอด LED
#define LED_PIN A2
#define NUM_LEDS 9  // จำนวนหลอด LED

// สร้างอ็อบเจ็กต์สำหรับควบคุม NeoPixel
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin(); // เริ่มต้น NeoPixel
  strip.show();  // ทำให้ทุก LED ดับตอนเริ่มต้น
}

void loop() {
  colorWipe(strip.Color(255, 0, 0), 50); // ไฟแดงทีละดวง
  colorWipe(strip.Color(0, 255, 0), 50); // ไฟเขียวทีละดวง
  colorWipe(strip.Color(0, 0, 255), 50); // ไฟน้ำเงินทีละดวง
}

// ฟังก์ชันไล่ไฟสีทีละดวง
void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color); // ตั้งค่าสีของ LED
    strip.show();                  // แสดงผล
    delay(wait);                   // รอเวลาตามที่กำหนด
  }
}
