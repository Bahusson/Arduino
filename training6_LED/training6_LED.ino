void setup() {
  // put your setup code here, to run once:
  pinMode(8, OUTPUT); // Wyjście na pinie #8
}

void loop() {
  // Zwraca sygnał SOS.
  for (int counter = 1; counter < 5; counter++) {
    if (counter < 2 or counter > 3) { // Taka pętla, żeby sprawdzić czy działa "or"
      blink_led(8, 500);
    }
    else {
      blink_led(8, 1000);    
    }
  }
}

void blink_led(int pin, int del) {
      digitalWrite(pin, HIGH);
      delay(del);
      digitalWrite(pin, LOW);
      delay(del);
}
