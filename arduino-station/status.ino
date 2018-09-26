#define STATUS_PIN D3

void initializeStatusLed() {
  pinMode(STATUS_PIN, OUTPUT);
  disableStatusLed();
}

void enableStatusLed() {
  digitalWrite(STATUS_PIN, LOW);
}

void disableStatusLed() {
  digitalWrite(STATUS_PIN, HIGH);
}

void blinkStatusLed() {
    disableStatusLed();
    delay(250);
    enableStatusLed();
    delay(250);
    disableStatusLed();
}

void testStatusLed() {
  while (true) {
    enableStatusLed();
    delay(500);
    disableStatusLed();
    delay(500);
  }
}

