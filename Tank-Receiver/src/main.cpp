#include <Arduino.h>

#include "alarm.h"
#include "config.h"
#include "indicator.h"
#include "motor.h"
#include "receiver.h"

uint8_t indicator_level_placeholder[] = {0, 1, 3, 7, 15};
uint8_t water_level, prev_water_level;
unsigned long last_data_time, current_time, tank_full_time;
uint8_t error_count = 0;
uint16_t loop_counter;

void startup_sequence() {
  for (uint8_t i = 0; i < 4; i++) {
    for (uint8_t j = 1; j <= 4; j++) {
      indicator_show(indicator_level_placeholder[j]);
      delay(50);
    }
    for (uint8_t j = 1; j <= 4; j++) {
      indicator_show(~indicator_level_placeholder[j]);
      delay(50);
    }
    alarm_toggle();
    delay(200);
  }

  indicator_show(indicator_level_placeholder[4]);
  alarm_stop();
}

void setup() {
  alarm_init();
  indicator_init();
  motor_init();
  receiver_init();

  startup_sequence();
  delay(1000);




  // int _pin_l = 3;
  // pinMode(_pin_l, OUTPUT);

  // while (1)
  // {
  //   digitalWrite(_pin_l, HIGH);
  //   delay(80);
  //   digitalWrite(_pin_l, LOW);
  //   delay(80);
  // }
  
}

void loop() {
  current_time = millis();
  water_level = receiver_get_data();
  // water_level = water_level > MAX_WATER_LEVEL ? MAX_WATER_LEVEL : water_level;
  last_data_time = receiver_last_receive_time();

  // updating last_data_time to prevent unwanted behaviour
  if (current_time < last_data_time) {
    last_data_time = 0;
  }

  if (water_level != prev_water_level && water_level == MAX_WATER_LEVEL) {
    tank_full_time = current_time;
  }
  // updating tank_full_time to prevent unwanted behaviour
  if (current_time < tank_full_time) {
    tank_full_time = 0;
  }

  // TODO change time limit based on water level
  if (current_time - last_data_time > NO_RECEIVE_ERROR_TIME) {
    // not receiving data

    if (error_count < 2) {
      error_count++;
    } else {
      motor_off();
      indicator_error();
      if (!(loop_counter % 4)) {
        alarm_toggle();
      }
    }
  } else {
    // receiving data

    // motor
    if (water_level == MAX_WATER_LEVEL) {
      motor_off();
    } else {
      motor_continue();
    }

    // alarm
    if (tank_full_time - current_time < TANK_FULL_ALARM_TIME) {
      if (!(loop_counter % 2)) {
        alarm_toggle();
      }
    } else {
      alarm_stop();
    }

    // indicator
    indicator_show(indicator_level_placeholder[water_level + 1]);
  }

  loop_counter++;
  prev_water_level = water_level;
  delay(500);
}
