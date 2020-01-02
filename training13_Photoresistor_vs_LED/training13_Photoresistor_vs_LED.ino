void setup() {
  // put your setup code here, to run once:
  pinMode(6, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  /// Analog read daje wartości od 0-1023
  int potValue = analogRead(A2);

  //Konwertuje wartości z jednej funkcji na drugą.
  int mappedValue = map(potValue, 0, 1023, 0, 255);

  int modValue = mappedValue - 10;
  if (modValue < 0) {
   modValue = 0;
   }
    
  //Analog Write przyjmuje wartości od 0-255
  analogWrite(6, modValue);
  Serial.print("After conversion: ");
  Serial.println(modValue);
  delay(100);
}
