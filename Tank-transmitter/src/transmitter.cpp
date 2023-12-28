#include "transmitter.h"

#include "config.h"

void transmitter_init() {
  pinMode(LASER_PIN, OUTPUT);
  digitalWrite(LASER_PIN, HIGH);
}

void transmitter_send(uint8_t data) {
  for (uint8_t i = 0; i < data; i++) {
    digitalWrite(LASER_PIN, LOW);
    delay(TRANSMITTER_DELAY);
    digitalWrite(LASER_PIN, HIGH);
    delay(TRANSMITTER_DELAY);
  }
}