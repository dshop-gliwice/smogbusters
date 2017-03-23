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
    values.dew = dewPointFast(values.temp, values.hum);
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
  MeasurementData values = readTemp();
  Serial.print("DATA:");
  Serial.print(values.temp);
  Serial.print(";");
  Serial.print(values.humidity);
  Serial.print(";");
  Serial.println(values.preassure);
}
