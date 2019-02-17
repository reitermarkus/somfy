#pragma once

const unsigned long E = 1000;

volatile int current_channel = -1;

volatile unsigned long last_interrupt = 0;
volatile unsigned long last_interrupt_ch1 = 0;
volatile unsigned long last_interrupt_ch2 = 0;
volatile unsigned long last_interrupt_ch3 = 0;
volatile unsigned long last_interrupt_ch4 = 0;

void ch1_interrupt() {
  int detected_channel = -1;
  unsigned long start = micros();
  last_interrupt = last_interrupt_ch1 = start;
  unsigned long last_interrupt_min = min(last_interrupt_ch2, min(last_interrupt_ch3, last_interrupt_ch4));
  if ((start - last_interrupt_min) < 150000) {
    detected_channel = 0;
  } else if (last_interrupt_ch1 > (last_interrupt_ch2 + E) && last_interrupt_ch1 > (last_interrupt_ch3 + E) && last_interrupt_ch1 > (last_interrupt_ch4 + E)) {
    detected_channel = 1;
  }

  if (last_interrupt <= start && detected_channel >= 0) {
    current_channel = detected_channel;
  }
}

void ch2_interrupt() {
  int detected_channel = -1;
  unsigned long start = micros();
  last_interrupt = last_interrupt_ch2 = start;
  unsigned long last_interrupt_min = min(last_interrupt_ch1, min(last_interrupt_ch3, last_interrupt_ch4));

  if ((start - last_interrupt_min) < 150000) {
    detected_channel = 0;
  } else if (last_interrupt_ch2 > (last_interrupt_ch1 + E) && last_interrupt_ch2 > (last_interrupt_ch3 + E) && last_interrupt_ch2 > (last_interrupt_ch4 + E)) {
    detected_channel = 2;
  }

  if (last_interrupt <= start && detected_channel >= 0) {
    current_channel = detected_channel;
  }
}

void ch3_interrupt() {
  int detected_channel = -1;
  unsigned long start = micros();
  last_interrupt = last_interrupt_ch3 = start;
  unsigned long last_interrupt_min = min(last_interrupt_ch1, min(last_interrupt_ch2, last_interrupt_ch4));
  if ((start - last_interrupt_min) < 150000) {
    detected_channel = 0;
  } else if (last_interrupt_ch3 > (last_interrupt_ch1 + E) && last_interrupt_ch3 > (last_interrupt_ch2 + E) && last_interrupt_ch3 > (last_interrupt_ch4 + E)) {
    detected_channel = 3;
  }

  if (last_interrupt <= start && detected_channel >= 0) {
    current_channel = detected_channel;
  }
}

void ch4_interrupt() {
  int detected_channel = -1;
  unsigned long start = micros();
  last_interrupt = last_interrupt_ch4 = start;
  unsigned long last_interrupt_min = min(last_interrupt_ch1, min(last_interrupt_ch2, last_interrupt_ch3));

  if ((start - last_interrupt_min) < 150000) {
    detected_channel = 0;
  } else if (last_interrupt_ch4 > (last_interrupt_ch1 + E) && last_interrupt_ch4 > (last_interrupt_ch2 + E) && last_interrupt_ch4 > (last_interrupt_ch3 + E)) {
    detected_channel = 4;
  }

  if (last_interrupt <= start && detected_channel >= 0) {
    current_channel = detected_channel;
  }
}
