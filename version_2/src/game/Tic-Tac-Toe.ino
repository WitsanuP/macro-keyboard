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

// สถานะของกระดาน: 0 = ว่าง, 1 = ผู้เล่น 1, 2 = ผู้เล่น 2
int board[3][3] = {0};

int currentPlayer = 1; // ผู้เล่นคนแรกเริ่มก่อน

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
    pinMode(rowPins[i], INPUT_PULLUP);
  }
  leds.begin();
  leds.show();
}

void loop() {
  for (int col = 0; col < 3; col++) {
    digitalWrite(colPins[col], LOW);

    for (int row = 0; row < 3; row++) {
      if (digitalRead(rowPins[row]) == LOW && board[row][col] == 0) { // ตรวจจับปุ่มกดและช่องว่าง
        board[row][col] = currentPlayer;
        int ledIndex = ledMapping[row][col];
        
        // กำหนดสีตามผู้เล่น
        if (currentPlayer == 1) {
          leds.setPixelColor(ledIndex, leds.Color(0, 255, 0)); // สีเขียว
        } else {
          leds.setPixelColor(ledIndex, leds.Color(0, 0, 255)); // สีฟ้า
        }
        leds.show();

        delay(300); // ดีเลย์เพื่อป้องกันการกดซ้ำ

        if (checkWin(currentPlayer)) {
          showWinner(currentPlayer);
          resetGame();
          return;
        }

        if (isBoardFull()) { // ตรวจสอบกรณีเสมอ
          showDraw();
          resetGame();
          return;
        }

        currentPlayer = (currentPlayer == 1) ? 2 : 1; // สลับผู้เล่น
      }
    }

    digitalWrite(colPins[col], HIGH);
  }
}

bool checkWin(int player) {
  for (int i = 0; i < 3; i++) {
    if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) || // แถว
        (board[0][i] == player && board[1][i] == player && board[2][i] == player)) { // คอลัมน์
      return true;
    }
  }
  if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || // แนวทแยงหลัก
      (board[0][2] == player && board[1][1] == player && board[2][0] == player)) { // แนวทแยงรอง
    return true;
  }
  return false;
}

bool isBoardFull() {
  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      if (board[row][col] == 0) return false;
    }
  }
  return true;
}

void showWinner(int player) {
  uint32_t color = (player == 1) ? leds.Color(0, 255, 0) : leds.Color(0, 0, 255);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds.setPixelColor(i, color);
  }
  leds.show();
  delay(2000); // แสดงผลลัพธ์ 2 วินาที
}

void showDraw() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds.setPixelColor(i, leds.Color(255, 255, 0)); // สีเหลืองสำหรับเสมอ
  }
  leds.show();
  delay(2000);
}

void resetGame() {
  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      board[row][col] = 0;
    }
  }
  leds.clear();
  leds.show();
  currentPlayer = 1; // เริ่มใหม่โดยผู้เล่นคนแรก
}
