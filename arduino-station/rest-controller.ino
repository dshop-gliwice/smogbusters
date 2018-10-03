#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* gatewayUrl = "http://api.smogbusters.org:8080/api/measurement";

unsigned long sendCount = 0;
unsigned long sendCountFailed = 0;

void initClient() {
    Serial.println();
    Serial.print("Gateway url: ");
    Serial.println(gatewayUrl);
    Serial.print("MAC: ");
    Serial.println(WiFi.macAddress());
    Serial.print("FW version: ");
    Serial.println(FW_VERSION);

    Serial.print("Connecting to ");
    Serial.println(ctx.wifiSSID);

    Serial.flush();

    WiFi.mode(WIFI_STA);
    WiFi.begin(ctx.wifiSSID, ctx.wifiPasswd);

    int i=0;
    while (WiFi.status() != WL_CONNECTED && i<40) {
      blinkStatusLed();
      Serial.print(".");
      i++;
    }
    
    if (WiFi.status() == WL_CONNECTED){
      Serial.println("WIFI connected");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
      enableStatusLed();
    }else{
      Serial.println("WIFI is NOT connected");
    }
}

bool sendMeasurement(Measurement * msr, size_t memSize) {
    //Prepare data
    DynamicJsonBuffer jsonBuffer(memSize);

    JsonObject& json = jsonBuffer.createObject();
    json["version"] = msr->version;

    JsonObject& idField = json.createNestedObject("id");
    idField["uuid"] = msr->id.uuid;
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
    dataField["cnt"] = sendCount;
    dataField["cnt_failed"] = sendCountFailed;
    dataField["heater_state"] = getHeaterState();
    dataField["firmware"] = msr->data.firmware;

    String payload;
    json.printTo(payload);
    Serial.println(payload);
    
    // Send data
    if(WiFi.status() != WL_CONNECTED){
      return false;
    }

    HTTPClient client;
    client.begin(gatewayUrl);
    client.addHeader("Content-Type", "application/json");

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
