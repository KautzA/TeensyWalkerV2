/*
 * Generates gaits for hexapod
 */

 void GaitTripod(int period, int currentTime) {
  int temp = currentTime%period;
  
  if (temp <= period/2){
    squareWave = 1
    triangularWave = 2*(double(temp)/double(period)); 
  } else {
    squareWave = -1
    triangularWave = 1-2*(double(temp)/double(period));
  }

  
 }
