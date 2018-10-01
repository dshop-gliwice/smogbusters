#define HEATER_PIN D6

#define HEATER_POWER      500 // in mW
#define HEATER_RESISTANCE 18 // in ohms

int heaterState = 0;

void initializeHeater() {
  pinMode(HEATER_PIN, OUTPUT);
  analogWriteFreq(100);
  setHeaterState(0);
}

void setHeaterState(int val) {
  heaterState = val;
  analogWrite(HEATER_PIN, heaterState); //0 (always off) - 1023 (always on)
}

int getHeaterState() {
  return heaterState;
}

// TODO - safety when no sensor is present or sensor is broken
void updateHeater(Measurement * msr) {
  char msg[10];

  int heaterFullPower = 1000 * ctx.voltage * ctx.voltage / HEATER_RESISTANCE; // heater power when powered at 100% PWM
  int heaterPWMPower = 1023 * HEATER_POWER / heaterFullPower;                 // PWM duty cycle to reach HEATER_POWER power

  int heatPwr = constrain(map(msr->data.humidity, 50, 90, 0, heaterPWMPower), 0, heaterPWMPower);
  if(msr->data.temp > 25) heatPwr = 0;
  setHeaterState(heatPwr);
}
