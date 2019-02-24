#pragma once

#include <ArduinoOTA.h>
#include <Scheduler.h>

class OtaTask: public Task {
  protected:
    void setup() {
      ArduinoOTA.onStart([]() {
        Serial.println("OTA update started.");
      });

      ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("\rOTA update progress: %u%%", (progress / (total / 100)));
      });

      ArduinoOTA.onEnd([]() {
        Serial.println("\nOTA update finished, restarting…");
      });

      ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("\nOTA Error (%u): ", error);
        if (error == OTA_AUTH_ERROR) {
          Serial.println("Auth Failed");
        } else if (error == OTA_BEGIN_ERROR) {
          Serial.println("Begin Failed");
        } else if (error == OTA_CONNECT_ERROR) {
          Serial.println("Connect Failed");
        } else if (error == OTA_RECEIVE_ERROR) {
          Serial.println("Receive Failed");
        } else if (error == OTA_END_ERROR) {
          Serial.println("End Failed");
        }
      });

      ArduinoOTA.begin(false);
    }

    void loop() {
      ArduinoOTA.handle();
    }
};
