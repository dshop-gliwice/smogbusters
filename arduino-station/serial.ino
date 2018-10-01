char serialInput[100];

void initializeSerial() {
  Serial.begin(115200);
  Serial.println();
  Serial.setTimeout(2000);
  Serial.flush();

  memset(serialInput, '\0', sizeof(serialInput));
}

void serialLoop() {
  while (Serial.available() > 0) readSerial();
}

void readSerial() {
  char inChar = (char)Serial.read();
  if (inChar == '\n') {
    serialCommand(serialInput);
    memset(serialInput, '\0', sizeof(serialInput));
  } else {
    byte len = strlen(serialInput);
    serialInput[len] = inChar;
    serialInput[len + 1] = '\0';
  }
}

void serialCommand(char *command) {
  char param[50]; memset(param, '\0', sizeof(param));
  char answer[100]; memset(answer, '\0', sizeof(answer));
  byte commandLen = strlen(command);
  if (commandLen > 2) {
    strncpy(param, command + 2, commandLen - 2);
    param[commandLen - 2] = '\0';
  }
  strncpy(answer, command, 1);
  strcat(answer, ": ");
  switch (command[0]) {
    case 'i':
      contextToStr(answer);
      break;
    case 'I': //set device ID
      memset(ctx.deviceID, '\0', sizeof(ctx.deviceID));
      strcat(ctx.deviceID, param);
      contextToStr(answer);
      saveContext();
      break;
    case 'S': // set wifi network name
      memset(ctx.wifiSSID, '\0', sizeof(ctx.wifiSSID));
      strcat(ctx.wifiSSID, param);
      contextToStr(answer);
      saveContext();
      break;
    case 'P': //set password for wifi
      memset(ctx.wifiPasswd, '\0', sizeof(ctx.wifiPasswd));
      strcat(ctx.wifiPasswd, param);
      contextToStr(answer);
      saveContext();
      break;
    case 'B': //set BME i2c address
      ctx.bmeI2CAddress = atoi(param);
      contextToStr(answer);
      saveContext();
      break;
    case 'V': //set heater voltage
      ctx.voltage = atoi(param);
      contextToStr(answer);
      saveContext();
      break;

    default:  strcat(answer, "Command unknown");
  }

  Serial.print("Response: ");
  Serial.println(answer);
}
