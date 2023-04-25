//#include "Adafruit_Keypad.h"

/*const byte ROWS = 8; // rows
const byte COLS = 14; // columns
//define the symbols on the buttons of the keypads
char keys[ROWS][COLS] = {
  {'1','2','3','a', '1','2','3','a', '1','2','3','a', '1','2'},
  {'1','2','3','a', '1','2','3','a', '1','2','3','a', '1','2'},
  {'1','2','3','a', '1','2','3','a', '1','2','3','a', '1','2'},
  {'1','2','3','a', '1','2','3','a', '1','2','3','a', '1','2'},
  {'1','2','3','a', '1','2','3','a', '1','2','3','a', '1','2'},
  {'1','2','3','a', '1','2','3','a', '1','2','3','a', '1','2'},
  {'1','2','3','a', '1','2','3','a', '1','2','3','a', '1','2'},
  {'1','2','3','a', '1','2','3','a', '1','2','3','a', '1','2'},
};
byte rowPins[ROWS] = {18, 19, 20, 21, 22, 23, 24, 25}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {15, 14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Adafruit_Keypad customKeypad = Adafruit_Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);*/

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
  //customKeypad.begin();
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
  /*// put your main code here, to run repeatedly:
  customKeypad.tick();

  while(customKeypad.available()){
    keypadEvent e = customKeypad.read();
    Serial.write((char)e.bit.KEY);
    if(e.bit.EVENT == KEY_JUST_PRESSED){
      Serial.println(" pressed");
    } else if(e.bit.EVENT == KEY_JUST_RELEASED){
      Serial.println(" released");
    }
  }*/

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
