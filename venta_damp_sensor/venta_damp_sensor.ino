// Szkic dodaje inteligencji staremu niemieckiemu nawilżaczowi powietrza "Venta"
// Napisany pod niepełnowartościwą (reklamacyjną) płytkę PRO Mini

#define G_LED  2  // LED zielony
#define Y_LED  3  // LED Żółty
#define R_LED  4  // LED Czerwony
#define Buzzer 5  // Głośnik
#define Waterlvl A0 // Czujnik poziomu wody

int waterval = 0;  // wartość poziomu wody
int waterbeep = 0; // dzięki temu na żółtym poziomie wody beeper daje znać tylko raz.
int minute = 60000; // minuta w milisekundach

void setup() {
  Serial.begin(9600);
  pinMode(G_LED, OUTPUT);
  pinMode(Y_LED, OUTPUT);
  pinMode(R_LED, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  ledblinks(G_LED, 300, 1);
  ledblinks(Y_LED, 300, 1);
  ledblinks(R_LED, 300, 1);
  buzz_buzz(3);
}

void loop() {
  waterval = analogRead(Waterlvl);
  if (waterval<=100){ 
    Serial.println("Water Level: Empty");
    digitalWrite(R_LED, HIGH);
    digitalWrite(Y_LED, LOW);
    digitalWrite(G_LED, LOW);
    buzz_buzz(2);
    delay(minute/2);
    } 
  else if (waterval>100 && waterval<=950){ 
    Serial.println("Water Level: Medium"); 
    digitalWrite(Y_LED, HIGH);
    digitalWrite(R_LED, LOW);
    digitalWrite(G_LED, LOW);
    if (waterbeep == 1){
      buzz_buzz(1);
      delay(minute);
     }
    } 
  else if (waterval>950){ 
    Serial.println("Water Level: High");
    digitalWrite(G_LED, HIGH);
    digitalWrite(R_LED, LOW);
    digitalWrite(Y_LED, LOW);
    waterbeep = 1;
    }
  delay(1000); 
}

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
