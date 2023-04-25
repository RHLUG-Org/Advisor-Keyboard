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
    Serial.println(incomingByte, DEC);
  }

}
