#include "alarm.h"

#include "config.h"


void alarm_init() {
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
}

void alarm_play() {
  digitalWrite(BUZZER_PIN, HIGH);
}

void alarm_stop() {
  digitalWrite(BUZZER_PIN, LOW);
}

void alarm_toggle() {
  digitalWrite(BUZZER_PIN, !digitalRead(BUZZER_PIN));
}