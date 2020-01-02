//IMPORTY
#include <Servo.h> //ściągnij bibliotekę obsługującą serwo
#include <AccelStepper.h> //ściągnij bibliotekę obsługującą silnik krokowy 
// Opcjonalne dla sensora wilgotności i temperatury (DHT)
#include <Adafruit_Sensor.h> //ściągnij ogólną bibliotekę sensorów
#include <DHT.h> //Poniższe dwa to biblioteki sensorów wilgotności/temperatury.
#include <DHT_U.h>

//DEFINICJE pinów
//LEDy "głowicy"
#define LEDpin1  3
#define LEDpin2  5
#define LEDpin3  11
//LEDy "indykatory"
#define lightPin A5
#define weatherPin A4
#define boosterPin A3
//StepperMotor
#define motorPin1  7     // IN1 on the ULN2003 driver 1
#define motorPin2  8     // IN2 on the ULN2003 driver 1
#define motorPin3  12     // IN3 on the ULN2003 driver 1
#define motorPin4  13     // IN4 on the ULN2003 driver 1
//UltrasonicDistanceSensor
#define trigPin 10
#define echoPin 9
//Czujnik DHT
#define DHTPIN A1
#define DHTTYPE DHT11

//ZMIENNE GLOBALNE
//Servo
Servo barrel; // Stwórz obiekt serwo, który będziesz kontrolował.
//StepperMotor
AccelStepper rotator(AccelStepper::FULL4WIRE, motorPin1, motorPin3, motorPin2, motorPin4);
//Buzzer
const int buzzPin = 2;   // Buzzer pin.
//Przycisk
const int buttonPin = 4; // Button pin.
//Czujnik DHT
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

int buttonState = 0;
int power_lvl = 0;
int val = 0;
int saveddistance = 0;
int dedication = 0;

void setup() {
  Serial.begin(9600);
  barrel.attach(6); // Przyporządkuj obiekt serwa "barrel" do pinu RWM 6.
  barrel_load_pos(); // Głowica na pozycję 0 po starcie programu.
  rotator.setMaxSpeed(200); // Parametry rotatora ustawione eksperymentalnie.
  rotator.setSpeed(200);
  rotator.setAcceleration(100.0);
  pinMode(trigPin, OUTPUT); // Piny trigger i echo dla czujnika ruchu.
  pinMode(echoPin, INPUT);
  pinMode(buzzPin, OUTPUT); // Pin głośnika/buzzera.
  pinMode(buttonPin, INPUT); // Pin przycisku "na żądanie".
  randomSeed(analogRead(0)); // Ziarno dla generatora liczb losowych z pina analogowego - input 0.
  dht.begin(); // Zainicjalizuj DHT.
  pinMode(lightPin, OUTPUT);
  pinMode(weatherPin, OUTPUT);
  pinMode(boosterPin, OUTPUT);
  //digitalWrite(lightPin, HIGH);
  //digitalWrite(weatherPin, HIGH);
}

void loop() {
  // Kalkuluje "determinację" działka przy szukaniu celu.
  LED_loader();
  int photvalue = analogRead(A2);
  byte flipval = random (60, 80)
  byte power_flip = random(100);
  if (power_flip < flipval){
    power_lvl++; //Dodaj 1 do poziomu naładowania z 75% prawdopodobieństwem.
  }
  Serial.println(power_lvl);
  //Serial.println(photvalue);
  if(power_lvl < 99){ 
    delay(100); // Domyślne opóźnienie ładowania w ms - do dostosowania w produkcji.
    light_switch(500, photvalue);
    if (dedication == 0) { // Opóźnienie na 1% ładowania
      delay(500);
    }
    // Tutaj wstaw warunki dla opóźniacza temperatury i wilgotności.
    
  }
  if (power_lvl == 100){
    rotator.enableOutputs(); // Podłącz prąd do silnika krokowego, żeby mógł się ruszyć..
  }
  if (power_lvl > 2500){
    rotator.disableOutputs(); // Odetnij prąd od silnika krokowego, żeby się nie grzał.
    //Sprawdź, czy nic się nie rusza przez 1-5 minut.
    byte stubborn = random(2,6);
    long determination = stubborn * 12; // ; W produkcji daj 120 (minuty)!
    while (determination > 0 && power_lvl > 100) {
    determination-=1;
    ultrasonic();
    }
    if (determination == 0){
      Shot(); // Jeśli nic się nie pojawi, wal na oślep!
    }
  }
  human_booster();
  dem_shot();
  rotator_search();
  //Serial.println(dedication);
}

//void(* resetFunc) (void) = 0; // Funkcja resetuje pamięć Arduino po strzale, bo inaczej głupieje.

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
  dedication = 0;
  //resetFunc();
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

// Strzał na żądanie z ryzykiem - drugie naciśnięcie guzika.
void dem_shot(){
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH && power_lvl >= 70) {
    rotator.disableOutputs();
    Shot();
  }
  if (dedication > 2){
   if (buttonState == HIGH && power_lvl < 70){
    rotator.disableOutputs();
    buzz_nought();
    power_lvl = power_lvl - 16;
    dedication = 0;
    if (power_lvl < 0) {
     power_lvl = 0;
    }  
   }  
  }
  if (buttonState == HIGH && dedication > 0){
    dedication += 1;
  }
}

// Booster mocy - pierwsze nacisnięcie guzika.
void human_booster(){
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH && dedication == 0) {
     dedication += 1;
    }
  if (dedication == 0){
     digitalWrite(boosterPin, LOW);
    }
  if (dedication > 0){
     digitalWrite(boosterPin, HIGH);
    }
}

//Silnik krokowy szuka i zatrzymuje się.
void rotator_search() {
   int myposition = superposition();
   if (power_lvl > 99 && power_lvl < 100 + myposition){
  rotator.move(myposition);
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

// Czujnik ultradźwiękowy.
void ultrasonic() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Tyle czasu wracał ping.
  distance = (duration / 2) / 29.1; // Konwertujemy powyższą wartość na centymetry z prędkości dźwięku.
  int res = 2; // Ustaw czułość

  if (saveddistance > 0 && saveddistance < 400) {
    if (saveddistance - distance >= res or saveddistance - distance <= -res){
      Shot();
    }
  }
  if (distance >= 400 || distance <= 0){
   Serial.println("Out of range");
   }
  else {
   Serial.print(distance);
   Serial.println(" cm");
   }
  delay(500);
  saveddistance = distance;
}

void light_switch(int delay_time, int photval) {
    if (photval > 400){
      digitalWrite(lightPin, LOW);
      delay(delay_time);
    }
    else {
      digitalWrite(lightPin, HIGH);
    }
}
