#include <ESP32Servo.h>

typedef void Function();

Function *move;

Servo servo_motor_1;
Servo servo_motor_2;
Servo servo_motor_3;
Servo servo_motor_4;

int speed = 10;
int cycle = 5;

int counter_1 = 90;
int counter_2 = 99;
int counter_3 = 14;
int counter_4 = 104;

void standStill() {  
}

void attachMotors() {
  servo_motor_1.attach(5); // Controla a garra
  servo_motor_2.attach(23);// Levanta e abaixa o braço
  servo_motor_3.attach(13);// Movimento frente e tras
  servo_motor_4.attach(19);// Rotação esquerda e direita

  move = standStill;
}

void monitor() { // Monitorar o posiconamento de cada servo
  Serial.print("Motor garra: ");
  Serial.println(counter_1);
  Serial.print("Motor para cima e para baixo: ");
  Serial.println(counter_2);
  Serial.print("Motor para frente e para traz: ");
  Serial.println(counter_3);
  Serial.print("Motor rotação: ");
  Serial.println(counter_4);

  Serial.println("");
  Serial.println("-----------------------------------------");
  Serial.println("");
}

void closedClaw() {
 if(counter_1 <=180) {
  servo_motor_1.write(++counter_1);
 }

 monitor();
}

void openClaw() {
  if(counter_1 >= 0) {
    servo_motor_1.write(--counter_1);
  }

  monitor();
}

void raiseArm() {
  if(counter_2 >= 0) {
    servo_motor_2.write(++counter_2);
  }

  monitor();
}

void lowerArm() {
  if(counter_2 >= 0) {
    servo_motor_2.write(--counter_3);
  }

  monitor();
}

void strechArm() {
  if(counter_3 <= 180) {
    servo_motor_3.write(++counter_3);
  }

  monitor();
}

void retractArm() {
  if(counter_3 >= 0) {
    servo_motor_3.write(--counter_3);
  }

  monitor();
}

void rotateLeft() {
  if(counter_4 <= 180) {
    servo_motor_4.write(++counter_4);
  }

  monitor();
}

void rotateRight() {
  if(counter_4 >= 0) {
    servo_motor_4.write(--counter_4);
  }

  monitor();
}

void moveUp() {

}

void moveBack() {

}

void performAutomaticMoviment() {
  
}