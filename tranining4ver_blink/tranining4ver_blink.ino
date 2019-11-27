void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
   for (int countr = 0; countr < 30; countr++) {
      Serial.print(countr);
      Serial.print(",");
      Serial.println("Iitializing counter!");
      digitalWrite(LED_BUILTIN, HIGH);
      delay(50);
      digitalWrite(LED_BUILTIN, LOW); 
      delay(50);
   }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int counter = 0; counter < 20; counter++) {
    if (counter < 10) {
      Serial.print(counter);
      Serial.print(",");
      Serial.println("Counter is smaller than 10");
      digitalWrite(LED_BUILTIN, HIGH);
      delay(counter * 100);
      digitalWrite(LED_BUILTIN, LOW); 
      delay(counter * 150);
    } 
    else {
      Serial.print(counter);
      Serial.print(", ");
      Serial.println("Counter is not smaller than 10");
      digitalWrite(LED_BUILTIN, HIGH);
      delay(counter * 150);
      digitalWrite(LED_BUILTIN, LOW); 
      delay(counter * 100);
    }
  }
  //delay(500); Odkomentuj i wywal z if/else jeśli chcesz cały cykl co pół sekundy.
}
