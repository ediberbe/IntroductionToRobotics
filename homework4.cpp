#include <EEPROM.h>

//DS= [D]ata [S]torage - data
//STCP= [ST]orage [C]lock [P]in latch
//SHCP= [SH]ift register [C]lock [P]in clock
// Define Connections to 74HC595
const int latchPin = 11; // STCP to 12 on Shift Register
const int clockPin = 10; // SHCP to 11 on Shift Register
const int dataPin = 12; // DS to 14 on Shift Register
/*  See that the array is declared as int
*  The B in front is the binary representation of the int number
*  Instead of B11111100, which displays 0, we can write 252
*/
int digitArray[10] = {
  //A B C D E F G DP
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
};

const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;
int displayDigits[] = { segD1, segD2, segD3, segD4 };
const int displayCount = 4;

int arr[4] = { 0, 0, 0, 0};
int dotPos = 0;
int dotState = 1;

int VRx = A0;
int VRy = A1;
int SW = 2;
int xPosition = 0;
int yPosition = 0;
int SW_state = 1;

bool joyReady = true;
int SW_state_last = 1;

bool isSelected = false;
int blinkCycle = 500;
int blinkState = 1;

void setup () {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
  }

  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP); 

  arr[0] = EEPROM.read(0);
  arr[1] = EEPROM.read(1);
  arr[2] = EEPROM.read(2);
  arr[3] = EEPROM.read(3);
  
  Serial.begin(9600);
}

void loop() {
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);

  writeArray(arr);

  if(xPosition>100 && xPosition<900 && yPosition>100 && yPosition<900) joyReady = true;
  else if(joyReady == true){
    joyReady = false;
    
    if(xPosition<100 && !isSelected) {
      Serial.println("Joystick Left");
      if(dotPos == 0) dotPos = 3;
      else dotPos--;
    }
    if(xPosition>900 && !isSelected) {
      Serial.println("Joystick Right");
      if(dotPos == 3) dotPos = 0;
      else dotPos++;
    }
    
    if(yPosition<100 && isSelected) {
      Serial.println("Joystick Up");
      if(arr[dotPos] == 9) arr[dotPos] = 0;
      else arr[dotPos]++;
    }
    if(yPosition>900 && isSelected) {
      Serial.println("Joystick Down");
      if(arr[dotPos] == 0) arr[dotPos] = 9;
      else arr[dotPos]--;
    }
  }

  if(SW_state == 0 && SW_state_last == 1) {
    Serial.println("Press");
    if(isSelected == true) EEPROM.update(dotPos, arr[dotPos]);
    isSelected = !isSelected;
  }

  if(millis() % blinkCycle < blinkCycle/2) blinkState = 0;
  else blinkState = 1;
  Serial.println(blinkState);
  
  SW_state_last = SW_state;
}

void writeReg(int digit) { // Trimite din shift register in display ce numar vreau eu
  // ST_CP LOW to keep LEDs from changing while reading serial data
  digitalWrite(latchPin, LOW);
  // Shift out the bits
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  /* ST_CP on Rising to move the data from shift register
  * to storage register, making the bits available for output.
  */
  digitalWrite(latchPin, HIGH);
}

void showDigit(int displayNumber) { // Disable all digits si porneste segmentul care trebuie
  // first, disable all the display digits
  for (int i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], HIGH);
  }
  // then enable only the digit you want to use now
  digitalWrite(displayDigits[displayNumber], LOW);
}

void writeArray( int array[] ) {

  int currentDigit = 0;
  
  while(currentDigit != 4){
    showDigit(3-currentDigit);

    if(dotPos == currentDigit) {
      if(isSelected) writeReg(digitArray[arr[currentDigit]]+dotState*blinkState);
      else writeReg(digitArray[arr[currentDigit]]+dotState);
    }
    else writeReg(digitArray[arr[currentDigit]]);

    delay(5);
    currentDigit ++;
  }
  currentDigit = 0;
}