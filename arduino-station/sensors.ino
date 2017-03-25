void initializeSensors() {

  initializeBME();
  initializePMS();
  timer.every(READ_CYCLE, readAndSend);
}

void readAndSend() {
  
  MeasurementData data = readMeasurementFromBME();
  PmsData pmsData = pmsLoop();
  data.pm25 = pmsData.pm25;
  data.pm10 = pmsData.pm10;
  Measurement measurement = {"1", {"ABC1234", "0.0.1", "BME280"}, data};
  
  bool msrSent = sendMeasurement(&measurement, sizeof(measurement));
  
  if (!msrSent) {
  
    Serial.println("Could not sent measurement");
  }
}
