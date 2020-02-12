#include <Servo.h>
#include <math.h>
#include <LiquidCrystal.h>
Servo myservo1;  

const int rs = 10, en = 12, d4 = 6, d5 = 7, d6 = 8, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  myservo1.attach(2);  
  lcd.begin(16,2);
  lcd.print("Servo using LIB");
}
void loop() {
  myservo1.write(90); 
  delay(1000);
  myservo1.write(180);  
  delay(1000);                        
  myservo1.write(0);
  delay(1000); 

}
