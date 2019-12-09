#include <Servo.h> //ściągnij bibliotekę obsługującą serwo

int pos = 0;

Servo myservo1, myservo2; // Stwórz obiekt serwo, który będziesz kontrolował.

void setup() {
  myservo1.attach(9); //Przyporządkuj obiekt servo1 do pinu 9
//  myservo2.attach(10); 
}

void loop() {
  //Poniższy kod przesuwa 180-stopniowe serwo z poziomu 0 na 180.
  //Jeśli się zacina po osiągnięciu końca to zmień parametry o ok. 10 stopni z z do 10 i z 180 na 170.
  for (pos = 0; pos <= 180; pos +=1) { //przejedź z 0 do 180 stopni.
      myservo1.write(pos);           //serwo 1 otrzymuje rozkaz przejścia na pozycję "pos"
     // myserwo2.write(pos);           //analogicznie tylko serwo 2.
      delay(5);                      //poczekaj 5ms aż serwo osiągnie swoją pozycję.
  }
  for (pos = 180; pos >=0; pos -=1) { //przejedź z 180 do 0 stopni.
      myservo1.write(pos);           //serwo 1 otrzymuje rozkaz przejścia na pozycję "pos"
     // myserwo2.write(pos);           //analogicznie tylko serwo 2.
      delay(5);                      //poczekaj 5ms aż serwo osiągnie swoją pozycję.
  }
// Tutaj masz możliwość przetestowania jak twoje serwo znajduje się na określonej pozycji.
myservo1.write(85); //Serwo1 idzie na pozycję 85
delay(500);
myservo1.write(20); //Serwo1 idzie na pozycję 20
delay(500);
myservo1.write(170); //Serwo1 idzie na pozycję 170
delay(500);
  
}  
