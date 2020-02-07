// include the library code:
#include <LiquidCrystal.h>
#define SERVO1  2
#define SERVO2  3
#define SERVO3  4
#define SERVO4  5
#define SERVO5  11
#define SERVO6  13
/*==============================================================================
 * GLOBAL VARIABLES
 *============================================================================*/
unsigned long currentMicros;        // store the current value from millis()
unsigned long previousMicros; 
unsigned int samplingInterval = 10;
unsigned int cicle_count = 0;
/* Servo flags */
bool flag1 = false;
bool flag2 = false;
bool flag3 = false;
bool flag4 = false;
bool flag5 = false;
bool flag6 = false;
bool flagInit = false;
/* Servo Initial Angle  */
unsigned int angle1 = 0;
unsigned int angle2 = 36;
unsigned int angle3 = 72;
unsigned int angle4 = 108;
unsigned int angle5 = 144;
unsigned int angle6 = 180;
unsigned int current_angle = 0;
unsigned int valueang1 = 0;
unsigned int valueang2 = 0;
unsigned int valueang3 = 0;
unsigned int valueang4 = 0;
unsigned int valueang5 = 0;
unsigned int valueang6 = 0;

const int rs = 10, en = 12, d4 = 6, d5 = 7, d6 = 8, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  randomSeed(analogRead(0));
  pinMode(SERVO1, OUTPUT);
  pinMode(SERVO2, OUTPUT);
  pinMode(SERVO3, OUTPUT);
  pinMode(SERVO4, OUTPUT);
  pinMode(SERVO5, OUTPUT);
  pinMode(SERVO6, OUTPUT);
  digitalWrite(SERVO1, LOW);
  digitalWrite(SERVO2, LOW);
  digitalWrite(SERVO3, LOW);
  digitalWrite(SERVO4, LOW);
  digitalWrite(SERVO5, LOW);
  digitalWrite(SERVO6, LOW);
  previousMicros =  micros();
  // real angle values
  valueang1 = 500+10*angle1;
  valueang2 = 500+10*angle2;
  valueang3 = 500+10*angle3;
  valueang4 = 500+10*angle4;
  valueang5 = 500+10*angle5;
  valueang6 = 500+10*angle6; 
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.print("6 SERVO CONTROL");
}

void setServoAngle(byte servo,unsigned int angle) {
  unsigned int ang = 500+10*angle;
  switch(servo){
    case 1: valueang1 = ang; angle1=angle; break;
    case 2: valueang2 = ang; angle2=angle; break;
    case 3: valueang3 = ang; angle3=angle; break;
    case 4: valueang4 = ang; angle4=angle; break;
    case 5: valueang5 = ang; angle5=angle; break;
    case 6: valueang6 = ang; angle6=angle; break;
  }
}
String data;
void loop() {
  
  currentMicros = micros();
  if (currentMicros - previousMicros > samplingInterval) {
    previousMicros += samplingInterval;
    if(current_angle==0){ flagInit = true; }        // restart PWM cicle
    current_angle = current_angle + 10;             // one loop every 10 micro seconds
    if(current_angle==valueang1){flag1 = true; } 
    if(current_angle==valueang2){flag2 = true; }
    if(current_angle==valueang3){flag3 = true; }
    if(current_angle==valueang4){flag4 = true; }
    if(current_angle==valueang5){flag5 = true; }
    if(current_angle==valueang6){flag6 = true; }
    if(current_angle == 18450){                    // Aprox (20000us) 20ms 50Hz PWM Frecuency
      current_angle = 0; 
      cicle_count++;
      if(cicle_count==50){                         // Aprox every 1 sec
        setServoAngle(1,random(20,160));           // changing Servo Angle randomly
        setServoAngle(2,random(20,160));
        setServoAngle(3,random(20,160));
        setServoAngle(4,random(20,160));
        setServoAngle(5,random(20,160));
        setServoAngle(6,random(20,160));
        cicle_count = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        data = "A="+String(angle1)+" B="+String(angle2)+" C="+String(angle3);
        lcd.print(data);
        lcd.setCursor(0, 1);
        data = "D="+String(angle4)+" E="+String(angle5)+" F="+String(angle6);
        lcd.print(data);
      }
    } 
  }

  if(flagInit){
    digitalWrite(SERVO1, HIGH);
    digitalWrite(SERVO2, HIGH);
    digitalWrite(SERVO3, HIGH);
    digitalWrite(SERVO4, HIGH);
    digitalWrite(SERVO5, HIGH);
    digitalWrite(SERVO6, HIGH);
    flagInit = false;
  }
  if(flag1){
    digitalWrite(SERVO1, LOW);
    flag1 = false;
  }
  if(flag2){
    digitalWrite(SERVO2, LOW);
    flag2 = false;
  }
  if(flag3){
    digitalWrite(SERVO3, LOW);
    flag3 = false;
  }
  if(flag4){
    digitalWrite(SERVO4, LOW);
    flag4 = false;
  }
  if(flag5){
    digitalWrite(SERVO5, LOW);
    flag5 = false;
  }
  if(flag6){
    digitalWrite(SERVO6, LOW);
    flag6 = false;
  }
}
