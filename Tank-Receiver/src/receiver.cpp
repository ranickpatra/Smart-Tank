#include "receiver.h"

#include "config.h"

volatile unsigned long _receiver_last_receive_time;
volatile unsigned long _receiver_now;
volatile unsigned long _receiver_pulse_in_time;
volatile uint8_t _receiver_data;
uint8_t _receiver_data_2;

void receiver_on_receive() {
  _receiver_pulse_in_time = millis();
  if (_receiver_pulse_in_time < _receiver_now + LASER_MIN_PULSE_DURATION)
    return;

  _receiver_now = _receiver_pulse_in_time;

  if ((_receiver_now - _receiver_last_receive_time) > RECEIVE_TIME_GAP) {
    _receiver_last_receive_time = _receiver_now;
    _receiver_data = 0;
  }

  _receiver_data++;
}

void receiver_init() {
  pinMode(LASER_INPUT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(LASER_INPUT_PIN), receiver_on_receive,
                  RISING);
}

uint8_t receiver_get_data() {

  if (millis() > (_receiver_last_receive_time + RECEIVE_TIME_GAP)) {
    uint8_t water_level = _receiver_data - WATER_EMPTY_VALUE;
    if (_receiver_data < WATER_EMPTY_VALUE) {
      water_level = 0;
    }

    _receiver_data_2 =
        water_level > MAX_WATER_LEVEL ? MAX_WATER_LEVEL : water_level;
  }

  return _receiver_data_2;
}

unsigned long receiver_last_receive_time() {
  return _receiver_last_receive_time;
}