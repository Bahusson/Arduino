int buttonState = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(2,INPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(2);

  if (buttonState == HIGH)
  {
    Serial.println("High");
    digitalWrite(8, HIGH);
  }
  else
  {
    Serial.println("Low");
    digitalWrite(8, LOW);
  }
}
