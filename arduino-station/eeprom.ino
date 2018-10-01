#define CONFIG_START  100
#define CONFIG_VERSION  "qw1"
String defaultWifiSSID = "public";
String defaultWifiPassword = "empty";

struct {
  char ver[4];
  char deviceID[UUID_LENGTH];
  char wifiSSID[32];
  char wifiPasswd[32];
  unsigned int voltage;
  unsigned int bmeI2CAddress;
} ctx = {CONFIG_VERSION, "newID", "-", "-", 0x77};

void checkContext() {
  if (! readContext()) {
    Serial.println("Generating new deviceID");
    String id;
    generateUUID(id);
    id.toCharArray(ctx.deviceID, UUID_LENGTH);
    ctx.voltage = 12;
    saveContext();
  }

  if (! findEOS(ctx.wifiSSID, 32)) {
    defaultWifiSSID.toCharArray(ctx.wifiSSID, 32);
    saveContext();
  }

  if (! findEOS(ctx.wifiPasswd, 32)) {
    defaultWifiPassword.toCharArray(ctx.wifiPasswd, 32);
    saveContext();
  }

  char info[100]; memset(info, '\0', sizeof(info));
  contextToStr(info);
  Serial.println(info);
}

void contextToStr(char *answer) {
  char append[4];

  strcat(answer, "\n>DeviceID: '");
  strcat(answer, ctx.deviceID);
  strcat(answer, "'\n>WIFI SSID: '");
  strcat(answer, ctx.wifiSSID);
  strcat(answer, "'\n>WIFI PSWD: '");
  strcat(answer, ctx.wifiPasswd);
  strcat(answer, "'\n>BmeI2CAddress : '");
  sprintf(append, "%u", ctx.bmeI2CAddress);
  strcat(answer, "'\n>Heater voltage : '");
  sprintf(append, "%u", ctx.voltage);
  strcat(answer, append);
  strcat(answer, "'");
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

void generateUUID(String &uuid) {
  int sum = 0;
  for (int i = 0; i < 256; i++) {
    sum += analogRead(0);
    delay(2);
  }
  randomSeed(sum);

  String mac = WiFi.macAddress();
  mac.replace(":", "");

  String randStr = String(random(1000000000, 2147483647));
  uuid = mac + randStr;
}

bool findEOS(char *a, int arraySize) {
  for (int i = 0; i < arraySize; i++) {
    if (a[i] == '\0') {
      return true;
    }
  }
  return false;
}
