#include "PMS.h"
#include <SoftwareSerial.h>
SoftwareSerial swSer(14, 12, false, 256);
PMS pms(swSer);
PMS::DATA rawData;

int PM01Value = 0;        //define PM1.0 value of the air detector module
int PM2_5Value = 0;       //define PM2.5 value of the air detector module
int PM10Value = 0;       //define PM10 value of the air detector module

void initializePMS() {
  swSer.begin(9600);
  swSer.setTimeout(2000);
}

PmsData pmsLoop() {
  PmsData data = {-1, -1, -1};
  if (pms.readUntil(rawData, 1000)) {
    data.pm1 = rawData.PM_AE_UG_1_0;
    data.pm25 = rawData.PM_AE_UG_2_5;
    data.pm10 = rawData.PM_AE_UG_10_0;
  }
  
  return data;
}
