/*    INTERNET ADVISOR KEYBOARD DECODER
 *
 *    Reads the pins from the advisor's keyboard and determine which key is pressed. Then sends the info to the 16U2.
 *
 *    Written by Nicco Scanu for the Rose-Hulman Linux User Group
 *
*/
const int NUM_GREEN = 14;
const int NUM_BLUE = 8;
int greenPins[NUM_GREEN] = {2, 20, 4, 5, 16, 7, 8, 9, 10, 11, 12, 13, 14, 15};
int bluePins[NUM_BLUE] = {18, 19, 17, 21, 22, 23, 24, 25};
char keyMap[NUM_GREEN][NUM_BLUE] = {
  {'p', 'a', '=', 'a', 'a', 'a', 'a', 'a'},
  {'o', 'a', '-', 'a', 'a', 'a', 'a', 'a'},
  {'i', 'a', '0', 'a', 'a', 'a', 'a', 'a'},
  {'u', 'a', '9', 'a', 'a', 'a', 'a', 'a'},
  {'y', 'a', '8', 'a', 'a', 'a', 'a', 'a'},
  {'t', 'r', '7', 'a', 'a', 'a', 'a', 'a'},
  {'4', 'e', '6', 'a', 'a', 'a', 'a', 'a'},
  {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
  {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
  {'3', 'w', '5', 'a', 'a', ' ', 'z', ' '},
  {'2', 'q', 'a', 'a', 'a', '1', 'a', 'a'},
  {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
  {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
  {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
};

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("IO MCU Reporting for duty.");
  for(int i = 0; i < NUM_BLUE; i++){
      pinMode(bluePins[i], OUTPUT);
  }
  for(int i = 0; i < NUM_GREEN; i++){
     pinMode(greenPins[i], INPUT_PULLUP);
  }
}

void loop() {

  for(int i = 0; i < NUM_BLUE; i++) {
    digitalWrite(bluePins[i], LOW);
    for(int j = 0; j < NUM_GREEN; j++){
       if(!digitalRead(greenPins[j])){
        Serial.print("(");
        Serial.print(j);
        Serial.print(", ");
        Serial.print(i);
        Serial.print(") pressed\n");
        Serial.write(keyMap[j][i]);
        Serial.write('\n');
       }
    }
    digitalWrite(bluePins[i], HIGH);
  }
  delay(10);
}
