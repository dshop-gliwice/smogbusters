#include <OneWire.h>
#include <DallasTemperature.h>

#define DS1820_CYCLE 200
#define DS1820_DELAY 100
#define DS_PIN D7   //SSD3

OneWire dsWire(DS_PIN);
DallasTemperature dsSensor(&dsWire);
DeviceAddress dsThermometer;

float DStemp = 0.0;

bool initializeDS() {
  dsSensor.begin();
  bool sensorConnected = dsSensor.getAddress(dsThermometer, 0);
  if(sensorConnected) {
    dsSensor.setResolution(dsThermometer, 10);
    dsSensor.setWaitForConversion(false);

    readDS1820();
  }
  Serial.print("DS18B20 state: ");
  Serial.println(sensorConnected);
  return sensorConnected;
}

void requestDS1820() {
  dsSensor.requestTemperaturesByAddress(dsThermometer);
  timer.after(DS1820_CYCLE, readDS1820);
}

void readDS1820() {
  DStemp = dsSensor.getTempC(dsThermometer);
  timer.after(DS1820_DELAY, requestDS1820);
}

