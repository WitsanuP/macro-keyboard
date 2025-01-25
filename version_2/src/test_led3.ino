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
  gradientShift(20); // ไล่สีทีละหลอดแบบนุ่มนวล
}

// ฟังก์ชันไล่สีทีละหลอดแบบนุ่มนวล
void gradientShift(uint8_t wait) {
  static int startPosition = 0; // ตำแหน่งเริ่มต้นของสี
  
  for (int j = 0; j < 256; j++) { // วนลูปเฉดสี
    for (int i = 0; i < strip.numPixels(); i++) {
      // คำนวณเฉดสีตามตำแหน่งของหลอด LED
      strip.setPixelColor((i + startPosition) % NUM_LEDS, Wheel((j + i * 20) & 255));
    }
    strip.show();  // แสดงผลสีที่ตั้งค่า
    delay(wait);   // รอเวลาตามที่กำหนด

    // หลังจากวนลูปสีแต่ละครั้ง ย้ายตำแหน่งเริ่มต้นไป 1
    startPosition = (startPosition + 1) % NUM_LEDS;
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
