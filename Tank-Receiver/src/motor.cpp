#include "motor.h"
#include "config.h"

void motor_init() {
  pinMode(MOTOR_STOP_PIN, OUTPUT);
  digitalWrite(MOTOR_STOP_PIN, LOW);
}

void motor_off() {
  digitalWrite(MOTOR_STOP_PIN, HIGH);
}

void motor_continue() {
  digitalWrite(MOTOR_STOP_PIN, LOW);
}

void motor_stop() {
  motor_off();
  delay(500);
  motor_continue();
}

