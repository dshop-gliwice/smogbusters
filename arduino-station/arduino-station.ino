#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "Timer.h"


#define READ_CYCLE 5000
#define UUID_LENGTH 25

Timer timer;

struct MeasurementId {
  char uuid[UUID_LENGTH];
  char firmware [10];
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
}

void loop() {
  serialLoop();
  timer.update();
}
