#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <wifi_info.h>
#include <arduino_homekit_server.h>

// Set web server port number to 80
WiFiServer server(80);

// D4
// const int RELAY = 2;
// access your HomeKit characteristics defined in my_accessory.c
extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_switch_on;

void on_switch_change(const homekit_value_t value) {
  bool on = value.bool_value;
  cha_switch_on.value.bool_value = on;
  if (on) {
    digitalWrite(D4, LOW);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.print("Turned on");
  }
  else {
    digitalWrite(D4, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print("Turned off");
  }

  Serial.print(on);
}

void setup() {
  Serial.begin(9600);
  pinMode(D4, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(D4, LOW);
  digitalWrite(LED_BUILTIN, LOW); 
  // homekit_storage_reset();

  wifi_connect();
  cha_switch_on.setter = on_switch_change;
  arduino_homekit_setup(&config);
  digitalWrite(D4, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);

}

void loop() {
  arduino_homekit_loop();
  delay(10);
}