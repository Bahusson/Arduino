// const int red_pin = 3; <- Można definiować stałe w ten sposób.
// Albo w ten poniżej:

#define RED_PIN   3
#define GREEN_PIN 5
#define BLUE_PIN  6

void setup() {
  // put your setup code here, to run once:
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  blinker(GREEN_PIN, RED_PIN);
  blinker(RED_PIN, BLUE_PIN);
  blinker(BLUE_PIN, GREEN_PIN);
}

void blinker(char pin1, char pin2){
  digitalWrite(pin1, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(pin2, HIGH);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
