/*    INTERNET ADVISOR KEYBOARD DECODER
 *
 *    Reads the pins from the advisor's keyboard and determine which key is pressed. Then sends the info to the 16U2.
 *
 *    Written by Nicco Scanu and Andrew Grasman for the Rose-Hulman Linux User Group
 *
*/



#include <Adafruit_NeoPixel.h>
#include <Keyboard.h>

#define LED_PIN 26
#define LED_COUNT 30

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

const int NUM_GREEN = 14;
const int NUM_BLUE = 8;
int greenPins[NUM_GREEN] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
int bluePins[NUM_BLUE] = {15, 16, 17, 18, 19, 20, 21, 22};
char keyMap[NUM_GREEN][NUM_BLUE] = { //Map keys to ASCII character and Keyboard.h codes https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/
  {'p', '\\', KEY_LEFT_CTRL, 207, ';', 176, 218, 217},
  {KEY_F3, KEY_F1, KEY_ESC, KEY_F2, '1', KEY_F4, '2', 'q'},
  {'5', 'z', KEY_TAB, 'a', KEY_CAPS_LOCK, KEY_F5, '3', 'w'},
  {'u', 'h', KEY_F24, 202, 'j', 'm', '.', 209},
  {'y', 'g', KEY_LEFT_ALT, 201, 'f', 'n', 'a', '`'},
  {'6', 'x', ' ', 's', 'v', KEY_F6, '4', 'e'},
  {'7', 'c', '6', 'd', 'b', KEY_F7, 't', 'r'},
  {'8', 'a', '`', 'f', 'n', KEY_F8, 'y', 'g'},
  {'9', '.', 'a', 'j', 'm', KEY_F9, 'u', 'h'},
  {'0', '/', '5', 'k', ',', KEY_F10, 'i', '['},
  {'-', 'q', KEY_LEFT_ARROW, 'l', '\'', KEY_NUM_LOCK, 'o', ']'},
  {'+', KEY_UP_ARROW, KEY_DOWN_ARROW, ';', KEY_RETURN, KEY_SCROLL_LOCK, 'p', '\\'},
  {'a', KEY_RIGHT_SHIFT, KEY_LEFT_SHIFT, 'a', 'a', 'a', 133, 129},
  {KEY_PAUSE, KEY_END, KEY_RIGHT_ARROW, KEY_PAGE_UP, KEY_PAGE_DOWN, KEY_PRINT_SCREEN, KEY_BACKSPACE, KEY_HOME},
};

char functionMap[NUM_GREEN][NUM_BLUE] = { //Alternate map to be used when the FN key is pressed
  {'p', '\\', KEY_LEFT_CTRL, 207, ';', 176, 218, 217},
  {KEY_F13, KEY_F11, KEY_ESC, KEY_F12, '1', KEY_F14, '2', 'q'},
  {'5', 'z', KEY_TAB, 'a', KEY_CAPS_LOCK, KEY_F15, '3', 'w'},
  {'u', 'h', KEY_F24, 202, 'j', 'm', KEY_KP_DOT, 209},
  {'y', 'g', KEY_LEFT_ALT, 201, 'f', 'n', 'a', '`'},
  {'6', 'x', ' ', 's', 'v', KEY_F16, '4', 'e'},
  {KEY_KP_7, 'c', '6', 'd', 'b', KEY_F17, 't', 'r'},
  {KEY_KP_8, 'a', '`', 'f', 'n', KEY_F18, 'y', 'g'},
  {KEY_KP_9, '.', 'a', KEY_KP_1, KEY_KP_0, KEY_F19, KEY_KP_4, 'h'},
  {KEY_KP_ASTERISK, KEY_KP_SLASH, '5', KEY_KP_2, ',', KEY_F20, KEY_KP_5, '['},
  {'-', 'q', KEY_LEFT_ARROW, KEY_KP_3, '\'', KEY_NUM_LOCK, KEY_KP_6, ']'},
  {'+', KEY_UP_ARROW, KEY_DOWN_ARROW, KEY_KP_PLUS, KEY_RETURN, KEY_SCROLL_LOCK, KEY_KP_MINUS, '\\'},
  {'a', KEY_RIGHT_SHIFT, KEY_LEFT_SHIFT, 'a', 'a', 'a', 133, 129},
  {KEY_PAUSE, KEY_END, KEY_RIGHT_ARROW, KEY_PAGE_UP, KEY_PAGE_DOWN, KEY_PRINT_SCREEN, KEY_BACKSPACE, KEY_HOME},
};

const int FN_GREEN = 3;
const int FN_BLUE = 2;

int pressed[NUM_GREEN][NUM_BLUE];
char sentKey[NUM_GREEN][NUM_BLUE]; // HID code actually sent for this matrix position

char keyForPosition(int g, int b) {
  if(pressed[FN_GREEN][FN_BLUE] == 1){
    return functionMap[g][b];
  }
  return keyMap[g][b];
}

void setup() {
  Serial.begin(115200);
  delay(100);
  
  // Sends a clean report to the host. This is important on any Arduino type.
  Keyboard.begin();

  // Idle columns as high-Z so holding one key does not fight other columns.
  for(int i = 0; i < NUM_BLUE; i++){
      digitalWrite(bluePins[i], LOW);
      pinMode(bluePins[i], INPUT);
  }
  for(int i = 0; i < NUM_GREEN; i++){
     pinMode(greenPins[i], INPUT_PULLUP);
  }
  for(int g = 0; g < NUM_GREEN; g++){
    for(int b = 0; b < NUM_BLUE; b++){
      pressed[g][b] = 0;
      sentKey[g][b] = 0;
    }
  }

  strip.begin();
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(50 * (i % 2), 50 * ((i + 1) % 2), 0)); // Red color
  }
  strip.show();
}

void releaseAllKeys() {
  for(int g = 0; g < NUM_GREEN; g++){
    for(int b = 0; b < NUM_BLUE; b++){
      if(pressed[g][b] == 1){ //Release any key currently pressed through software
        Keyboard.release(sentKey[g][b]);
        Serial.printf("(%d, %d) released\n", g, b);
      }
      pressed[g][b] = 0;
      sentKey[g][b] = 0;
    }
  }
}

void loop() {
  for(int i = 0; i < NUM_BLUE; i++) {
    pinMode(bluePins[i], OUTPUT);
    digitalWrite(bluePins[i], LOW);
    delayMicroseconds(10);

    for(int j = 0; j < NUM_GREEN; j++){
      bool isDown = !digitalRead(greenPins[j]);

      if(isDown){
        if(pressed[j][i] == 0){
          if(j == FN_GREEN && i == FN_BLUE){//FN was just pressed
            releaseAllKeys();
          }

          char keyToPress = keyForPosition(j, i);
          Keyboard.press(keyToPress);
          sentKey[j][i] = keyToPress;
          pressed[j][i] = 1;
          Serial.printf("%c (%d, %d) pressed\n", keyToPress, j, i);
        }
      } else if(pressed[j][i] == 1){
        if(j == FN_GREEN && i == FN_BLUE){//FN was just released
          releaseAllKeys();
        } else {
          Keyboard.release(sentKey[j][i]);
          Serial.printf("%c (%d, %d) released\n", sentKey[j][i], j, i);
          pressed[j][i] = 0;
          sentKey[j][i] = 0;
        }
      }
    }

    pinMode(bluePins[i], INPUT); // high-Z so other columns can be scanned independently
  }
}
