

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "set_me";
const char* password = ""; 
const char* gatewayUrl = "http://172.20.10.2:3000/data";

void initClient() {
    Serial.begin(115200);
    Serial.print("Connecting to ");
    Serial.println(ssid);
    Serial.flush();
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
      delay(250);
      Serial.print(".");
    }  
    Serial.println();
}

bool sendMeasurement(Measurement * msr, size_t memSize){
    if(WiFi.status() != WL_CONNECTED){
      return false;
    }
    
    HTTPClient client;
    client.begin(gatewayUrl);
    client.addHeader("Content-Type", "application/json");
    DynamicJsonBuffer jsonBuffer(memSize);
 
    JsonObject& json = jsonBuffer.createObject();
    json["version"] = msr->version;
    
    JsonObject& idField = json.createNestedObject("id");
    idField["uuid"] = msr->id.uuid;
    idField["firmware"] = msr->id.firmware;
    idField["sensors"] = msr->id.sensors;
    
    JsonObject& dataField = json.createNestedObject("data");
    dataField["temp"] = msr->data.temp;
    dataField["humidity"] = msr->data.humidity;
    dataField["preassure"] = msr->data.preassure;
    dataField["pm25"] = msr->data.pm25;
    dataField["pm10"] = msr->data.pm10;  
  
    String payload;
    json.printTo(payload);
    Serial.println(payload);
    
    int httpCode = client.POST(payload);
    Serial.println("Request sent");
    if (httpCode != HTTP_CODE_OK) {
      Serial.printf("Request failed, error: %s\n", client.errorToString(httpCode).c_str());
      return false;
    } 
    
    Serial.flush();
    client.end();  
    return true;  
}
