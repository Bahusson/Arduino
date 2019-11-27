int button_pressed = 1; // Symuluje wciśnięcie przycisku nr1

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  switch (button_pressed) {
    case 1:
      Serial.println("Wciśnięto Guzik nr 1");
      break;
    case 2:
      Serial.println("Wciśnięto Guzik nr 2");
      break;
    default:
      Serial.println("Nie widomo co zostało wciśnięte. :P");
      Serial.println("Jest to opcjonalna wartość domyślna!");
      break;
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
