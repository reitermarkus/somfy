#pragma once

#include "interrupts.hpp"

extern const int CH1_PIN;
extern const int CH2_PIN;
extern const int CH3_PIN;
extern const int CH4_PIN;

extern const int UP_PIN;
extern const int STOP_PIN;
extern const int DOWN_PIN;
extern const int SWITCH_PIN;

unsigned long last_switch = 0;

bool switching() {
  if (last_switch == 0) {
    return false;
  }

  if (last_switch > (micros() - 4000000)) {
    return true;
  }

  delay(2000);
  return false;
}

void up() {
  disable_interrupts();
  digitalWrite(UP_PIN, LOW);
  delay(100);
  digitalWrite(UP_PIN, HIGH);
  last_switch = 0;
  delay(400);
}

void stop() {
  disable_interrupts();
  digitalWrite(STOP_PIN, LOW);
  delay(100);
  digitalWrite(STOP_PIN, HIGH);
  last_switch = 0;
  delay(400);
}

void down() {
  disable_interrupts();
  digitalWrite(DOWN_PIN, LOW);
  delay(100);
  digitalWrite(DOWN_PIN, HIGH);
  last_switch = 0;
  delay(400);
}

void channel() {
  enable_interrupts();
  digitalWrite(SWITCH_PIN, LOW);
  delay(100);
  digitalWrite(SWITCH_PIN, HIGH);
  last_switch = micros();
  delay(400);
}

void next_channel() {
  int count = switching() ? 1 : 2;

  for (int i = 0; i < count; i++) {
    channel();
  }
}

void switch_channel(int channel) {
  int from = detect_channel();
  int to = channel;

  if (from == to) {
    return;
  }

  int diff = (to - from + 5) % 5;

  for (int i = 0; i < diff; i++) {
    next_channel();
  }

  delay(500);
}

void up(int channel) {
  switch_channel(channel);
  up();
}


void stop(int channel) {
  switch_channel(channel);
  stop();
}


void down(int channel) {
  switch_channel(channel);
  down();
}
