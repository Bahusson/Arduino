//IMPORTY
#include <Servo.h> //ściągnij bibliotekę obsługującą serwo
#include <AccelStepper.h> //ściągnij bibliotekę obsługującą silnik krokowy 

//DEFINICJE pinów
//LEDy
#define LEDpin1  3  // IN3 on PWM LED1
#define LEDpin2  5  // IN5 on PWM LED2
#define LEDpin3  11  // IN6 on PWM LED3
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

int power_lvl = 0;

void setup() {
  Serial.begin(9600);
  barrel.attach(6); // Przyporządkuj obiekt serwa "barrel" do pinu RWM 6.
  barrel_load_pos(); // Głowica na pozycję 0 po starcie programu.
  rotator.setMaxSpeed(200); // Parametry rotatora ustawione eksperymentalnie.
  rotator.setSpeed(200);
  rotator.setAcceleration(100.0);

}

void loop() {
  // put your main code here, to run repeatedly:
  LED_loader();
  power_lvl++; //Dodaj 1 do poziomu naładowania - musi być na końcu.
  delay(100);
  if (power_lvl == 100){
    power_lvl = 0;
  }
}

//FUNKCJE
//Głowica w pozycji do ładowania
void barrel_load_pos() {
  barrel.write(0);
}
//Głowica w pozycji do ładowania
void barrel_shot_pos() {
  barrel.write(85);
}
// Zestaw LED-ów 'ładuje' się
void LED_loader() {
  LEDcurb(33, 0, power_lvl, LEDpin1); // Dodawaj najpierw do 9
  LEDcurb(66, 33, power_lvl, LEDpin2); // Potem dodawaj do 10
  LEDcurb(99, 66, power_lvl, LEDpin3); // Na końcu dodawaj do 11
  
}
// Funkcja zwracająca mapująca dla LED-ów
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
