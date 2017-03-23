#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>
#include "Timer.h"
#include "dht.h"

SoftwareSerial swSer(14, 12, false, 256);
Timer timer;

#define DHT_PIN 4
#define READ_CYCLE 5000

dht DHT;

char serialInput[100];

struct MeasurementId {
    char uuid[20];
    char firmware [10];
    char sensors [10];      
};

struct MeasurementData {
    float temp;
    float humidity;
    float preassure;
    float pm25;
    float pm10;  
};
struct Measurement {
    char version [5];
    struct MeasurementId id;
    struct MeasurementData data;
};

void setup() {
  EEPROM.begin(512);
  initializeSerial();
  //initializePMS();
  readContext();
  initializeSensor();
  initClient();
}

void loop() {
  serialLoop();
  //pmsLoop();
  timer.update();  
}
