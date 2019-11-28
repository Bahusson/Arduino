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
  rgb_led(255, 0, 50);
}

void rgb_led(int red, int green, int blue){
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}
