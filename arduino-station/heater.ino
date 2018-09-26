#define HEATER_PIN D8

int heaterState = 0;

void initializeHeater() {
  pinMode(HEATER_PIN, OUTPUT);
  setHeaterState(0);
}

void setHeaterState(int val){
  heaterState = val;
  analogWrite(HEATER_PIN, val); //0 (always off) - 255 (always on)
}

int getHeaterState(){
  return heaterState;
}

