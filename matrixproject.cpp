#include <LiquidCrystal.h>
#include "LedControl.h"

//================PINS================

//display
const int RS = 7;
const int enable = 6;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;

//joystick
const int VRx = A0;
const int VRy = A1;
const int SW = 0;

//matrix
const int dinPin = 12;
const int clockPin = 11;
const int loadPin = 10;

//================VAR================

int state = 9;
String username = "john";
int difficulty = 0;

//display
LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);

//menu
int menuSelection = 0;

String menuMain[5] = {"Start game", "Highscore", "Settings", "About", ""};
int menuMainCount = 4;

String menuSettings[3] = {"Change name", "Set Difficulty", ""};
int menuSettingsCount = 2;

String menuAbout[4] = {"Snake", "Edi Berbescu", "https://github.com/ediberbe", ""};
int menuAboutCount = 3;

//highscores
String highNames[3] = {"andr", "miha", "radu"};
int highScores[3] = {6, 4, 2};

//joystick
int xPosition = 0;
int yPosition = 0;
int SW_state = 1;
bool joyReady = true;
int SW_state_last = 1;

//matrix
LedControl lc = LedControl(dinPin, clockPin, loadPin, 1); //DIN, CLK, LOAD, No. DRIVER

byte matrixBrightness = 2;
byte moveInterval = 150;
unsigned long long lastMoved = 0;
const byte matrixSize = 8;
bool matrixChanged = true;

bool matrix[matrixSize][matrixSize] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

//snake
int xPos = 0;
int yPos = 0;
int yVel = 0;
int xVel = 0;

int xFood = 7;
int yFood = 0;
int score = 0;

//================FUNC================

void updateMatrix() {
  for (int row = 0; row < matrixSize; row++) {
    for (int col = 0; col < matrixSize; col++) {
      lc.setLed(0, row, col, matrix[row][col]);
    }
  }
}

void updatePositions() {
  matrix[xPos][yPos] = 0;
  matrixChanged = true;

  xPos = xPos + yVel;
  yPos = yPos + xVel;

  if(xPos<0 || xPos>7 || yPos<0 || yPos>7){
    // DEATH
    state = 9;
    menuSelection = 0;
    xPos = 0;
    yPos = 0;
    yVel = 0;
    xVel = 0;
    matrix[xFood][yFood] = 0;
    xFood = 7;
    yFood = 0;
    
    //HIGHSCORES
    if(score >= highScores[0]){
      highScores[2] = highScores[1];
      highNames[2] = highNames[1];
      highScores[1] = highScores[0];
      highNames[1] = highNames[0];
      highNames[0] = username;
      highScores[0] = score;
    }

    else if(score >= highScores[1]){
      highScores[2] = highScores[1];
      highNames[2] = highNames[1];
      highNames[1] = username;
      highScores[1] = score;
    }

    else if(score >= highScores[2]){
      highNames[2] = username;
      highScores[2] = score;
    }

    score = 0;
  }
  else matrix[xPos][yPos] = 1;
}

void joystickMovement() {
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
      
  if(xPosition<200 && xVel != 1) {
    Serial.println("Joystick Left");
    yVel = 0;
    xVel = -1;
  }

  if(xPosition>800 && xVel != -1) {
    Serial.println("Joystick Right");
    yVel = 0;
    xVel = 1;
  }
        
  if(yPosition<200 && yVel != 1) {
    Serial.println("Joystick Up");
    yVel = -1;
    xVel = 0;
  }

  if(yPosition>800 && yVel != -1) {
    Serial.println("Joystick Down");
    yVel = 1;
    xVel = 0;
  }

  if(SW_state == 0 && SW_state_last == 1) {
    Serial.println("Press");
  }
  SW_state_last = SW_state;
}

void updateFood() {
  matrix[xFood][yFood] = 1;
  if(xPos == xFood && yPos == yFood){
    score++;
    xFood = random(0, 7);
    yFood = random(0, 7);
    matrix[xFood][yFood] = 1;
    matrixChanged = true;
  }
}

void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Score: ");
  lcd.print(score);

}

//================MAIN================

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);

  //MATRIX
  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, matrixBrightness); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
  matrix[xPos][yPos] = 1;
}

void loop() {

  switch (state) {
    case 9: //================mainmenu================
      Serial.println("Main Menu");
      
      lcd.setCursor(0, 0);
      lcd.print(menuMain[menuSelection]);
      lcd.setCursor(0, 1);
      lcd.print(menuMain[menuSelection+1]);
      
      xPosition = analogRead(VRx);
      yPosition = analogRead(VRy);
      SW_state = digitalRead(SW);
      
      if(xPosition>100 && xPosition<900 && yPosition>100 && yPosition<900) joyReady = true;
      else if(joyReady == true){
        joyReady = false;
        lcd.clear();

        if(xPosition<100) {
          Serial.println("Joystick Left");
        }

        if(xPosition>900) {
          Serial.println("Joystick Right");    
          state = menuSelection;
          menuSelection = 0;
          lastMoved = millis();
        }

        if(yPosition<100) {
          Serial.println("Joystick Up");
          if(menuSelection != 0) menuSelection--;
        }

        if(yPosition>900) {
          Serial.println("Joystick Down");
          if(menuSelection != menuMainCount-1) menuSelection++;
        }
      }

      if(SW_state == 0 && SW_state_last == 1) {
        Serial.println("Press");
      }
      SW_state_last = SW_state;
      
      break;

    case 0: //================Start game================
      joystickMovement();

      if (millis() - lastMoved > moveInterval) {
        updateFood();
        updatePositions();
        lastMoved = millis();
        updateLCD();
      }

      if (matrixChanged == true) {
        updateMatrix();
        matrixChanged = false;
      }

      break;

    case 1: //================Highscore================
      Serial.println("Highscore");

      lcd.setCursor(0, 0);
      lcd.print(highNames[menuSelection]);
      lcd.print(": ");
      lcd.print(highScores[menuSelection]);
      lcd.setCursor(0, 1);
      lcd.print(highNames[menuSelection+1]);
      lcd.print(": ");
      lcd.print(highScores[menuSelection+1]);
      
      xPosition = analogRead(VRx);
      yPosition = analogRead(VRy);
      SW_state = digitalRead(SW);
      
      if(xPosition>100 && xPosition<900 && yPosition>100 && yPosition<900) joyReady = true;
      else if(joyReady == true){
        joyReady = false;
        lcd.clear();
        
        if(xPosition<100) {
          Serial.println("Joystick Left");
          state = 9;
          menuSelection = 0;
        }

        if(xPosition>900) {
          Serial.println("Joystick Right");
        }
        
        if(yPosition<100) {
          Serial.println("Joystick Up");
          if(menuSelection != 0) menuSelection--;
        }

        if(yPosition>900) {
          Serial.println("Joystick Down");
          if(menuSelection != 1) menuSelection++;
        }
      }

      if(SW_state == 0 && SW_state_last == 1) {
        Serial.println("Press");
      }
      SW_state_last = SW_state;

      break;
      
    case 2: //================Settings================
      Serial.println("Settings");

      lcd.setCursor(0, 0);
      lcd.print(menuSettings[menuSelection]);
      lcd.setCursor(0, 1);
      lcd.print(menuSettings[menuSelection+1]);
      
      xPosition = analogRead(VRx);
      yPosition = analogRead(VRy);
      SW_state = digitalRead(SW);
      
      if(xPosition>100 && xPosition<900 && yPosition>100 && yPosition<900) joyReady = true;
      else if(joyReady == true){
        joyReady = false;
        lcd.clear();

        if(xPosition<100) {
          Serial.println("Joystick Left");
          state = 9;
          menuSelection = 0;
        }

        if(xPosition>900) {
          Serial.println("Joystick Right");
          if(menuSelection == 0) state = 10; //Settings-Name
          if(menuSelection == 1) state = 11; //Settings-Difficulty
          menuSelection = 0;
        }

        if(yPosition<100) {
          Serial.println("Joystick Up");
          if(menuSelection != 0) menuSelection--;
        }

        if(yPosition>900) {
          Serial.println("Joystick Down");
          if(menuSelection != menuSettingsCount-1) menuSelection++;
        }
      }

      if(SW_state == 0 && SW_state_last == 1) {
        Serial.println("Press");
      }
      SW_state_last = SW_state;

      break;
      
    case 3: //================About================
      Serial.println("About");

      lcd.setCursor(0, 0);
      lcd.print(menuAbout[menuSelection]);
      lcd.setCursor(0, 1);
      lcd.print(menuAbout[menuSelection+1]);
      
      if((menuAbout[menuSelection].length() > 16 || menuAbout[menuSelection+1].length() > 16)
          && millis() - lastMoved > 500){
        lcd.scrollDisplayLeft();
        lastMoved = millis();
      }

      xPosition = analogRead(VRx);
      yPosition = analogRead(VRy);
      SW_state = digitalRead(SW);
      
      if(xPosition>100 && xPosition<900 && yPosition>100 && yPosition<900) joyReady = true;
      else if(joyReady == true){
        joyReady = false;
        lcd.clear();
        lastMoved = millis();
        
        if(xPosition<100) {
          Serial.println("Joystick Left");
          state = 9;
          menuSelection = 0;
        }

        if(xPosition>900) {
          Serial.println("Joystick Right");
        }
        
        if(yPosition<100) {
          Serial.println("Joystick Up");
          if(menuSelection != 0) menuSelection--;
        }

        if(yPosition>900) {
          Serial.println("Joystick Down");
          if(menuSelection != menuAboutCount-1) menuSelection++;
        }
      }

      if(SW_state == 0 && SW_state_last == 1) {
        Serial.println("Press");
      }
      SW_state_last = SW_state;

      break;
      
    case 10: //================Settings-Name================
      Serial.println("Settings-Name");

      lcd.setCursor(0, 0);
      lcd.print(username);
      lcd.setCursor(menuSelection, 1);
      lcd.print('X');
    
      xPosition = analogRead(VRx);
      yPosition = analogRead(VRy);
      SW_state = digitalRead(SW);
      
      if(xPosition>100 && xPosition<900 && yPosition>100 && yPosition<900) joyReady = true;
      else if(joyReady == true){
        joyReady = false;
        lcd.clear();

        if(xPosition<100) {
          Serial.println("Joystick Left");
          if(menuSelection != 0) menuSelection--;
        }

        if(xPosition>900) {
          Serial.println("Joystick Right");
          if(menuSelection != 15) menuSelection++;
        }

        if(yPosition<100) {
          Serial.println("Joystick Up");
          username[menuSelection]--;
        }

        if(yPosition>900) {
          Serial.println("Joystick Down");
          username[menuSelection]++;
        }
      }

      if(SW_state == 0 && SW_state_last == 1) {
        Serial.println("Press");
        state = 2;
        menuSelection = 0;
      }
      SW_state_last = SW_state;
      break;

    case 11: //================Settings-Difficulty================
      Serial.println("Settings-Difficulty");

      lcd.setCursor(0, 0);
      lcd.print(difficulty);
    
      xPosition = analogRead(VRx);
      yPosition = analogRead(VRy);
      SW_state = digitalRead(SW);
      
      if(xPosition>100 && xPosition<900 && yPosition>100 && yPosition<900) joyReady = true;
      else if(joyReady == true){
        joyReady = false;
        lcd.clear();

        if(xPosition<100) {
          Serial.println("Joystick Left");
        }

        if(xPosition>900) {
          Serial.println("Joystick Right");
        }

        if(yPosition<100) {
          Serial.println("Joystick Up");
          if(difficulty != 2) difficulty++;
        }

        if(yPosition>900) {
          Serial.println("Joystick Down");
          if(difficulty != 0) difficulty--;
        }
      }

      if(SW_state == 0 && SW_state_last == 1) {
        Serial.println("Press");
        state = 2;
        menuSelection = 0;

        if(difficulty == 0) moveInterval = 200;
        else if(difficulty == 1) moveInterval = 150;
        else if(difficulty == 2) moveInterval = 100;
      }
      SW_state_last = SW_state;
      break;
  }
  
}