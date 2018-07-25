#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "SAP-Guest";
const char* password = "";

const char* gatewayUrl = "http://35.156.69.56:8080/api/measurement";

void initClient() {
    Serial.println();
    Serial.print("MAC: ");
    Serial.println(WiFi.macAddress());

    Serial.print("Connecting to ");
    Serial.println(ssid);

    Serial.flush();

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      blinkStatusLed();
      Serial.print(".");
    }
    enableStatusLed();
    Serial.println("WIFI connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}
unsigned long cnt = 0;
unsigned long cntFailed = 0;
bool sendMeasurement(Measurement * msr, size_t memSize){
    cnt++;
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
    dataField["pressure"] = msr->data.pressure;
    dataField["pm25"] = msr->data.pm25;
    dataField["pm10"] = msr->data.pm10;
    dataField["pm1"] = msr->data.pm1;
    dataField["DStemp"] = msr->data.DStemp;
    dataField["free_heap"] = ESP.getFreeHeap();
    dataField["cnt"] = cnt;
    dataField["cnt_failed"] = cntFailed;

    String payload;
    json.printTo(payload);
    Serial.println(payload);

    int httpCode = client.POST(payload);
    Serial.println("Request sent");
    if (httpCode != HTTP_CODE_OK) {
      Serial.printf("Request failed, error: %s\n", client.errorToString(httpCode).c_str());
      cntFailed++;
      if (cntFailed > 10) {
        disableStatusLed();
        ESP.restart();
      }
      return false;
    }
    cntFailed=0;

    Serial.flush();
    client.end();
    return true;
}
