#include "MyServo.h"
#include <math.h>

//call setServoRad from setServoDeg
void MyServo::setServoDeg(float pos){
  setServoRad(pos * M_PI / 180.0);
}

//call getServoRad for getServoDeg
float MyServo::getServoDeg(){
  return(getServoRad() * 180.0 / M_PI);
}

//call getServoLowerLimitRad for getServoLowerLimitDeg
float MyServo::getServoLowerLimitDeg(){
  return(getServoLowerLimitRad() * 180.0 / M_PI);
}

//call getServoUpperLimitRad for getServoUpperLimitDeg
float MyServo::getServoUpperLimitDeg(){
  return(getServoUpperLimitRad() * 180.0 / M_PI);
}

MyServo::~MyServo(){
  //nothing to delete
}
