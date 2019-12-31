//IMPORTY
#include <Servo.h> //ściągnij bibliotekę obsługującą serwo
#include <AccelStepper.h> //ściągnij bibliotekę obsługującą silnik krokowy 

//DEFINICJE pinów
//LEDy
#define LEDpin1  3
#define LEDpin2  5
#define LEDpin3  11
//StepperMotor
#define motorPin1  7     // IN1 on the ULN2003 driver 1
#define motorPin2  8     // IN2 on the ULN2003 driver 1
#define motorPin3  12     // IN3 on the ULN2003 driver 1
#define motorPin4  13     // IN4 on the ULN2003 driver 1

//ZMIENNE GLOBALNE
//Servo
Servo barrel; // Stwórz obiekt serwo, który będziesz kontrolował.
//StepperMotor
AccelStepper rotator(AccelStepper::FULL4WIRE, motorPin1, motorPin3, motorPin2, motorPin4);
//Buzzer
const int buzzPin = 2;   // Buzzer pin.
//Przycisk
const int buttonPin = 4; // Button pin.

int buttonState = 0;
int power_lvl = 0;
int val = 0;

void setup() {
  Serial.begin(9600);
  barrel.attach(6); // Przyporządkuj obiekt serwa "barrel" do pinu RWM 6.
  barrel_load_pos(); // Głowica na pozycję 0 po starcie programu.
  rotator.setMaxSpeed(200); // Parametry rotatora ustawione eksperymentalnie.
  rotator.setSpeed(200);
  rotator.setAcceleration(100.0);
  pinMode(buzzPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  randomSeed(analogRead(0)); // Ziarno dla generatora liczb losowych z pina analogowego - input 0.
}

void loop() {
  // Kalkuluje "determinację" działka przy szukaniu celu.
  LED_loader();
  power_lvl++; //Dodaj 1 do poziomu naładowania - musi być na końcu?
  if(power_lvl < 99){ 
  delay(100); // Opóźnienie ładowania w ms - do dostosowania w produkcji.
  }
  Serial.println(power_lvl);
  if (power_lvl > 2500){
    //Sprawdź, czy nic się nie rusza.
    delay(1000);
    Shot();
  }
  dem_shot();
  rotator_search();
  //if (power_lvl == 100){ // Po pełnim naładowaniu działko "szuka" celu z coraz mniejszą zawziętością.
    
    //delay(10000);
    //byte stubborn = random(2,5);
    //Serial.println(stubborn);
    //while (stubborn > 0) {
    // long determination = stubborn * 1000; // 60000; W produkcji daj minutę!
    // stubborn-=1;
    // Serial.println(determination);
    // delay(determination);
    // rotator_search();
    //}
    //Shot();
  //}
}

//FUNKCJE
//Głowica w pozycji do ładowania
void barrel_load_pos() {
  barrel.write(0);
}

//Głowica w pozycji do strzału
void barrel_shot_pos() {
  barrel.write(85);
}

// Zestaw LED-ów 'ładuje' się
void LED_loader() {
  LEDcurb(33, 0, power_lvl, LEDpin1); // Dodawaj najpierw do 9
  LEDcurb(66, 33, power_lvl, LEDpin2); // Potem dodawaj do 10
  LEDcurb(99, 66, power_lvl, LEDpin3); // Na końcu dodawaj do 11
}

// Funkcja mapująca dla LED-ów
void LEDcurb(int curb,int mod, int p_lvl,int pin) { 
  if (p_lvl > curb){
    p_lvl = curb;
  }
  int pinpower = p_lvl-mod;
  int mapfrom = curb-mod;
  if (mapfrom < 0){
    mapfrom = 0;
  }
    if (pinpower < 0){
    pinpower = 0;
  }
  int mappedvalue = map(pinpower, 0, mapfrom, 0, 255);
  analogWrite(pin, mappedvalue);
}

// Zestaw LED-ów symuluje 'wystrzał'
void LED_shot() {
  //powoli gaśnie do 10%
  for (val = 255; val >=10; val-=1){
  analogWrite(LEDpin1, val);
  analogWrite(LEDpin2, val);
  analogWrite(LEDpin3, val);
  delay(5);
  }
  //Szybko zapala się na 100%
  for (val = 0; val <=255; val +=5){
  analogWrite(LEDpin1, val);
  analogWrite(LEDpin2, val);
  analogWrite(LEDpin3, val);
  delay(1);
  }
  buzz_shot();
  //powoli gaśnie do 0%
  for (val = 255; val >=0; val-=1){
  analogWrite(LEDpin1, val);
  analogWrite(LEDpin2, val);
  analogWrite(LEDpin3, val);
  delay(5);
  }
}

// Głośnik symuluje 'wystrzał'
void buzz_shot() {
  for (val = 150; val <=900; val+=30){
  tone(buzzPin, val); 
  delay(4);
  }
  for (val = 900; val >=0; val-=60){
  tone(buzzPin, val); 
  delay(20);
  }
  noTone(buzzPin);
}

// Pełna sekwencja wystrzału.
void Shot() {
  barrel_shot_pos();
  delay(1000);
  LED_shot(); //Zawiera buzz_shot();
  delay(1500);
  barrel_load_pos();
  power_lvl = 0;
}

// Odgłos sygnalizuje nienaładowanie zestawu.
void buzz_nought(){
  int n_buzz_val = 350;
  int b_del = 100;
  tone(buzzPin, n_buzz_val);
  delay(b_del);
  noTone(buzzPin);
  delay(b_del);
  tone(buzzPin, n_buzz_val);
  delay(b_del);
  noTone(buzzPin);
  delay(b_del);
}

// Strzał na żądanie z ryzykiem (guzik)
void dem_shot(){
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH && power_lvl >= 70) {
    Shot();
  }
  if (buttonState == HIGH && power_lvl < 70) {
    buzz_nought();
    power_lvl = power_lvl - 16;
   if (power_lvl < 0) {
     power_lvl = 0;
    }
 }
}

//Silnik krokowy szuka i zatrzymuje się.
void rotator_search() {
   int myposition = superposition();
   if (power_lvl > 99 && power_lvl < 100 + myposition){
//  if (rotator.distanceToGo() == 0) {  // Tylko po zakończeniu poprzedniego ruchu
//    rotator.moveTo(superposition());  // Rusz się.
//  }
//    rotator.run();
  rotator.moveTo(myposition);
  rotator.run();
 }
}

// Zwraca losową 'superpozycję' dla silnika krokowego. ;)
int superposition() {
  byte flip = random(2); // Wylosuj, czy ruszy się w prawo czy w lewo.
  int dist = random(250, 2500); //Wylosuj odległość na którą obróci się wieża.
  int superpos = 0;
  if (flip == 0){
    superpos = -dist;
  }
  else{
    superpos = dist;
  }
  return superpos;
}
