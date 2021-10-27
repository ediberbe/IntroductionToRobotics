const int p1Out = 13;
const int p2Out = 12;
const int p3Out = 8;

const int p1In = A0;
const int p2In = A1;
const int p3In = A2;

int vRead1, vRead2, vRead3;
float vWrite1, vWrite2, vWrite3;

const int ledPinRed = 6;
const int ledPinGreen = 5;
const int ledPinBlue = 3;

const int maxVoltageValue = 1023;
const int maxLedBrightness = 255;

void setup() {
  // put your setup code here, to run once:
  pinMode(p1Out,OUTPUT);
  pinMode(p2Out,OUTPUT);
  pinMode(p3Out,OUTPUT);
  pinMode(p1In,INPUT);
  pinMode(p2In,INPUT);
  pinMode(p3In,INPUT);
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinBlue, OUTPUT);

  digitalWrite(p1Out, HIGH);
  digitalWrite(p2Out, HIGH);
  digitalWrite(p3Out, HIGH);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  vRead1 = analogRead(p1In);
  vWrite1 = map(vRead1, 0, maxVoltageValue, 0, maxLedBrightness);
  analogWrite(ledPinRed,vWrite1);
  delay(1);
  
  vRead2 = analogRead(p2In);
  vWrite2 = map(vRead2, 0, maxVoltageValue, 0, maxLedBrightness);
  analogWrite(ledPinGreen,vWrite2);
  delay(1);
  
  vRead3 = analogRead(p3In);
  vWrite3 = map(vRead3, 0, maxVoltageValue, 0, maxLedBrightness);
  analogWrite(ledPinBlue,vWrite3);
  delay(1);
}

