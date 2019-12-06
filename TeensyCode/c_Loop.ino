//loop

void loop() {
  int legPositions [NUM_LEGS] [3];
  for (int i = 0; i < NUM_LEGS; i++) {
    legPositions[i][0] = kInitialPositions[i][0];
    legPositions[i][1] = kInitialPositions[i][1];
    legPositions[i][2] = kInitialPositions[i][2];
  }

  GaitTripod(legPositions, 10000, millis(), 0, 0, 0, 0);
}
