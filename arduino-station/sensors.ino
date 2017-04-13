#define DS1820_INITDELAY 100

void initializeSensors() {
  initializeBME();
  initializePMS();
  if(initializeDS()) {
    timer.after(DS1820_INITDELAY, requestDS1820);
  }
  timer.every(READ_CYCLE, readAndSend);
}

void readAndSend() {
  
  MeasurementData data = readMeasurementFromBME();
  PmsData pmsData = pmsLoop();
  data.pm25 = pmsData.pm25;
  data.pm10 = pmsData.pm10;
  data.pm1 = pmsData.pm1;
  data.DStemp = DStemp;
  Measurement measurement = {"1", {"uuid", "0.0.1", "BME280"}, data};
  memcpy( measurement.id.uuid, ctx.deviceID, UUID_LENGTH*sizeof(char));
  bool msrSent = sendMeasurement(&measurement, sizeof(measurement));
  
  if (!msrSent) {
    Serial.println("Could not sent measurement");
  }
}
