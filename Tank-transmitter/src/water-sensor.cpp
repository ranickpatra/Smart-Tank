#include "water-sensor.h"

#include "config.h"

int water_level_pins[] = WATER_LEVEL_PINS;

void water_sensor_init() {
  pinMode(WATER_LEVEL_ENABLE_PIN, OUTPUT);
  digitalWrite(WATER_LEVEL_ENABLE_PIN, LOW);

  for (uint8_t i = 0; i < WATER_LEVEL_PINS_COUNT; i++) {
    pinMode(water_level_pins[i], INPUT);
  }
}

uint8_t water_sensor_read_water_level() {
  digitalWrite(WATER_LEVEL_ENABLE_PIN, HIGH);
  delay(2); // wait for 2ms
  uint8_t water_level = 0;
  for (uint8_t i = 0; i < WATER_LEVEL_PINS_COUNT; i++) {
    if (!digitalRead(water_level_pins[i])) {
      water_level++;
    }
  }
  digitalWrite(WATER_LEVEL_ENABLE_PIN, LOW);
  return water_level;
}