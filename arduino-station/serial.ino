void initializeSerial() {
  Serial.begin(115200);
  Serial.setTimeout(2000);
  Serial.flush();

  memset(serialInput, '\0', sizeof(serialInput));
}


void readSerial() {
  char inChar = (char)Serial.read();
  if (inChar == '\n') {
    serialCommand(serialInput);
    memset(serialInput, '\0', sizeof(serialInput));
  }
  else {
    byte len = strlen(serialInput);
    serialInput[len] = inChar;
    serialInput[len + 1] = '\0';
  }
}

void serialCommand(char *command) {
  char param[50]; memset(param, '\0', sizeof(param));
  char answer[50]; memset(answer, '\0', sizeof(answer));

  byte commandLen = strlen(command);
  if (commandLen > 2) {
    strncpy(param, command + 2, commandLen - 2);
    param[commandLen - 2] = '\0';
  }
  strncpy(answer, command, 1);
  strcat(answer, ":");
  switch (command[0]) {
    case 'i': strcat(answer, ctx.deviceID); break;
    case 'I': memset(ctx.deviceID, '\0', sizeof(ctx.deviceID)); strcat(ctx.deviceID, param); saveContext(); strcat(answer, "OK"); break;
    default:  strcat(answer, "Command unknown");
  }
  Serial.println(answer);
}

