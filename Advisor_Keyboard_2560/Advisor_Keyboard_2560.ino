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
  {'p', '\\', '=', 'a', ';', '\n', 'a', 'a'},
  {'o', 'a', '-', 'a', 'l', '\'', 'a', 'a'},
  {'i', 'a', '0', 'a', 'k', ',', '/', 'a'},
  {'u', 'h', '9', 'a', 'j', 'm', '.', 'a'},
  {'y', 'g', '8', 'a', 'f', 'n', 'a', 'a'},
  {'t', 'r', '7', 'a', 'd', 'b', 'c', 'a'},
  {'4', 'e', '6', 'a', 's', 'v', 'x', ' '},
  {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
  {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
  {'3', 'w', '5', 'a', 'a', ' ', 'z', ' '},
  {'2', 'q', 'a', 'a', 'a', '1', 'a', 'a'},
  {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
  {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
  {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'},
};

int pressed[NUM_GREEN][NUM_BLUE];

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
  for(int g = 0; g < NUM_GREEN; g++){
    for(int b = 0; b < NUM_BLUE; b++){
      pressed[g][b] = 0;
    }
  }
}

void loop() {

  for(int i = 0; i < NUM_BLUE; i++) {
    digitalWrite(bluePins[i], LOW);
    for(int j = 0; j < NUM_GREEN; j++){
       if(!digitalRead(greenPins[j])){
        if(pressed[j][i] == 0){
          Serial.println("?")
          Serial.println(i);
          Serial.println(j);
          Serial.println("?");
          pressed[j][i] = 1;
        }
        /*Serial.print("(");
        Serial.print(j);
        Serial.print(", ");
        Serial.print(i);
        Serial.print(") pressed\n");*/
        
        //Serial.write('\n');
       } else {
        pressed[j][i] = 0;
       }
    }
    digitalWrite(bluePins[i], HIGH);
  } 
}
