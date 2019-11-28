void setup() {
  // put your setup code here, to run once:
  pinMode(6, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  /// Analog read daje wartości od 0-1023
  int potValue = analogRead(A0);
  Serial.print("Before conversion: ");
  Serial.println(potValue);
  delay(10);

  //Konwertuje wartości z jednej funkcji na drugą.
  int mapppedValue = map(potValue, 0, 1023, 0, 255);
    
  //Analog Write przyjmuje wartości od 0-255
  analogWrite(6, mapppedValue);
  Serial.print("After conversion: ");
  Serial.println(mapppedValue);
  delay(10);
}
