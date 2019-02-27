#pragma once

const unsigned long TOLERANCE = 1000;

volatile unsigned long last_interrupt = 0;
volatile unsigned long _last_interrupt_ch1 = 0;
volatile unsigned long _last_interrupt_ch2 = 0;
volatile unsigned long _last_interrupt_ch3 = 0;
volatile unsigned long _last_interrupt_ch4 = 0;

extern const int CH1_PIN;
extern const int CH2_PIN;
extern const int CH3_PIN;
extern const int CH4_PIN;

int detect_channel() {
  Serial.println("Detecting channel…");

  int detected_channel = -1;

  while (detected_channel == -1) {
    unsigned long last_interrupt_ch1 = _last_interrupt_ch1;
    unsigned long last_interrupt_ch2 = _last_interrupt_ch2;
    unsigned long last_interrupt_ch3 = _last_interrupt_ch3;
    unsigned long last_interrupt_ch4 = _last_interrupt_ch4;

    unsigned long last_interrupt_min = min(last_interrupt_ch1, min(last_interrupt_ch2, min(last_interrupt_ch3, last_interrupt_ch4)));
    unsigned long last_interrupt_max = max(last_interrupt_ch1, max(last_interrupt_ch2, max(last_interrupt_ch3, last_interrupt_ch4)));

    if (last_interrupt_max - last_interrupt_min < 250000) {
      detected_channel = 0;
    } else if ((last_interrupt_max == last_interrupt_ch1) && (last_interrupt_ch1 > (last_interrupt_ch2 + TOLERANCE)) && (last_interrupt_ch1 > (last_interrupt_ch3 + TOLERANCE)) && (last_interrupt_ch1 > (last_interrupt_ch4 + TOLERANCE))) {
      detected_channel = 1;
    } else if ((last_interrupt_max == last_interrupt_ch2) && (last_interrupt_ch2 > (last_interrupt_ch1 + TOLERANCE)) && (last_interrupt_ch2 > (last_interrupt_ch3 + TOLERANCE)) && (last_interrupt_ch2 > (last_interrupt_ch4 + TOLERANCE))) {
      detected_channel = 2;
    } else if ((last_interrupt_max == last_interrupt_ch3) && (last_interrupt_ch3 > (last_interrupt_ch1 + TOLERANCE)) && (last_interrupt_ch3 > (last_interrupt_ch2 + TOLERANCE)) && (last_interrupt_ch3 > (last_interrupt_ch4 + TOLERANCE))) {
      detected_channel = 3;
    } else if ((last_interrupt_max == last_interrupt_ch4) && (last_interrupt_ch4 > (last_interrupt_ch1 + TOLERANCE)) && (last_interrupt_ch4 > (last_interrupt_ch2 + TOLERANCE)) && (last_interrupt_ch4 > (last_interrupt_ch3 + TOLERANCE))) {
      detected_channel = 4;
    } else {
      detected_channel = 0;
    }

    if (last_interrupt != last_interrupt_max) {
      detected_channel = -1;
    }
  }

  Serial.printf("Channel %d detected.\n", detected_channel);
  return detected_channel;
}

void ch1_interrupt() {
  last_interrupt = _last_interrupt_ch1 = micros();
}

void ch2_interrupt() {
  last_interrupt = _last_interrupt_ch2 = micros();
}

void ch3_interrupt() {
  last_interrupt = _last_interrupt_ch3 = micros();
}

void ch4_interrupt() {
  last_interrupt = _last_interrupt_ch4 = micros();
}

void enable_interrupts() {
  attachInterrupt(digitalPinToInterrupt(CH1_PIN), ch1_interrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(CH2_PIN), ch2_interrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(CH3_PIN), ch3_interrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(CH4_PIN), ch4_interrupt, CHANGE);
}

void disable_interrupts() {
  detachInterrupt(digitalPinToInterrupt(CH1_PIN));
  detachInterrupt(digitalPinToInterrupt(CH2_PIN));
  detachInterrupt(digitalPinToInterrupt(CH3_PIN));
  detachInterrupt(digitalPinToInterrupt(CH4_PIN));
}
