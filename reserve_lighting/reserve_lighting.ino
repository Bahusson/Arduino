// Szkic reguluje oświetlenie awaryjne z UPS

// Zdefiniuj piny dla lampek i odpowiadających im
// guzików/przełączników.
#define workLight    2
#define workButton   3
#define corrLight    4
#define corrButton   5
#define bath1Light   6
#define bath1Button  7
#define gateLight    8
#define gateButton   9
#define bath2Light  10
#define bath2Button 11
#define kitchLight  12
#define kitchButton 13
#define smallLight  A0
#define smallButton A1
#define sleepLight  A2
#define sleepButton A3

// Zmienne trzymające stan poszczególnych przycisków.
int workState = 0;
int corrState = 0;
int bath1State = 0;
int gateState = 0;
int bath2State = 0;
int kitchState = 0;
int smallState = 0;
int sleepState = 0;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
