#pragma once

#include <Arduino.h>

void receiver_init();
uint8_t receiver_get_data();
unsigned long receiver_last_receive_time();