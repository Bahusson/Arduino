const int button = 2;
const int buzzer = 8;
int buttonState = 0;

void setup() {
  pinMode(button,INPUT);
  pinMode(buzzer, OUTPUT); // Ustaw głośnik jako wyjście.
  Serial.begin(9600);
}

void loop() {
   buttonState = digitalRead(button);
   Serial.println(buttonState);
   if (buttonState == HIGH) {
    tone(buzzer, 100); // Wydaje dźwięk o czestotliwości 1KHz
    delay(1000);
    noTone(buzzer); // Wyłącz to wycie...
    delay(1000);
  }
}
