#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE); //4 lines lcd - ok

byte smiley[8] = {
  B00000,  
  B01010,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
  B00000
};

byte sadface[8] = {
  B00000,  
  B01010,
  B00000,
  B00000,
  B01110,
  B10001,
  B00000,
  B00000
};

void lcdPrintCenter(const char* data) {
  int prefixLen=(20-strlen(data))/2;
  String prefix="";
  for (int x=0; x<prefixLen; x++){
    prefix += " ";
  }
  lcd.print(prefix);
  lcd.print(data);
}

void initializeLCD() {
  if (ctx.lcdEnabled != 't') return;
  lcd.begin (20,4);
  lcd.createChar (0, smiley);    // load smiley to memory 0
  lcd.createChar (1, sadface);    // load sadface to memory 0
  lcd.setBacklight(HIGH);
  //**************************
  lcd.clear();
  lcd.setCursor(0, 0);
  lcdPrintCenter("Version");
  lcd.setCursor(0, 1);
  lcdPrintCenter(FW_VERSION);
  delay(1000);
  //**************************
  lcd.clear();
  lcd.setCursor(0, 0);
  lcdPrintCenter("SMOGBUSTERS.ORG");
  lcd.setCursor(0, 1);
  lcdPrintCenter("Connecting to WIFI");
  lcd.setCursor(1, 2);
  lcdPrintCenter(ctx.wifiSSID);
  lcd.setCursor(1, 3);
  lcd.print(WiFi.macAddress());
}

void clrLine(int n) {
  lcd.setCursor(0, n);
  lcd.print("                    ");
  lcd.setCursor(0, n);
}

void updateLCD(Measurement * msr) {
  if (ctx.lcdEnabled != 't') return;
  char msg[10];
  
  lcd.setCursor(0, 0);
  lcd.print("T: ");
  lcd.print(msr->data.temp, 1);
  lcd.print((char)223);
  lcd.print("C   ");
  

  lcd.setCursor(11, 0);
  sprintf(msg, "PM10: %-3d", msr->data.pm10);
  lcd.print(msg);
  
//**************************
  lcd.setCursor(0, 1);
  lcd.print("H: ");
  lcd.print(msr->data.humidity, 1);
  lcd.print("%   ");

  lcd.setCursor(12, 1);
  sprintf(msg, "2.5: %-3d", msr->data.pm25);
  lcd.print(msg);

//**************************
  lcd.setCursor(0, 2);
  lcd.print("P: ");
  lcd.print(msr->data.pressure, 1);
  lcd.print("hP    ");

  lcd.setCursor(14, 2);
  sprintf(msg, "1: %-3d", msr->data.pm1);
  lcd.print(msg);
  
//**************************
  lcd.setCursor(0, 3);
  lcd.print("Tds: ");
  lcd.print(msr->data.DStemp, 1);
  lcd.print((char)223);
  lcd.print("C    ");
  lcd.setCursor(13, 3);
  lcd.print("CN: ");
  if (WiFi.status() != WL_CONNECTED){
    lcd.print(char(1));
    lcd.print(sendCountFailed);
  }else{
    lcd.print(char(0));
    lcd.print(sendCountFailed);
  }
}

