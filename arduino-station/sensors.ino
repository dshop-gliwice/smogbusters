void initializeSensor() {
  pinMode(DHT_PIN, INPUT);
  timer.every(READ_CYCLE, readAndSend);
}

MeasurementData readTemp() {  
  int chk = DHT.read11(DHT_PIN);
  MeasurementData values = {0.0, 0.0, 0.0, 0.0, 0.0};
  if (chk == DHTLIB_OK) {    
    values.temp = DHT.temperature;
    values.humidity = DHT.humidity;
    values.preassure = dewPointFast(values.temp, values.humidity);
  }
  else
  {  
    Serial.println(chk);
  }
  return values;
}

double dewPointFast(double celsius, double humidity)
{
  double a = 17.271;
  double b = 237.7;
  double temp = (a * celsius) / (b + celsius) + log(humidity * 0.01);
  double Td = (b * temp) / (a - temp);
  return Td;
}


void readAndSend() {
  MeasurementData data = readTemp();
  
  Measurement measurement = {"v1",{"ABC1234","0.0.1","DHT11"},data};
  bool msrSent = sendMeasurement(&measurement, sizeof(measurement));
  if(!msrSent){
    Serial.println("Could not sent measurement");
  }
}
