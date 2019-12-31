#define trigPin 10
#define echoPin 9

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  ultrasonic();
}

void ultrasonic() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Tyle czasu wracał ping.
  distance = (duration / 2) / 29.1; // Konwertujemy powyższą wartość na centymetry z prędkości dźwięku.

  if (distance >= 2000 || distance <= 0){
   Serial.println("Out of range");
   }
  else {
   Serial.print(distance);
   Serial.println(" cm");
   }
  delay(500);
}
