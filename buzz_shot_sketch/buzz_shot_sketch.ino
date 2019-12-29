const int buzzPin = 2; // IN2 on buzzer
int val = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(buzzPin, OUTPUT);
  buzz_shot();
}

void loop() {
  // put your main code here, to run repeatedly:
  //buzz_shot();
}
void buzz_shot(){
  for (val = 150; val <=900; val+=30){
  tone(buzzPin, val); 
  delay(4);
  }
  for (val = 900; val >=0; val-=60){
  tone(buzzPin, val); 
  delay(20);
  }
  noTone(buzzPin);
  delay(2000);
}
