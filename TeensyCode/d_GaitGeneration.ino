/*
   Generates gaits for hexapod
*/

void GaitTripod(int legPositions[NUM_LEGS][3], int period, int currentTime, int xVelocity, int yVelocity, int stepHeight, float yawVelocity) {
  int temp = currentTime % period;
  float squareWave = 0;
  float triangularWave = 0;

  //Generate waves from -1 to 1
  if (temp <= period / 2) {
    squareWave = 1;
    triangularWave = (4 * double(temp) / double(period)) - 1;
  } else {
    squareWave = -1;
    triangularWave = 2 - ((4 * double(temp) / double(period)) - 1);
  }

  //Scale waves based on direction of travel
  float scaledYawWave = (yawVelocity * PI / 4 * squareWave);
  float scaledXWave = xVelocity * triangularWave;
  float scaledYWave = yVelocity * triangularWave;
  float scaledZWave = (stepHeight / 2) * squareWave;

  //Add scaled values to initial leg positions
  for (int i = 0; i < NUM_LEGS; i++) {
    legPositions[i][0] += scaledXWave;
    legPositions[i][1] += scaledYWave;
    legPositions[i][2] += scaledZWave;

    //Add in rotation values
    legPositions[i][0] = (legPositions[i][0] * cosf(scaledYawWave) - output1[i][1] * sinf(scaledYawWave));
    legPositions[i][1] = (legPositions[i][0] * sinf(scaledYawWave) + output1[i][1] * cosf(scaledYawWave));
  }

  //Serial.println(String(squareWave) + ' ' + String(triangularWave));
}
