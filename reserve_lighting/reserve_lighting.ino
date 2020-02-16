// Szkic reguluje oświetlenie awaryjne z UPS
// Wykorzystuje wszystkie piny na Arduino PRO Mini

// Zdefiniuj piny dla lampek i odpowiadających im
// guzików/przełączników.
#define workLight     2
#define workButton    3
#define corrLight     4
#define corrButton    5
#define bath1Light    6
#define bath1Button   7
#define gateLight     8  //Oświetlenie w maszynowni włącza się z guzika oświetlającego również wiatrołap. (hardware)
#define gateButton    9
#define bath2Light   10
#define bath2Button  11
#define kitchLight   12
#define kitchButton  13
#define smallLight   A0
#define smallButton  A1
#define sleepLight   A2
#define sleepButton  A3
#define buttonsLight A4 //Światła guzików przy włącznikach włączają się tylko po zmroku. (A6)
// A5 pozostaje wolny.
#define lightSensor  A5 // A6 na Arduino PRO Mini
// Analog input A7 pozostaje wolny.
  
unsigned int lightbuffer = 0;
  
void setup() {
  // Przypisz piny związane z LEDami jako wyjścia.
  Serial.begin(9600);
  pinMode(workLight, OUTPUT);
  pinMode(corrLight, OUTPUT);
  pinMode(bath1Light, OUTPUT);
  pinMode(gateLight, OUTPUT);
  pinMode(bath2Light, OUTPUT);
  pinMode(kitchLight, OUTPUT);
  pinMode(smallLight, OUTPUT);
  pinMode(workLight, OUTPUT);
  pinMode(sleepLight, OUTPUT);
  pinMode(buttonsLight, OUTPUT);
  // Od razu po załączeniu oświetlenia awaryjnego
  // Załącz światło w kotłowni i na korytarzu.
  digitalWrite(gateLight, HIGH);
  digitalWrite(corrLight, HIGH);
}

void loop() {
  // Sprawia, że światło na guzikach nie miga jak ktoś zasłoni czujnik na chwilę. Tolerancja 10s.
  if (lightbuffer > 1000) {
    switch_visible();
    lightbuffer = 0;
  }
  Serial.println(lightbuffer);
  // Umożliwia włączanie i wyłączanie wszystkich LEDów guzikami.
  switch_light(workLight, workButton);
  switch_light(corrLight, corrButton);
  switch_light(bath1Light, bath1Button);
  switch_light(gateLight, gateButton);
  switch_light(bath2Light, bath2Button);
  switch_light(kitchLight, kitchButton);
  switch_light(smallLight, smallButton);
  switch_light(sleepLight, sleepButton);
  /* Pewnie da się to jakoś skrócić za pomocą 2 list
   *  i pętli FOR. Jak będzie czas, to spróbuję, ale najpierw
   *  hardware...*/
  lightbuffer += 1;
}

//Przełącznik LEDów (guziki)
void switch_light(int defLED, int switch_button) {
  int ledState = digitalRead(defLED);
  int buttonState = digitalRead(switch_button);
  
  if (buttonState == HIGH && ledState == LOW){
    digitalWrite(defLED, HIGH);
    delay(150);
  }
  else if (buttonState == HIGH && ledState == HIGH){
    digitalWrite(defLED, LOW);
    delay(200);
  }
}

//Przełącznik LEDów na guzikach (fotorezystor)
void switch_visible() {
  int daytime = analogRead(lightSensor);
  // Jak się robi ciemno, to zapala diody przy guzikach,
  // żeby były łatwo widoczne i na odwrót.
  if (daytime > 200) {
    digitalWrite(buttonsLight, HIGH);
    delay(5);
  }
  else {
    digitalWrite(buttonsLight, LOW);
    delay(5);
  }
}
