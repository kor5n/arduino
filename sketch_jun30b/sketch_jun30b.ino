int notes[] = {262, 294, 330, 349};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int keyval = analogRead(A0);
  Serial.println(keyval);

  if(keyval==1023){
    tone(8, notes[0]);
  }else if(keyval >= 990 && keyval <= 1010){
    tone(8, notes[1]);
  }else if(keyval >= 505 && keyval <= 515){
    tone(8, notes[2]);
  }else if(keyval >= 4 && keyval <= 15){
    tone(8, notes[3]);
  }else{
    noTone(8);
  }
}
