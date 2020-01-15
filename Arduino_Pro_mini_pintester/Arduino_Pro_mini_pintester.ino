int val = 0;

void setup() {
  pinMode(2, OUTPUT); // 0-1
  pinMode(3, OUTPUT); // PWM
  pinMode(4, OUTPUT); // 0-1
  pinMode(5, OUTPUT); // PWM
  pinMode(6, OUTPUT); // PWM
  pinMode(7, OUTPUT); // 0-1
  pinMode(8, OUTPUT); // 0-1
  pinMode(9, OUTPUT); // PWM
  pinMode(10, OUTPUT); // PWM
  pinMode(11, OUTPUT); // PWM
  pinMode(12, OUTPUT); // 0-1
  pinMode(13, OUTPUT); // 0-1
  pinMode(A0, OUTPUT); // 0-1
  pinMode(A1, OUTPUT); // 0-1
  pinMode(A2, OUTPUT); // 0-1
  pinMode(A3, OUTPUT); // 0-1
  pinMode(A4, OUTPUT); // 0-1
  pinMode(A5, OUTPUT); // 0-1
  pinMode(A6, OUTPUT); // Tylko analog input.
  pinMode(A7, OUTPUT); // Tylko analog input.
}

void loop() {
  // put your main code here, to run repeatedly:
  LED_shot();
}

void LED_shot() {

  //Szybko zapala się na 100%
  for (val = 0; val <=255; val +=5){
  analogWrite(2, val);
  analogWrite(3, val);
  analogWrite(4, val);
  analogWrite(5, val);
  analogWrite(6, val);
  analogWrite(7, val);
  analogWrite(8, val);
  analogWrite(9, val);
  analogWrite(10, val);
  analogWrite(11, val);
  analogWrite(12, val);
  analogWrite(13, val);
  analogWrite(A0, val);
  analogWrite(A1, val);
  analogWrite(A2, val);
  analogWrite(A3, val);
  analogWrite(A4, val);
  analogWrite(A5, val);
  analogWrite(A6, val);
  analogWrite(A7, val);
  delay(1);
  }
  //powoli gaśnie do 0%
  for (val = 255; val >=0; val-=1){
  analogWrite(2, val);
  analogWrite(3, val);
  analogWrite(4, val);
  analogWrite(5, val);
  analogWrite(6, val);
  analogWrite(7, val);
  analogWrite(8, val);
  analogWrite(9, val);
  analogWrite(10, val);
  analogWrite(11, val);
  analogWrite(12, val);
  analogWrite(13, val);
  analogWrite(A0, val);
  analogWrite(A1, val);
  analogWrite(A2, val);
  analogWrite(A3, val);
  analogWrite(A4, val);
  analogWrite(A5, val);
  analogWrite(A6, val);
  analogWrite(A7, val);
  delay(5);
  }
}
