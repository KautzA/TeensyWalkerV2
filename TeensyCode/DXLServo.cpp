#include "DXLServo.h"
#include<ax12Serial.h>   //KurtE's bioloid library https://github.com/KurtE/BioloidSerial
#include<BioloidSerial.h> //KurtE's bioloid library https://github.com/KurtE/BioloidSerial

//Constructor
//Relies on having bioloid library setup
DXLServo::DXLServo(int id, Stream* servoSerialIn){
  servo_id = id;
  //nothing when using KurtE's bioloid library
}

//Set angle of target servo
void DXLServo::setServoRad(float pos){
  float poscounts = (pos / 5.23599) * 1024 - 512;
  int counts = constrain(pos, 0, 1024);
  SetPosition(servo_id, counts);
}

//Get angle of target servo
float DXLServo::getServoRad(){
  return (((float)(ax12GetRegister(servo_id,AX_PRESENT_POSITION_L,2)))/1024.0)*5.23599;//setup for AX12
}

float DXLServo::getServoLowerLimitRad() {
  return (((float)(ax12GetRegister(servo_id,AX_CW_ANGLE_LIMIT_L,2)))/1024.0)*5.23599;//setup for AX12
}

float DXLServo::getServoUpperLimitRad() {
  return (((float)(ax12GetRegister(servo_id,AX_CCW_ANGLE_LIMIT_L,2)))/1024.0)*5.23599;//setup for AX12
}

//Deconstructor
DXLServo::~DXLServo(){
  
}
