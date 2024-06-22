//1 мотор:4 dir 5 step
//2 мотор:2 dir 3 step
#include <MsTimer2.h>
#include "Servo.h"   // подключаем библиотеку для работы с серво
#define _LCD_TYPE 1  // для работы с I2C дисплеями
//#include <LCD_1602_RUS_ALL.h>  // подключаем библиотеку с русскими буквами для дисплея
#include <SoftwareSerial.h>
SoftwareSerial espSerial(5, 6);
const int stepPin = 7;  //прописываем пины
const int dirPin = 6;
const int stepPin2 = 3;
const int dirPin2 = 2;
const int stepPin3 = 5;
const int dirPin3 = 4;
const int ks = 11;
const int kz = 10;
const int kb = 12;
const int sv1 = 8;
const int sv2 = 9;
int old_time = 0;
String content = "";
int m = 0;
char character;
int flag = 0;
//LCD_1602_RUS lcd(0x27, 16, 2);
Servo zahvat;
Servo povorot;
float norma = 2.00;
int angle;  // переменная для угла поворота микро серво
int incomingByte = 0;
int posz = 0;
int posp = 0;

void go_up(int steps) {         //фунция поднятия стрелы манипулятора
  digitalWrite(dirPin3, HIGH);  // Enables the motor to move in a particular direction
  for (int x = 0; x < steps; x++) {
    if (flag == 0) {
      digitalWrite(stepPin3, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin3, LOW);
      delayMicroseconds(500);
    } else {
      while (flag == 1) {
        Serial.println(flag);
      }
    }
  }
}
void go_down(int steps) {      // фунция опускания стрелы манипулятора
  digitalWrite(dirPin3, LOW);  //Changes the direction of rotation
  for (int x = 0; x < steps; x++) {
    if (flag == 0) {
      digitalWrite(stepPin3, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin3, LOW);
      delayMicroseconds(500);
    } else {
      while (flag == 1) {
        Serial.println(flag);
      }
    }
  }
}
void rotate_leftb(int steps) {  //функции поворота вправо / влево
  digitalWrite(dirPin2, LOW);   // Enables the motor to move in a particular direction
  for (int x = 0; x < steps; x++) {
    if (flag == 0) {
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(600);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(600);
    } else {
      while (flag == 1) {
        Serial.println(flag);
      }
    }
  }
}
void rotate_rightb(int steps) {
  digitalWrite(dirPin2, HIGH);  // Enables the motor to move in a particular direction
  for (int x = 0; x < steps; x++) {
    if (flag == 0) {
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(600);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(600);
    } else {
      while (flag == 1) {
        Serial.println(flag);
      }
    }
  }
}

void rotate_lefts(int steps) {
  digitalWrite(dirPin, LOW);  //Changes the direction of rotation
  for (int x = 0; x < steps; x++) {
    if (flag == 0) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(500);
    } else {
      while (flag == 1) {
        Serial.println(flag);
      }
    }
  }
}
void first() {
  povorot.write(85); 
  zahvat.attach(9);
  sbros();
  z_align();
  go_up(32000);
  go_up(10000);
  y_align();
  x_align();
  rotate_lefts(300);
  rotate_rightb(600);
  rotate_rights(100);
  // Serial.write("1");
  // while((content!= 7) and (content!= 8)){
  //   if(Serial.available()){
  //     character = Serial.read();
  //     content.concat(character);
  //     Serial.println(content);
  //     m = character - '0';
  //     if(m == 7){
  //       Serial.write("priem");

  go_down(32000);
  go_down(3000);
  zahvat.attach(9);
  catchservo();
  delay(1000);  // пин для подключения микро серво
  
  go_up(20000);
  rotate_rightb(200);
  rotate_rightb(150);
  rotate_lefts(50);
  delay(1000);
  go_down(18000);
  sliv();
  // }
  // else if(m == 8){
  //   Serial.write("priem");

  //   return 0;
  // }
  //   }
  // }}}
}
void second() {
  z_align();
  // go_up(32000);
  // go_up(10000);
  y_align();
  x_align();
  rotate_lefts(100);
  rotate_rightb(600);
  rotate_rightb(100);
  rotate_leftb(150);
  // go_down(30000);
  catchservo();
  // go_up(10000);
  rotate_rightb(200);
  rotate_rightb(150);
  rotate_lefts(200);
  // go_down(10000);
  sliv();
}
void rotate_rights(int steps) {
  digitalWrite(dirPin, HIGH);  // Enables the motor to move in a particular direction
  for (int x = 0; x < steps; x++) {
    if (flag == 0) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(600);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(600);
    } else {
      while (flag == 1) {
        Serial.println(flag);
      }
    }
  }
}
void z_align() {
  while (digitalRead(kz) == HIGH) {
    go_down(10);
  }
  return 0;
}
void x_align() {
  while (digitalRead(ks) == HIGH) {
    rotate_rights(10);
  }
  return 0;
}
void y_align() {
  while (digitalRead(kb) == HIGH) {
    rotate_leftb(10);
  }
  return 0;
}
void catchservo() {
  for (posz = 0; posz <= 180; posz += 1) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    zahvat.write(posz);  // tell servo to go to position in variable 'pos'
    delay(15);           // waits 15 ms for the servo to reach the position
  }
}
void sbros() {
  for (posz = 180; posz >= 0; posz -= 1) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    zahvat.write(posz);  // tell servo to go to position in variable 'pos'
    delay(15);           // waits 15 ms for the servo to reach the position
  }
}
void sliv() {
  for (posp = 45; posp <= 180; posp += 1) {  // goes from 0,kk,kkkkkkkkkkkklmnbvc

    // degrees to 180 degrees
    // in steps of 1 degree
    povorot.write(posp);  // tell servo to go to position in variable 'pos'
    delay(20);            // waits 15 ms for the servo to reach the position
  }
}
// byte customChar[] = {
//   0x0E,
//   0x04,
//   0x0E,
//   0x11,
//   0x11,
//   0x11,
//   0x1F,
//   0x00
// };
void setup() {
  zahvat.attach(9);  // пин для подключения микро серво
  povorot.attach(8);
  pinMode(stepPin, OUTPUT);  //
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(stepPin3, OUTPUT);
  pinMode(dirPin3, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ks, INPUT);
  pinMode(kz, INPUT);
  pinMode(kb, INPUT);
  MsTimer2::set(2, timerInterupt);
  MsTimer2::start();
  Serial.begin(115200);
  povorot.write(85);  // tell servo to go to position in variable 'pos'
  zahvat.detach();
}
void loop() {
  if (Serial.available()) {
    character = Serial.read();
    content.concat(character);
    Serial.println(content);
    m = character - '0';
    if (m == 1) {
      first();
      // first();
      // first();
    }
  }
}
void timerInterupt() {
  if (Serial.available()) {
    character = Serial.read();
    content.concat(character);
    Serial.println(content);
    m = character - '0';
    if (m == 4) {
      Serial.write("priem");
      flag = 1;
    }
    if (m == 5) {
      Serial.write("priem");

      flag = 0;
      Serial.println("lala");
    }
  }
}