#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int ballX = 64, ballY = 32;
int speedX = 2, speedY = 2;
int radius = 5;

void setup() {
    Wire.begin();
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        for (;;);
    }
    display.clearDisplay();
}

void loop() {
    display.clearDisplay();
    
    // วาดลูกบอล
    display.fillCircle(ballX, ballY, radius, SSD1306_WHITE);
    display.display();
    
    // อัปเดตตำแหน่ง
    ballX += speedX;
    ballY += speedY;
    
    // เด้งเมื่อชนขอบ
    if (ballX - radius <= 0 || ballX + radius >= SCREEN_WIDTH) speedX = -speedX;
    if (ballY - radius <= 0 || ballY + radius >= SCREEN_HEIGHT) speedY = -speedY;

    delay(20);
}
