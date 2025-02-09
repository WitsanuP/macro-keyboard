#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int colPins[] = {14, 16, 10}; 
const int rowPins[] = {15, A0, A1}; 
/*
const char* data[3][3] = {
  {"copy", "paste", "switch"},
  {"cut", "enter", "undo"},
  {"right", "down", "left"}
};
*/
const char* data[3][3] = {
  {"switch", "undo", "left"},
  {"paste", "enter", "down"},
  {"copy", "cut", "right"}
};

// ขนาดตารางของเกม
#define GRID_SIZE 4
#define MAX_LENGTH 50

struct Point {
  int x, y;
};

Point snake[MAX_LENGTH];
int snakeLength = 3;
Point food;
int dirX = 1, dirY = 0; // เริ่มต้นงูเคลื่อนที่ไปทางขวา

void setup() {
  // ตั้งค่าขาอินพุตของปุ่ม
  for (int i = 0; i < 3; i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
    pinMode(rowPins[i], INPUT_PULLUP);
  }

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;);
  }

  display.clearDisplay();
  randomSeed(analogRead(0));

  // ตำแหน่งเริ่มต้นของงู
  snake[0] = {32, 32};
  snake[1] = {28, 32};
  snake[2] = {24, 32};

  spawnFood();
}

void loop() {
  handleInput();
  moveSnake();
  checkCollision();
  drawGame();
  delay(150);
}

void handleInput() {
  for (int col = 0; col < 3; col++) {
    digitalWrite(colPins[col], LOW);
    for (int row = 0; row < 3; row++) {
      if (digitalRead(rowPins[row]) == LOW) {
        const char* btn = data[row][col];
        if (strcmp(btn, "left") == 0 && dirX == 0) { dirX = -1; dirY = 0; }
        if (strcmp(btn, "right") == 0 && dirX == 0) { dirX = 1; dirY = 0; }
        if (strcmp(btn, "enter") == 0 && dirY == 0) { dirX = 0; dirY = -1; } // up
        if (strcmp(btn, "down") == 0 && dirY == 0) { dirX = 0; dirY = 1; } // down
      }
    }
    digitalWrite(colPins[col], HIGH);
  }
}

void moveSnake() {
  for (int i = snakeLength - 1; i > 0; i--) {
    snake[i] = snake[i - 1];
  }
  snake[0].x += dirX * GRID_SIZE;
  snake[0].y += dirY * GRID_SIZE;
}

void checkCollision() {
  if (snake[0].x < 0 || snake[0].x >= SCREEN_WIDTH || snake[0].y < 0 || snake[0].y >= SCREEN_HEIGHT) {
    resetGame();
  }

  for (int i = 1; i < snakeLength; i++) {
    if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
      resetGame();
    }
  }

  if (snake[0].x == food.x && snake[0].y == food.y) {
    if (snakeLength < MAX_LENGTH) {
      snakeLength++;
    }
    spawnFood();
  }
}

void spawnFood() {
  food.x = (random(SCREEN_WIDTH / GRID_SIZE)) * GRID_SIZE;
  food.y = (random(SCREEN_HEIGHT / GRID_SIZE)) * GRID_SIZE;
}

void resetGame() {
  snakeLength = 3;
  snake[0] = {32, 32};
  snake[1] = {28, 32};
  snake[2] = {24, 32};
  dirX = 1; dirY = 0;
  spawnFood();
}

void drawGame() {
  display.clearDisplay();
  
  for (int i = 0; i < snakeLength; i++) {
    display.fillRect(snake[i].x, snake[i].y, GRID_SIZE, GRID_SIZE, SSD1306_WHITE);
  }

  display.fillRect(food.x, food.y, GRID_SIZE, GRID_SIZE, SSD1306_WHITE);
  display.display();
}
