#include <ESP32SERVO.h>

typedef void Function();

Function *move;

Servo servo_motor1;
Servo servo_motor2;
Servo servo_motor3;
Servo servo_motor4;

int speed = 10;
int cycle = 2;

int counter_1;
int counter_2;
int counter_3;
int counter_4;

void standStill() {  
}

void closedClaw() {
 if(counter_1 <=180) {
  servo_motor_1.write(++counter_1);
 }
}

void openClaw() {
  if(counter_1 >= 0) {
    servo_motor_1.write(--counter_1);
  }
}

void raiseArm() {
  if(counter_2 >= 0) {
    servo_motor_2.write(++counter_2);
  }
}

void lowerArm() {
  if(counter_2 >= 0) {
    servo_motor_2.write(--counter_3);
  }
}

void strechArm() {
  if(counter_3 <= 180) {
    servo_motor_3.write(++counter_3);
  }
}

void retractArm() {
  if(counter_3 >= 0) {
    servo_motor_3.write(--counter_3);
  }
}

void rotateLeft() {
  if(counter_4 <= 180) {
    servo_motor_4.write(++counter_4);
  }
}

void rotateRight() {
  if(counter_4 >= 0) {
    servo_motor_4.write(--counter_4);
  }
}

void moveUp() {

}

void moveBack() {

}

void performAutomaticMoviment() {
  
}