#include "MyServo.h"
#include <math.h>

//call setServoRad from setServoDeg
void MyServo::setServoDeg(int id, float pos){
  setServoRad(id, pos * M_PI / 180.0);
}

//call getServoRad for getServoDeg
float MyServo::getServoDeg(int id){
  return(getServoRad(id) * 180.0 / M_PI);
}

//call getServoLowerLimitRad for getServoLowerLimitDeg
float MyServo::getServoLowerLimitDeg(){
  return(getServoLowerLimitRad() * 180.0 / M_PI);
}

//call getServoUpperLimitRad for getServoUpperLimitDeg
float MyServo::getServoUpperLimitDeg(){
  return(getServoUpperLimitRad() * 180.0 / M_PI);
}
