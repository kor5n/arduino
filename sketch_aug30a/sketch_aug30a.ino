const int switchPin = 8;
unsigned long previousTime = 0;
int switchState = 0;
int prevSwitchState = 0;
int led = 2;
long interval = 100 * 60;

void setup() {
  // put your setup code here, to run once:
  for(int i=2; i<8;i++){
    pinMode(i, OUTPUT);
  }

  pinMode(switchPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentTime = millis();
  if(currentTime - previousTime > interval){
    previousTime = currentTime;
    digitalWrite(led, HIGH);

    if(led <7){
      led++;
    }

    
  }
  switchState = digitalRead(switchPin);
  if(switchState != prevSwitchState){
    for(int i=2;i<8;i++){
      digitalWrite(i, LOW);
    }

    led =2;
    previousTime = currentTime;
  }
  prevSwitchState = switchState;
  Serial.println(currentTime);
  Serial.println(switchState);
  Serial.println(led);

}
