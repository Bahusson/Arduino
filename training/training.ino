const int val5 = 6; //Stała globalna

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("Simple Calculation Using Functions");

int num1 = 4;
int num2;

num2 = 23;

Serial.println(do_a_calc(num1,num2));
}

void loop() {
  // put your main code here, to run repeatedly:
}

int do_a_calc(int val1,int val2) {
  int val3;
  val3 = val1 + val2 + val5;
  return val3;
}
