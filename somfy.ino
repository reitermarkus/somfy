#include <Scheduler.h>

#include "helper.hpp"
#include "interrupts.hpp"
#include "network.hpp"
#include "ota.hpp"
#include "server.hpp"

#ifdef ARDUINO_ESP8266_NODEMCU
  const int CH1_PIN = D1;
  const int CH2_PIN = D2;
  const int CH3_PIN = D5;
  const int CH4_PIN = D6;

  const int UP_PIN = D4;
  const int STOP_PIN = D0;
  const int DOWN_PIN = D3;
  const int SWITCH_PIN = D7;
#elif ARDUINO_ESP8266_ESP12
#elif ARDUINO_MOD_WIFI_ESP8266
#else
#endif

NetworkTask network_task;
OtaTask ota_task;
ServerTask server_task;

void setup() {
  pinMode(CH1_PIN, INPUT_PULLUP);
  pinMode(CH2_PIN, INPUT_PULLUP);
  pinMode(CH3_PIN, INPUT_PULLUP);
  pinMode(CH4_PIN, INPUT_PULLUP);

  pinMode(UP_PIN, OUTPUT);
  pinMode(STOP_PIN, OUTPUT);
  pinMode(DOWN_PIN, OUTPUT);
  pinMode(SWITCH_PIN, OUTPUT);

  digitalWrite(UP_PIN, HIGH);
  digitalWrite(STOP_PIN, HIGH);
  digitalWrite(DOWN_PIN, HIGH);
  digitalWrite(SWITCH_PIN, HIGH);

  Serial.begin(115200);
  while (!Serial) {}
  Serial.println();

  delay(1000);

  channel();

  delay(5000);

  detect_channel();

  Scheduler.start(&network_task);
  Scheduler.start(&ota_task);
  Scheduler.start(&server_task);
  Scheduler.begin();
}

void loop() {}
