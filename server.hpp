#pragma once

#include <Scheduler.h>
#include <ArduinoJson.h>
#include <ESP8266WebServer.h>

#include "helper.hpp"

class ServerTask: public Task {
  public:
    ServerTask(): Task(), server(80) {}

  private:
    ESP8266WebServer server;

  protected:
    void setup() {
      Serial.println("Starting web server ...");

      server.on("/", HTTP_POST, [this]() {
        String json = server.arg("plain");

        Serial.printf("Received: %s\n", json.c_str());

        DynamicJsonDocument doc(1024);

        DeserializationError error = deserializeJson(doc, json);

        if (error) {
          server.send(400, "application/json", "{\"error\":\"invalid JSON\"}");
          return;
        }

        const JsonObject& obj = doc.as<JsonObject>();

        if (!obj.containsKey("channel")) {
          server.send(400, "application/json", "{\"error\":\"missing key \\\"channel\\\"\"}");
          return;
        }

        if (!obj.containsKey("command")) {
          server.send(400, "application/json", "{\"error\":\"missing key \\\"command\\\"\"}");
          return;
        }

        int channel = obj["channel"];
        String command = obj["command"];

        if (command == "up") {
          up(channel);
          server.send(204, "application/json", "");
          return;
        } else if (command == "stop") {
          stop(channel);
          server.send(204, "application/json", "");
          return;
        } else if (command == "down") {
          down(channel);
          server.send(204, "application/json", "");
          return;
        } else if (command == "switch") {
          switch_channel(channel);
          server.send(204, "application/json", "");
        }

        server.send(400, "application/json", "{\"error\":\"invalid command \\\"" + command + "\\\"\"}");
      });

      server.begin();
    }

    void loop() {
      server.handleClient();
      yield();
    }
};
