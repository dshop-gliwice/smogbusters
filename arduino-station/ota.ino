#include <ESP8266httpUpdate.h>
#define OTA_CHECK_DELAY 10 * 60000

/*
 * Copied from http://esp8266.github.io/Arduino/versions/2.0.0/doc/ota_updates/ota_updates.html
 *
 */
void initOTA(){
  timer.every(OTA_CHECK_DELAY, otaUpdate);
  otaUpdate();
}

void otaUpdate() {
  Serial.println("OTA check");
  t_httpUpdate_return ret = ESPhttpUpdate.update("ota.smogbusters.org", 8081, "/update.php", FW_VERSION);
  switch(ret) {
    case HTTP_UPDATE_FAILED:
        Serial.println("[update] Update failed.");
        break;
    case HTTP_UPDATE_NO_UPDATES:
        Serial.println("[update] Update no Update.");
        break;
    case HTTP_UPDATE_OK:
        Serial.println("[update] Update ok."); // may not be called cause we reboot the ESP
        break;
    default:
        Serial.println("[update] Undefined response.");
  }
  Serial.println(ESPhttpUpdate.getLastErrorString());
}
