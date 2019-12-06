//loop

void loop() {
  if (millis()%1000 > 500) {
    blinkAllLights(1);
  } else {
    blinkAllLights(0);
  }
  int legPositions [NUM_LEGS] [3];
  for (int i = 0; i < NUM_LEGS; i++) {
    legPositions[i][0] = kInitialPositions[i][0];
    legPositions[i][1] = kInitialPositions[i][1];
    legPositions[i][2] = kInitialPositions[i][2];
  }

  GaitTripod(legPositions, 10000, millis(), 20, 0, 5, 0);
}

void blinkAllLights(int state){
  digitalWrite(LED_RUNNING, state);
  digitalWrite(LED_ERROR, 1-state);
  digitalWrite(LED_RGB_RED, state);
  digitalWrite(LED_RGB_GRE, state);
  digitalWrite(LED_RGB_BLU, 1-state);
}
