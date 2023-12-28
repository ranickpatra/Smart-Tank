#include <Arduino.h>

#include "config.h"
#include "deep-sleep.h"
#include "interrupts.h"
#include "transmitter.h"
#include "water-sensor.h"



uint16_t deep_sleep_time = 0;
volatile int prev_water_level = 0;
volatile uint8_t data_send_counter = 0;

void setup() {
  deep_sleep_init();

  transmitter_init();
  water_sensor_init();
}

void loop() {
#ifdef LASER_TEST
  transmitter_send(2);
  delay(1500);
#else
  int water_level = water_sensor_read_water_level();

  if (water_level < (WATER_LEVEL_PINS_COUNT - 1)) {
    transmitter_send(WATER_EMPTY_VALUE + water_level);
    data_send_counter = 0;
    deep_sleep_time = 16;  // sleep for 2 min

  } else if (water_level == (WATER_LEVEL_PINS_COUNT - 1)) {
    // tank is about to full
    data_send_counter++;

    if (data_send_counter >= 2) {
      data_send_counter = 0;
      transmitter_send(WATER_EMPTY_VALUE + water_level);
    }

    deep_sleep_time = 8;  // sleep for 24 sec

  } else if (water_level == WATER_LEVEL_PINS_COUNT) {
    // tank is full

    if ((water_level - prev_water_level) > 0) {
      data_send_counter = 0;
      transmitter_send(WATER_EMPTY_VALUE + water_level);
      data_send_counter = 0;
      deep_sleep_time = 8;  // sleep for 8 sec
    } else {
      if (data_send_counter < 2) {
        transmitter_send(WATER_EMPTY_VALUE + water_level);
        data_send_counter++;
        deep_sleep_time = 8;  // sleep for 8 sec
      } else {
        transmitter_send(WATER_EMPTY_VALUE + water_level);
        deep_sleep_time = 16;  // sleep for 2 min
      }
    }
  }

  prev_water_level = water_level;

  deep_sleep(deep_sleep_time);
#endif
}
