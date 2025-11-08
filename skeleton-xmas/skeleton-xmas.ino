#include <Servo.h>

const int countLed = 3;
const int firstLed = 3;
const int pingPin = 6;
const int servoPin = 11;

Servo jaw;

int count = 0;
const int blinkTime = 750 - 200;//milliseconds, 
//don't change the 200, it is the ultrasonic sensor delay
long duration;
float distanceCm;

void setup()
{
  for (int i = 0; i<countLed;i++)
  {
  	pinMode(firstLed + i, OUTPUT);
  }
  
  jaw.attach(servoPin);
  Serial.begin(9600);
}	

void loop()
{
  
  digitalWrite(count + firstLed, HIGH);
  delay(blinkTime); 
  digitalWrite(count + firstLed, LOW);

  count++;
  if(count > countLed -1)
  {
  	count = 0;
  }
  
  //ultrasonic sensor
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  distanceCm = duration / 29.1 / 2;

  if (distanceCm > 0 && distanceCm <= 120) {
    //Action
    Serial.println("I see you!");
    jaw.write(90);
    delay(1000);
    jaw.write(0);
  }
  
  delay(200);
}
