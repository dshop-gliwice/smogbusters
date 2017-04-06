#define CONFIG_START  100
#define CONFIG_VERSION  "qw1"


struct {
  char ver[4];
  char deviceID[UUID_LENGTH];
} ctx = {CONFIG_VERSION, "newID"};

void checkContext() {
  if (! readContext()){
    Serial.println("Generating new deviceID");
    String id;
    getUUID(id);
    id.toCharArray(ctx.deviceID, UUID_LENGTH);
    saveContext();
  }
  Serial.print("DeviceID: ");
  Serial.println(ctx.deviceID);
}

bool readContext() {
  // To make sure there are settings, and they are YOURS!
  // If nothing is found it will use the default settings.
  if (EEPROM.read(CONFIG_START + 0) == CONFIG_VERSION[0] &&
      EEPROM.read(CONFIG_START + 1) == CONFIG_VERSION[1] &&
      EEPROM.read(CONFIG_START + 2) == CONFIG_VERSION[2]) {
    for (unsigned int t = 0; t < sizeof(ctx); t++)
      *((char*)&ctx + t) = EEPROM.read(CONFIG_START + t);
      Serial.println("Context data loaded from EEPROM");
    return true;
  }
  Serial.println("Context data are not present in EEPROM");
  return false;
}

void saveContext() {
  Serial.println("Context saved");
  for (unsigned int t = 0; t < sizeof(ctx); t++) {
    EEPROM.write(CONFIG_START + t, *((char*)&ctx + t));
  }
  EEPROM.commit();
}

void getUUID(String &uuid){
  int sum = 0;
  for (int i=0;i<256;i++) {
    sum += analogRead(0);
    delay(2);
  }
  randomSeed(sum);
  
  String mac = WiFi.macAddress();
  mac.replace(":","");
  
  String randStr = String(random(1000000000, 2147483647)); 
  uuid = mac + randStr;
}
