void setup() {
  // put your setup code here, to run once:
  pinMode(8, OUTPUT); // Wyjście na pinie #8
}

void loop() {
  // Zwraca sygnał SOS.
  for (int counter = 1; counter < 5; counter++) {
    if (counter < 2 or counter > 3) { // Taka pętla, żeby sprawdzić czy działa "or"
      digitalWrite(8, HIGH);
      delay(500);
      digitalWrite(8, LOW);
      delay(500);
    }
    else {
      digitalWrite(8, HIGH);
      delay(1000);
      digitalWrite(8, LOW);
      delay(1000);      
    }
  }
}
