#include "SparkFunBME280.h"
#include "Wire.h"

BME280 sensor;
bool bmeIsActive = false;

void initializeBME() {

  sensor.settings.commInterface = I2C_MODE;
  //sensor.settings.I2CAddress = 0x77; //119
  //sensor.settings.I2CAddress = 0x76; //118
  sensor.settings.I2CAddress = ctx.bmeI2CAddress;
  sensor.settings.runMode = 3;
  sensor.settings.tStandby = 0;
  sensor.settings.filter = 0;
  sensor.settings.tempOverSample = 1;
  sensor.settings.pressOverSample = 1;
  sensor.settings.humidOverSample = 1;

  sensor.begin();

  //BME280 requires about 2 ms to start up.
  delay(50);
  if (sensor.readTempC() > -100){
    bmeIsActive = true;
  }
  
  Serial.print("BME280 state: ");
  Serial.println(bmeIsActive);
}

MeasurementData readMeasurementFromBME() {

  MeasurementData data = {0.0, 0.0, 0.0, 0, 0, 0, 0.0};
  if (bmeIsActive){
    data.temp = sensor.readTempC(); //celsius
    data.pressure = sensor.readFloatPressure() / 100; //hPa
    data.humidity = sensor.readFloatHumidity(); //%
  }
  return data;
}

