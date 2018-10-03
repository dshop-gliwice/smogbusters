#include "PMS.h"
#include <SoftwareSerial.h>
SoftwareSerial swSer(14, 12, false, 256);
PMS pms(swSer);
PMS::DATA rawData;

//#define LENG 31   //0x42 + 31 bytes equal to 32 bytes
//unsigned char buf[LENG];

int PM01Value = 0;        //define PM1.0 value of the air detector module
int PM2_5Value = 0;       //define PM2.5 value of the air detector module
int PM10Value = 0;       //define PM10 value of the air detector module

void initializePMS() {
  swSer.begin(9600);
  swSer.setTimeout(2000);
}

PmsData pmsLoop() {
  pms.readUntil(rawData, 2000);
  PmsData data = {rawData.PM_AE_UG_1_0, rawData.PM_AE_UG_2_5, rawData.PM_AE_UG_10_0};
  return data;
}
