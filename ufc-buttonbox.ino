#include <Keypad.h>
#include <Joystick.h> // From https://github.com/MHeironimus/ArduinoJoystickLibrary

//Keypad definition:

//set up the matrix dimensions
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns

//define the mapping of key position to joystick button number:
byte hexaKeys[ROWS][COLS] = {
  {0,1,2},
  {3,4,5},
  {6,7,8},
  {9,10,11}
};
byte rowPins[ROWS] = {6, 7, 8, 9}; //connect to the row pinouts of the keypad - numbers are the gpio ports
byte colPins[COLS] = {3, 4, 5}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad buttbx = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

//Toggle switch matrix definition:
const byte swROWS = 2;
const byte swCOLS = 2;
//define the cymbols on the buttons of the keypads
byte swKeys[swROWS][swCOLS] = {
  {12,13},
  {14,15}
};
byte swrowPins[swROWS] = {14,15};
byte swcolPins[swCOLS] = {10,16};

//initialize an instance of class NewKeypad
Keypad swbutt = Keypad( makeKeymap(swKeys), swrowPins, swcolPins, swROWS, swCOLS); 

//initialize a joystick
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_JOYSTICK, 16, 0,
  false, false, false, false, false, false,
  false, false, false, false, false);

void setup(){
  Joystick.begin();
  // Serial.begin(9600); //for debugging
}
  
void loop(){
  CheckAllButtons();
  CheckToggles();
}

void CheckAllButtons(void) {
  if (buttbx.getKeys())
  {
    for (int i=0; i<LIST_MAX; i++)   
    {
      if ( buttbx.key[i].stateChanged )   
      {
        switch (buttbx.key[i].kstate) {  
                case PRESSED:
                          // Serial.println("pressed");
                case HOLD:
                          // Serial.println("hold ");
                          // Serial.println(buttbx.key[i].kchar);
                          Joystick.setButton(buttbx.key[i].kchar, 1);
                          break;
                case RELEASED:
                          // Serial.println("released");
                case IDLE:
                          // Serial.println("idle");
                          Joystick.setButton(buttbx.key[i].kchar, 0);
                          break;
        }
      }   
    }
  }
}

void CheckToggles(void) {
  if (swbutt.getKeys())
  {
    for (int i=0; i<LIST_MAX; i++)   
    {
      if ( swbutt.key[i].stateChanged )   
      {
        switch (swbutt.key[i].kstate) {  
                case PRESSED:
                          // Serial.println("pressed toggle");
                case HOLD:
                          // Serial.println("hold toggle");
                          // Serial.println(buttbx.key[i].kchar);
                          Joystick.setButton(swbutt.key[i].kchar, 1);
                          break;
                case RELEASED:
                          // Serial.println("released toggle");
                case IDLE:
                          // Serial.println("idle toggle");
                          Joystick.setButton(swbutt.key[i].kchar, 0);
                          break;
        }
      }   
    }
  }
}
