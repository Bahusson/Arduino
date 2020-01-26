// Szkic dodaje inteligencji staremu niemieckiemu nawilżaczowi powietrza "Venta"
// Napisany pod niepełnowartościwą (reklamacyjną) płytkę PRO Mini

#include <Servo.h> //ściągnij bibliotekę obsługującą serwo

#define G_LED  2  // LED zielony
#define Y_LED  3  // LED Żółty
#define R_LED  4  // LED Czerwony
#define Buzzer 5  // Głośnik
#define servoPin 6 // Serwo
#define Waterlvl A1 // Czujnik poziomu wody

int waterval = 0;  // wartość poziomu wody
int waterbeep = 0; // dzięki temu na żółtym poziomie wody beeper daje znać tylko raz.
unsigned int minute = 60000; // minuta w milisekundach
Servo breaker; // Stwórz obiekt serwo - przerywacz.
byte state = 1;
byte timeoff = 1;

void setup() {
  Serial.begin(9600);
  pinMode(G_LED, OUTPUT);
  pinMode(Y_LED, OUTPUT);
  pinMode(R_LED, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  ledblinks(G_LED, 300, 1);
  ledblinks(Y_LED, 300, 1);
  ledblinks(R_LED, 300, 1);
  breaker_off();
  buzz_buzz(3);
  //waterval = 1000; // Do kalibrowania serwa po wymianie przełącznika.
}

void loop() {
  waterval = analogRead(Waterlvl);
  Serial.println(waterval);
  if (waterval<=250){ 
    Serial.println("Water Level: Empty");
    digitalWrite(R_LED, HIGH);
    digitalWrite(Y_LED, LOW);
    digitalWrite(G_LED, LOW);
    buzz_buzz(2);
    breaker_off();
    state = 1;
    delay(minute/2);
    timeoff -= 1;
    if (timeoff < 2){
      timeoff = 2;
      standby();
     }
    }  
  else if (waterval>250 && waterval<=500){ 
    Serial.println("Water Level: Medium"); 
    digitalWrite(Y_LED, HIGH);
    digitalWrite(R_LED, LOW);
    digitalWrite(G_LED, LOW);
    state = 1;
    if (waterbeep == 1){
      buzz_buzz(1);
      delay(minute);
      waterbeep = 0;
     }
    }   
  else if (waterval>500){ 
    Serial.println("Water Level: High");
    timeoff = 120;
    digitalWrite(G_LED, HIGH);
    digitalWrite(R_LED, LOW);
    digitalWrite(Y_LED, LOW);
    waterbeep = 1;
    if(state == 1){
      breaker_on();
      state = 0;
     }
    }
  delay(1000);
}

//FUNKCJE
// Błyskacz ledów
void ledblinks(int pin, int interval, int rep) { // Błyska Ledem "x" w interwale "y" razy "z".
    while (rep > 0) {
         digitalWrite(pin, HIGH);
         delay(interval);
         digitalWrite(pin, LOW);
         delay(interval);
         rep -=1;
    }
}

// Głośnik bzyczy "rep" razy.
void buzz_buzz(byte rep){
  int n_buzz_val = 350;
  int b_del = 100;
  while (rep > 0){
  tone(Buzzer, n_buzz_val);
  delay(b_del);
  noTone(Buzzer);
  delay(b_del);
  rep -=1;
  }
}


//Głowica w pozycji "Włączonej"
void breaker_on() {
  breaker.attach(servoPin);
  breaker.write(46);
  delay(1000);
  breaker.detach();
}

//Głowica w pozycji "Wyłączonej"
void breaker_off(){
  breaker.attach(servoPin);
  breaker.write(68);
  delay(1000);
  breaker.detach();
}

//Tryb niskiego poboru energii po dwóch godzinach od zostawienia, jakby się wyłączył.
//Przypomina o sobie na chwilę tylko raz na dwie godziny.
void standby(){
  digitalWrite(R_LED, LOW);
  delay(minute*120);
}
