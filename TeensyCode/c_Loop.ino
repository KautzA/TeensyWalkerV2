//loop

void loop() {
  //Get time for synchronization purposes
  int currentTime = millis();
  USER_SERIAL.println("\r\n-----------------------");
  USER_SERIAL.println(currentTime);
  
  //Blink lights
  if (currentTime%1000 > 500) {
    blinkAllLights(1);
  } else {
    blinkAllLights(0);
  }

  //Get initial leg positions
  int legPositions [NUM_LEGS] [3];
  for (int i = 0; i < NUM_LEGS; i++) {
    legPositions[i][0] = kInitialPositions[i][0];
    legPositions[i][1] = kInitialPositions[i][1];
    legPositions[i][2] = kInitialPositions[i][2];
  }

  //Calculate walking leg positions
  GaitTripod(legPositions, 10000, currentTime, 20, 0, 20, 0);
  delay(100);

  int targetLeg0[3];
  int targetLeg1[3];
  int targetLeg2[3];
  int targetLeg3[3];
  int targetLeg4[3];
  int targetLeg5[3];

  float anglesLeg0[3] = {0,0,0};
  float anglesLeg1[3] = {0,0,0};
  float anglesLeg2[3] = {0,0,0};
  float anglesLeg3[3] = {0,0,0};
  float anglesLeg4[3] = {0,0,0};
  float anglesLeg5[3] = {0,0,0};
   
  for (int i = 0; i < 3; i++) {
    targetLeg0[i] = legPositions[0][i];
    targetLeg1[i] = legPositions[1][i];
    targetLeg2[i] = legPositions[2][i];
    targetLeg3[i] = legPositions[3][i];
    targetLeg4[i] = legPositions[4][i];
    targetLeg5[i] = legPositions[5][i];
  }

  Serial.print(targetLeg0[0]);
  Serial.print(", ");
  Serial.print(targetLeg0[1]);
  Serial.print(", ");
  Serial.print(targetLeg0[2]);
  Serial.println("Leg0 Coords");
  
  leg0.setXYZ(anglesLeg0, targetLeg0);
  leg4.setXYZ(anglesLeg4, targetLeg4);

  leg1.setServo(3,0);
}

void blinkAllLights(int state){
  digitalWrite(LED_RUNNING, state);
  digitalWrite(LED_ERROR, 1-state);
  digitalWrite(LED_RGB_RED, state);
  digitalWrite(LED_RGB_GRE, state);
  digitalWrite(LED_RGB_BLU, 1-state);
}
