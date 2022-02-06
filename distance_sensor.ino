#include <LiquidCrystal.h>
LiquidCrystal lcd(5, 4, A0, A1, A2, A3);
int trig1 = 13, echo1 = 12, trig2 = 11, echo2 = 10;
int trig3 = 9, echo3 = 8, trig4 = 7, echo4 = 6;
int buz = 3;
long duration, distance, minDist;
int sensorNbr;

void SonarSensor(int trigPin,int echoPin)
{
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin, HIGH);
	distance = (duration/2) / 29;
}


void setup()
{
  Serial.begin(9600);
  minDist = 10000;
  sensorNbr = 0;
  lcd.begin(16,2);
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo3, INPUT);
  pinMode(trig4, OUTPUT);
  pinMode(echo4, INPUT);  

}

void loop()
{
  minDist=10000;
  SonarSensor(trig1, echo1);
  if(distance < minDist)
  {
  	minDist = distance;
    sensorNbr = 1;
  }
  SonarSensor(trig2, echo2);
  if(distance < minDist)
  {
  	minDist = distance;
    sensorNbr = 2;
  }
  SonarSensor(trig3, echo3);
  if(distance < minDist)
  {
  	minDist = distance;
    sensorNbr = 3;
  }
  SonarSensor(trig4, echo4);
  if(distance < minDist)
  {
  	minDist = distance;
    sensorNbr = 4;
  }
  if(minDist <= 20){
  	tone(buz, 1000);
    delay(100);
    noTone(buz);
  }
  else if(minDist > 20 && minDist < 50){
    tone(buz, 1000);
    delay(500);
    noTone(buz);
  }
  else{
    tone(buz, 1000);
    delay(1000);
    noTone(buz);
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Min. Dist: ");
  lcd.print(minDist);
  lcd.setCursor(0,1);
  lcd.print("Sensor: ");
  lcd.print(sensorNbr);
}