const int ledPinRed = 13;
const int ledPinYellow = 12;
const int ledPinGreen = 11;

const int ledPinRed2 = 7;
const int ledPinGreen2 = 6;

int state = 1;

//stuff to make the button behave how it should:
const int buttonPin = 2;
bool buttonState = 0; 
bool reading = LOW;
bool lastReading = HIGH;
unsigned int lastDebounceTime = 0;
unsigned int debounceDelay = 50;

unsigned int timerStart = 0;
unsigned int state2Duration = 3000;
unsigned int state3Duration = 10000;
unsigned int state4Duration = 5000;

unsigned int buzzerTimerStart = 0;
const int buzzerPin = 8;
int buzzTone = 500;

unsigned int buzzerTime = 1000;
unsigned int buzzTime = 500;

unsigned int buzzerTime2 = 500;
unsigned int buzzTime2 = 250;

unsigned int blinkerTimerStart = 0;
unsigned int blinkTime = 250;
bool blinkState = HIGH;


void setup() {
  // put your setup code here, to run once:
  pinMode(ledPinRed,OUTPUT);
  pinMode(ledPinYellow,OUTPUT);
  pinMode(ledPinGreen,OUTPUT);
  pinMode(ledPinRed2,OUTPUT);
  pinMode(ledPinGreen2,OUTPUT);
  pinMode(buttonPin,INPUT_PULLUP);
  pinMode(buzzerPin,OUTPUT);

  digitalWrite(ledPinRed, LOW);
  digitalWrite(ledPinYellow, LOW);
  digitalWrite(ledPinGreen, LOW);
  digitalWrite(ledPinRed2, LOW);
  digitalWrite(ledPinGreen2, LOW);
  
  Serial.begin(9600);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  reading = digitalRead(buttonPin);
  
  if (reading != lastReading){
    lastDebounceTime = millis();
    }
    
  if(millis() - lastDebounceTime > debounceDelay){
    if(reading != buttonState){
      buttonState = reading;
      if(buttonState == LOW){
        // On button press
        Serial.println("Press");
        if(state == 1) {
          state = 2;
          timerStart = millis();
        }
      }
    }
  }

  switch(state){
    case 1:
      digitalWrite(ledPinRed, LOW);
      digitalWrite(ledPinYellow, LOW);
      digitalWrite(ledPinGreen, HIGH);
      digitalWrite(ledPinRed2, HIGH);
      digitalWrite(ledPinGreen2, LOW);
      digitalWrite(buzzerPin, LOW);
      break;
    case 2:
      digitalWrite(ledPinRed, LOW);
      digitalWrite(ledPinYellow, HIGH);
      digitalWrite(ledPinGreen, LOW);
      digitalWrite(ledPinRed2, HIGH);
      digitalWrite(ledPinGreen2, LOW);
      digitalWrite(buzzerPin, LOW);
      if(millis()-timerStart > state2Duration){
        state = 3;
        timerStart = millis();
        buzzerTimerStart = millis();
      }
      break;
    case 3:
      digitalWrite(ledPinRed, HIGH);
      digitalWrite(ledPinYellow, LOW);
      digitalWrite(ledPinGreen, LOW);
      digitalWrite(ledPinRed2, LOW);
      digitalWrite(ledPinGreen2, HIGH);
      if(millis()- buzzerTimerStart > buzzerTime){
        Serial.println("Buzz");
        tone(buzzerPin, buzzTone, buzzTime);
        buzzerTimerStart = millis();
      }
      if(millis()-timerStart > state3Duration){
        state = 4;
        timerStart = millis();
        buzzerTimerStart = millis();
        blinkerTimerStart = millis();
      }
      break;
    case 4:
      if(millis()- blinkerTimerStart > blinkTime){
        if(blinkState == HIGH) blinkState = LOW;
        else blinkState = HIGH;

        digitalWrite(ledPinGreen2, blinkState);
        blinkerTimerStart = millis();
      }
      
      if(millis()- buzzerTimerStart > buzzerTime2){
        Serial.println("Buzz");
        tone(buzzerPin, buzzTone, buzzTime2);
        buzzerTimerStart = millis();
      }
      if(millis()-timerStart > state4Duration){
        state = 1;
        timerStart = millis();
      }
      break;
    }

  lastReading = reading;
}
