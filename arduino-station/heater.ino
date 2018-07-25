#define HEATER_PIN D8

void initializeHeater() {
  pinMode(HEATER_PIN, OUTPUT);
  analogWrite(HEATER_PIN, 0); //0 (always off) - 255 (always on)
}
