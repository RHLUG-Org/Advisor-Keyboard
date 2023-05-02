/*    INTERNET ADVISOR KEYBOARD CONTROL
 *
 *    Recieves encoded keypresses from the 2560 and uses the keyboard library to type them on the computer
 *
 *    Written by Nicco Scanu for the Rose-Hulman Linux User Group
 *    Based on the HID-Bridge USB example by NicoHood
 *
*/

#include "Keyboard.h"
#include "HID.h"
int incomingByte = 0; // for incoming serial data
const int NUM_GREEN = 14;
const int NUM_BLUE = 8;
int keyMap[NUM_GREEN][NUM_BLUE] = {
  {KEY_P, KEY_BACKSLASH, KEY_EQUALS, KEY_A, KEY_SEMICOLON, KEY_RETURN, KEY_A, KEY_A},
  {KEY_O, KEY_A, KEY_MINUS, KEY_A, KEY_L, KEY_BACKSLASH, KEY_A, KEY_A},
  {KEY_I, KEY_A, KEY_0, KEY_A, KEY_K, KEY_COMMA, KEY_SLASH, KEY_A},
  {KEY_U, KEY_H, KEY_9, KEY_A, KEY_J, KEY_M, KEY_PERIOD, KEY_A},
  {KEY_Y, KEY_G, KEY_8, KEY_A, KEY_F, KEY_N, KEY_A, KEY_A},
  {KEY_T, KEY_r, KEY_7, KEY_A, KEY_D, KEY_B, KEY_C, KEY_A},
  {KEY_4, KEY_E, KEY_6, KEY_A, KEY_S, KEY_V, KEY_X, KEY_SPACE},
  {KEY_A, KEY_A, KEY_A, KEY_A, KEY_A, KEY_A, KEY_A, KEY_A},
  {KEY_A, KEY_A, KEY_A, KEY_A, KEY_A, KEY_A, KEY_A, KEY_A},
  {KEY_3, KEY_W, KEY_5, KEY_A, KEY_A, KEY_SPACE, KEY_Z, KEY_SPACE},
  {KEY_2, KEY_Q, KEY_A, KEY_A, KEY_A, KEY_1, KEY_A, KEY_A},
  {KEY_A, KEY_A, KEY_A, KEY_A, KEY_A, KEY_A, KEY_A, KEY_A},
  {KEY_A, KEY_A, KEY_A, KEY_A, KEY_A, KEY_A, KEY_A, KEY_A},
  {KEY_A, KEY_A, KEY_A, KEY_A, KEY_A, KEY_A, KEY_A, KEY_A},
};

void setup() {
  // Start the Serial1 which is connected with the IO MCU.
  // Make sure both baud rates are the same
  // you can go up to 2000000 for very fast data transmission.
  Serial1.begin(115200);

  // Sends a clean report to the host. This is important on any Arduino type.
  Keyboard.begin();

  // Start the USB Serial for debugging
  Serial.begin(115200);
  delay(500);
  Serial.println("USB MCU Reporting for duty");
}

void loop() {
  // Check if any Serial data from the IO MCU was received
  //char c = Serial1.read();

  // If it's a character, print it!
  //if (c >= 'a' && c <= 'z') {
   // Serial.print(F("USB: "));
  //  Serial.println(c);
  //  Keyboard.print(c);
  //}
  if (Serial1.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial1.read();

    // say what you got:
    Serial.print(F("[IO MCU]: "));
    Serial.write(incomingByte);
    Serial.print("\n");
  }

}
