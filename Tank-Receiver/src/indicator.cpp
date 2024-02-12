#include "indicator.h"

#include "config.h"

uint8_t indicator_pins[] = INDICATOR_PINS;
bool indicator_error_status = false;

void indicator_init() {
  for (uint8_t i = 0; i < INDICATOR_PINS_COUNT; i++) {
    pinMode(indicator_pins[i], OUTPUT);
    digitalWrite(indicator_pins[i], LOW);
  }
}

void indicator_show(uint8_t data) {
  for (uint8_t i = 0; i < INDICATOR_PINS_COUNT; i++) {
    digitalWrite(indicator_pins[i], !!(data & (1 << i)));
  }
}

void indicator_error() {
  indicator_error_status = !indicator_error_status;
  for (uint8_t i = 0; i < INDICATOR_PINS_COUNT; i++) {
    digitalWrite(indicator_pins[i], indicator_error_status);
  }
}