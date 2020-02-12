#include <Servo.h>
#include <math.h>
#include <LiquidCrystal.h>
Servo myservo1;  
Servo myservo2;
Servo myservo3;

const int rs = 10, en = 12, d4 = 6, d5 = 7, d6 = 8, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
double delta = 0.049087385;
double r = 5;
double P = 11.5;
double Q = 14.5;
int y = 8;
double alfa = 0;
void setup() {
  randomSeed(analogRead(0));
  myservo1.attach(2);  
  myservo2.attach(3); 
  myservo3.attach(4); 
  lcd.begin(16,2);
  lcd.print("Servo using LIB");
}
unsigned int angle = 0;
unsigned int count =0;
String data;
void loop() {
  double K = r*cos(alfa);
  double L = sqrt(square(y+r-K)+square(r*sin(alfa)));
  double teta = asin(r*sin(alfa)/L);
  int TETA = teta*180/M_PI*1.2;
  lcd.clear();
  //-----------------
  double H = sqrt( square(L)+36);
  double a1 = acos((square(P)+square(H)-square(Q))/(2*P*H));
  double a3 = acos(L/H);
  a1 = a1 - a3;
  int A1 = a1*180/M_PI;
  data = "T="+String(TETA)+"  A1="+String(A1);
  lcd.print(data);
  lcd.setCursor(0, 1);
  double a2 = acos((square(P)+square(Q)-square(H))/(2*P*Q));
  int A2 = a2*180/M_PI;
  data = "A2="+String(A2);
  lcd.print(data);
  
  myservo1.write(TETA+35); 
  myservo2.write(A1);
  myservo3.write(A2);
  delay(15);                           
  alfa = alfa + delta;
  if(alfa>2*M_PI){ alfa = 0;}

}
