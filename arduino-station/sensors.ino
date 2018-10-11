#define DS1820_INITDELAY 100

void initializeSensors() {
  delay(100);
  initializeBME();
  initializePMS();
  if(initializeDS()) {
    timer.after(DS1820_INITDELAY, requestDS1820);
  }
  timer.every(READ_CYCLE, readAndSend);
}

void readAndSend() {
  sendCount++;
  MeasurementData data = readMeasurementFromBME();
  PmsData pmsData = pmsLoop();
  strcpy(data.firmware, FW_VERSION);
  data.pm25 = pmsData.pm25;
  data.pm10 = pmsData.pm10;
  data.pm1 = pmsData.pm1;
  data.DStemp = DStemp;
  Measurement measurement = {"1", {"uuid", "BME280"}, data};
  memcpy( measurement.id.uuid, ctx.deviceID, UUID_LENGTH*sizeof(char));
  bool msrSent = sendMeasurement(&measurement, sizeof(measurement));
  if (!msrSent) {
    Serial.println("Could not send the measurement");
    sendCountFailed++;
    if (sendCountFailed > 9) {
      disableStatusLed();
      Serial.println("Too many failed attempts. Rebooting");
      delay(500);
      ESP.restart();
     }
  }else{
    sendCountFailed=0;
  }
  
  updateLCD(&measurement);
  updateHeater(&measurement);
  
  blinkStatusLed();
  if (msrSent) {
    enableStatusLed();
  }else{
    disableStatusLed();
  }
}
