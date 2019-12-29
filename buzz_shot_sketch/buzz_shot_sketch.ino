const int buzzPin = 2; // IN2 on buzzer

void setup() {
  // put your setup code here, to run once:
  pinMode(buzzPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int buzz_del = 20;
  tone(buzzPin, 350);
  delay(buzz_del);
  tone(buzzPin, 550);
  delay(buzz_del);
  tone(buzzPin, 800);
  delay(buzz_del);
  tone(buzzPin, 900);
  delay(buzz_del);
  noTone(buzzPin);
  delay(1000);
}
