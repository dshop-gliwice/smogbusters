#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>
#include "Timer.h"

#define READ_CYCLE 5000

SoftwareSerial swSer(14, 12, false, 256);
Timer timer;

char serialInput[100];

struct MeasurementId {
    char uuid[20];
    char firmware [10];
    char sensors [10];      
};

struct MeasurementData {
    float temp;
    float humidity;
    float pressure;
    int pm25;
    int pm10;  
};
struct Measurement {
    char version [5];
    struct MeasurementId id;
    struct MeasurementData data;
};

struct PmsData {
    int pm1;
    int pm25;
    int pm10;  
};

void setup() {
  EEPROM.begin(512);
  initializeSerial();
  readContext();
  initializeSensors();
  initClient();
}

void loop() {
  serialLoop();
  timer.update();  
}
