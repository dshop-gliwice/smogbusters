#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include "Timer.h"
#include "dht.h"

SoftwareSerial swSer(14, 12, false, 256);
Timer timer;

#define DHT_PIN 0
#define READ_CYCLE 1000

dht DHT;
WiFiServer server(80);

char serialInput[100];

struct Measurement {
  double temp; double hum; double dew;
};

void setup() {
  EEPROM.begin(512);
  initializeSerial();
  initializePMS();
  readContext();
  initializeSensor();
}

void loop() {
  serialLoop();
  pmsLoop();
  timer.update();
}
