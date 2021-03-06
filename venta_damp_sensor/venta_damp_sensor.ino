// Szkic dodaje inteligencji staremu niemieckiemu nawilżaczowi powietrza "Venta"
/* Napisany pod niepełnowartościwą (reklamacyjną) płytkę PRO Mini
 * Problem z tym szkicem jest taki, że trzeba zastosować wartości absolutne przewodnictwa wody,
 * zaś te za każdym razem są inne - zarówno na starcie (woda z kranu jest uzdatniana i nie zawsze ma idealne parametry,
 * nie zawsze da się doczyścić sam nawilżacz, element mieszający pozbywa się z czasem kamienia itp., być może też sam
 * czujnik zużywa się bardziej niż powinien, pomimo oprogramowania go na włączanie się raz na 15min).
 * Alternatywą byłoby użycie sondy, ale tutaj jest problem z obracającym się elementem w środku urządzenia.
 * Ostatecznie można dodać kontrolerowi jakąś kartę pamięci, żeby pamiętał z jakiej wartości startuje aż do 
 * następnego ładowania i kombinować z wartościami relatywnymi, ale imho to trochę overkill.
 * Można też olać pośrednią lampkę i zrobić tak, żeby się wyłączał przy uniwersalnej niskiej wartości, żeby
 * tylko nie chodził na jałowym biegu, ale to trochę ryzyko, że będzie jakiś czas wzbijal kurz z tego co właśnie oczyścił,
 * oraz, że właśnie będzie się tworzył dodatkowy osad.
 */ 

#include <Servo.h> //ściągnij bibliotekę obsługującą serwo

#define G_LED  2  // LED zielony
#define Y_LED  3  // LED Żółty
#define R_LED  4  // LED Czerwony
#define Buzzer 5  // Głośnik
#define servoPin 6 // Serwo
#define Waterlvl A1 // Czujnik poziomu wody
#define water_switch 7 // Wyłącznik czujnika wody

int waterval = 0;  // wartość poziomu wody
int waterbeep = 0; // dzięki temu na żółtym poziomie wody beeper daje znać tylko raz.
long minute = 60000; // minuta w milisekundach
Servo breaker; // Stwórz obiekt serwo - przerywacz.
byte state = 1;
byte lock = 0;

void setup() {
  Serial.begin(9600);
  pinMode(G_LED, OUTPUT);
  pinMode(Y_LED, OUTPUT);
  pinMode(R_LED, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(water_switch, OUTPUT);
  ledblinks(G_LED, 300, 1);
  ledblinks(Y_LED, 300, 1);
  ledblinks(R_LED, 300, 1);
  breaker_off();
  //breaker_on(); // Do usunięcia po testach przewodnictwa!!
  buzz_buzz(3);
  digitalWrite(water_switch, HIGH);
}

void loop() {
  digitalWrite(water_switch, HIGH);
  waterval = analogRead(Waterlvl);
  Serial.println(waterval);
  if (waterval < 610) {
    lock = 1;
    Serial.println("Water Level: Empty");
    digitalWrite(R_LED, HIGH);
    digitalWrite(Y_LED, LOW);
    digitalWrite(G_LED, LOW);
    buzz_buzz(2);
    breaker_off();
    state = 1;
    w_sensor_off_();
  }
  else if (waterval >= 666) {
    Serial.println("Water Level: Medium");
    digitalWrite(Y_LED, HIGH);
    digitalWrite(R_LED, LOW);
    digitalWrite(G_LED, LOW);
    lock = 1;
    state = 1;
    if (waterbeep == 1) {
      buzz_buzz(1);
      waterbeep = 0;
    }
    w_sensor_off_();
  }
  else if (waterval >= 635 && waterval < 666 && lock == 0) {
    Serial.println("Water Level: High");
    digitalWrite(G_LED, HIGH);
    digitalWrite(R_LED, LOW);
    digitalWrite(Y_LED, LOW);
    waterbeep = 1;
    if (state == 1) {
      breaker_on();
      state = 0;
    }
    w_sensor_off_();
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
    rep -= 1;
  }
}

// Głośnik bzyczy "rep" razy.
void buzz_buzz(byte rep) {
  int n_buzz_val = 350;
  int b_del = 100;
  while (rep > 0) {
    tone(Buzzer, n_buzz_val);
    delay(b_del);
    noTone(Buzzer);
    delay(b_del);
    rep -= 1;
  }
}


//Głowica w pozycji "Włączonej"
void breaker_on() {
  breaker.attach(servoPin);
  breaker.write(48);
  delay(500);
  breaker.detach();
}

//Głowica w pozycji "Wyłączonej"
void breaker_off() {
  breaker.attach(servoPin);
  breaker.write(68);
  delay(500);
  breaker.detach();
}

//Tryb oszczędzania elektrody w czujniku poziomu wody
void w_sensor_off_() {
  digitalWrite(water_switch, LOW);
  delay(minute * 15); // Wyłącz czujnik na kwadrans
}
