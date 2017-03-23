#include "dht.h"

#define DHT_PIN 4

dht DHT;

void initializeDHT() {

   pinMode(DHT_PIN, INPUT);
}

double dewPointFast(double celsius, double humidity){
  
  double a = 17.271;
  double b = 237.7;
  double temp = (a * celsius) / (b + celsius) + log(humidity * 0.01);
  double Td = (b * temp) / (a - temp);
  return Td;
}

MeasurementData readMeasurementFromDHT() {  
  
  int chk = DHT.read11(DHT_PIN);
  
  MeasurementData values = {0.0, 0.0, 0.0, 0.0, 0.0};
  
  if (chk == DHTLIB_OK) {   
     
    values.temp = DHT.temperature;
    values.humidity = DHT.humidity;
    values.pressure = dewPointFast(values.temp, values.humidity);
  }
  else {  
    Serial.println(chk);
  }
  
  return values;
}
