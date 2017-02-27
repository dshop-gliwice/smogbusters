#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include "Timer.h"
#include "dht.h"


Timer timer;

#define DHT_PIN 3
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
  readContext();

  //timer.every(READ_CYCLE, readAndSend);
}

void loop() {
  while (Serial.available() > 0) readSerial();
  timer.update();
}
