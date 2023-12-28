#include "deep-sleep.h"

#include "config.h"

void deep_sleep_init() {
  // set all pins as output to save power
  for (int i = 0; i < 20; i++) pinMode(i, OUTPUT);

  // Disable analog to digital converter
  ADCSRA &= ~(1 << ADEN);

#ifndef LASER_TEST
  // setup watch dog
  cli();                                 // Disable global interrupts
  WDTCSR = ((1 << WDCE) | (1 << WDE));   // WDCE and WDE - also resets
  WDTCSR = ((1 << WDP3) | (1 << WDP0));  // prescalers only - get rid of WDE and WDCE bit and run WD every 8s
  // WDTCSR = ((1 << WDP2) | (1 << WDP1));  // prescalers only - get rid of WDE and WDCE bit and run WD every 1s
  WDTCSR |= (1 << WDIE);  // enable interrupt mode
  sei();                  // Enable global interrupts

  // enable sleep
  SMCR |= (1 << SM1);  // Powerdown Mode
  // SMCR |= ((1 << SM1) | (1 << SM0));
  SMCR |= (1 << SE);  // enable sleep
#endif
}

void deep_sleep(uint16_t sec) {
#ifndef LASER_TEST
  sec /= 8;  // as WD timer is for every 8s
  for (uint16_t i = 0; i < sec; i++) {
    // BOD disable
    MCUCR |= ((1 << BODS) | (1 << BODSE));          // set both BODS and BODSE at the same time
    MCUCR = (MCUCR & ~(1 << BODSE)) | (1 << BODS);  // then set the BODS bit and clear the BODSE bit at the same time

    __asm__ __volatile__("sleep");  // execute sleep instruction
  }
#endif
}
