#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "Timer.h"


#define READ_CYCLE 10000

#define UUID_LENGTH 25
#define FW_VERSION "18.11.18-a"

Timer timer;

struct MeasurementId {
  char uuid[UUID_LENGTH];
  char sensors [10];      
};
  
struct MeasurementData {
  float temp;
  float humidity;
  float pressure;
  int pm25;
  int pm10;
  int pm1;
  float DStemp;
  char firmware [15];
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
  randomSeed(analogRead(0));
  EEPROM.begin(512);
  initializeSerial();
  checkContext();
  initializeStatusLed();
  initializeHeater();
  initializeSensors();
  initializeLCD();
  initClient();
  initOTA();
}

void loop() {
  serialLoop();
  timer.update();
}
