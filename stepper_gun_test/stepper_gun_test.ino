#include <AccelStepper.h>

// Motor pin definitions
#define motorPin1  7     // IN1 on the ULN2003 driver 1
#define motorPin2  8     // IN2 on the ULN2003 driver 1
#define motorPin3  12     // IN3 on the ULN2003 driver 1
#define motorPin4  13     // IN4 on the ULN2003 driver 1

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper rotator(AccelStepper::FULL4WIRE, motorPin1, motorPin3, motorPin2, motorPin4);

void setup()
{  
  Serial.begin(9600);
  rotator.setMaxSpeed(200); // Parametry rotatora ustawione eksperymentalnie.
  rotator.setSpeed(200);
  rotator.setAcceleration(100.0);
  rotator.setCurrentPosition(0);
  randomSeed(analogRead(0));
}

void loop()
{
  rotator_search();
}

//Silnik krokowy szuka i zatrzymuje się.
void rotator_search() {
  if (rotator.distanceToGo() == 0) {           // If position reached...
    rotator.moveTo(superposition());
  }
    rotator.run();                  // Call run() as often as possible
}

// Zwraca losową 'superpozycję' dla silnika krokowego. ;)
int superposition() {
  byte flip = random(2); // Wylosuj, czy ruszy się w prawo czy w lewo.
  int dist = random(250, 1500); //Wylosuj odległość na którą obróci się wieża.
  Serial.println(dist);
  int superpos = 0;
  if (flip == 0){
    superpos = -dist;
  }
  else{
    superpos = dist;
  }
  return superpos;
}
