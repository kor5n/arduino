const int sensorPin = A0;
const float baselineTemp = 22.0;

void setup(){
  Serial.begin(9600);

  for(int i = 2; i<5; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }

}

void loop(){
  int sensorVal = analogRead(sensorPin);

  Serial.print("Sensor value: ");
  Serial.print(sensorVal);

  float volt = (sensorVal/1024.0) * 5.0;
  Serial.print("Voltage value ");
  Serial.print(volt);

  Serial.print("Degrees C: ");
  float temp = (volt - .5) * 100;
  Serial.println(temp);

  if(temp<baselineTemp +2){
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  } else if(temp>= baselineTemp+2 && temp<baselineTemp + 4){
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }else if(temp>= baselineTemp+4 && temp<baselineTemp + 6){
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  }else if(temp>= baselineTemp+6){
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
  }
  delay(100);
}
