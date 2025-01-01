#include <Mouse.h>
#include <Keyboard.h>
#include <Encoder.h>

// encoder-----------------------------------------------------------------
Encoder myEncoder(3, 4); // Replace 3 and 4 with your actual pin numbers
const int buttonEncode = 2; // Replace with your actual pin number

int lastButtonState = HIGH;

long newPosition;
long rePosition;
long oldPosition;
//keybord----------------------------------------------------------------
const int buttonPin11 = 8;
const int buttonPin12 = 7;
const int buttonPin13 = 6;
const int buttonPin21 = 9;
const int buttonPin22 = 10;
const int buttonPin23 = 5;
const int buttonPin31 = 16;
const int buttonPin32 = 14;
const int buttonPin33 = 15;
bool button11Pressed = false;
bool button12Pressed = false;
bool button13Pressed = false;
bool button21Pressed = false;
bool button22Pressed = false;
bool button23Pressed = false;
bool button31Pressed = false;
bool button32Pressed = false;
bool button33Pressed = false;
void setup() {
  // Initialize the Mouse and Keyboard libraries
  //Mouse.begin();
  Keyboard.begin();
  pinMode(buttonPin11, INPUT_PULLUP);
  pinMode(buttonPin12, INPUT_PULLUP);
  pinMode(buttonPin13, INPUT_PULLUP);
  pinMode(buttonPin21, INPUT_PULLUP);
  pinMode(buttonPin22, INPUT_PULLUP);
  pinMode(buttonPin23, INPUT_PULLUP);
  pinMode(buttonPin31, INPUT_PULLUP);
  pinMode(buttonPin32, INPUT_PULLUP);
  pinMode(buttonPin33, INPUT_PULLUP);
  // Set the button pin as an input with a pull-up resistor
  pinMode(buttonEncode, INPUT_PULLUP);

  // Start the serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Read the button state
  int buttonState = digitalRead(buttonEncode);

  // Check for a button press
  if (buttonState == LOW && lastButtonState == HIGH) {
    // Button is pressed, send "Alt + K" keyboard command
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press('k');
    delay(50); // Delay for stability
    Keyboard.releaseAll();
  }

  // Read the rotary encoder position
  newPosition = myEncoder.read();
  rePosition = newPosition - oldPosition;
  //if(0!=newPosition)
  Serial.println(newPosition); // Print the encoder position for debugging

  // Check for clockwise rotation
  if (rePosition > 0) {
    // Clockwise rotation, send "Alt + J" keyboard command
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press('l');
    delay(50); // Delay for stability
    Keyboard.releaseAll();
  }
  // Check for counterclockwise rotation
  else if (rePosition < 0) {
    // Counterclockwise rotation, send "Alt + L" keyboard command
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press('j');
    delay(50); // Delay for stability
    Keyboard.releaseAll();
  }
  oldPosition = newPosition;
  // Update the last button state
  lastButtonState = buttonState;
  //keyboard-----------------------
  if (digitalRead(buttonPin11) == LOW) {

    if (!button11Pressed) {
      Keyboard.press(KEY_LEFT_ALT); 
      delay(50);
      Keyboard.press(KEY_TAB);
      delay(150);
      Keyboard.releaseAll();
      button11Pressed = true;
    }
  } else {
    button11Pressed = false;
  }
  //ctrl c
  if (digitalRead(buttonPin12) == LOW) {
    if (!button12Pressed) {
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('c');  // Send the 'C' key
      delay(50);
      Keyboard.releaseAll();
      button12Pressed = true;
    }
  } else {
    button12Pressed = false;
  }
//ctrl v
  if (digitalRead(buttonPin13) == LOW) {
    if (!button13Pressed) {
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('v');  // Send the 'C' key
      delay(200);
      Keyboard.releaseAll();
      button13Pressed = true;
    }
  } else {
    button13Pressed = false;
  }

  // buttom row 2
  //alt z 21
  if (digitalRead(buttonPin21) == LOW) {
    if (!button21Pressed) {
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('z');  
      delay(200);
      Keyboard.releaseAll();
      button21Pressed = true;
    }
  } else {
    button21Pressed = false;
  }
  //alt enter 22
  if (digitalRead(buttonPin22) == LOW) {
    if (!button22Pressed) {
      Keyboard.press(KEY_LEFT_ALT); 
      delay(50);
      Keyboard.press(KEY_RETURN);
      
      delay(150);
      Keyboard.releaseAll();
      button22Pressed = true;
    }
  } else {
    button22Pressed = false;
  }
  //alt x 23
  if (digitalRead(buttonPin23) == LOW) {
    if (!button23Pressed) {
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('x');  
      delay(200);
      Keyboard.releaseAll();
      button23Pressed = true;
    }
  } else {
    button23Pressed = false;
  }
  // buttom row 3
  //alt j 31
  if (digitalRead(buttonPin31) == LOW) {
    if (!button31Pressed) {
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('j');  
      delay(200);
      Keyboard.releaseAll();
      button31Pressed = true;
    }
  } else {
    button31Pressed = false;
  }

  //alt j 32
  if (digitalRead(buttonPin32) == LOW) {
    if (!button32Pressed) {
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('k');  
      delay(200);
      Keyboard.releaseAll();
      button32Pressed = true;
    }
  } else {
    button32Pressed = false;
  }

  //alt l 33
  if (digitalRead(buttonPin33) == LOW) {
    if (!button33Pressed) {
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('l');  
      delay(200);
      Keyboard.releaseAll();
      button33Pressed = true;
    }
  } else {
    button33Pressed = false;
  }
}
