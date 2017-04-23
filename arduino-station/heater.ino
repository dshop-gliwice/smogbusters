#define HEATER_PIN D6

void initializeHeater() {
  pinMode(HEATER_PIN, OUTPUT);  
  digitalWrite(HEATER_PIN, LOW);
}
