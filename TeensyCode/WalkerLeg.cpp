#include "WalkerLeg.h"

WalkerLeg::WalkerLeg(int offX, int offY, int offZ, float offRZ, int coxa, int femur, int tibia, int tarsus, MyServo* servos[]) {
  side = true;
  offsetX = offX;
  offsetY = offY;
  offsetZ = offZ;
  offsetRZ = offRZ;
  coxaLength = coxa;
  femurLength = femur;
  tibiaLength = tibia;
  tarsusLength = tarsus;
  for (int i = 0; i < WALKER_LEG_NUMSERVOS; i++) {
    legServos[i] = servos[i];
  }
}

void WalkerLeg::setSide(bool newSide) {
  side = newSide;
}

bool WalkerLeg::writeServos(float toWrite[WALKER_LEG_NUMSERVOS]) {
  //Serial.print("");
  for (int i = 0; i < WALKER_LEG_NUMSERVOS; i ++){
    setServo(i, toWrite[i]);
  }

  return true;
}

bool WalkerLeg::setXYZ(float result[WALKER_LEG_NUMSERVOS], int posXYZ[3]) {

  int posXYZdup[3];
  //shift origin to base of leg
  posXYZdup[0] = posXYZ[0] - offsetX;
  posXYZdup[1] = posXYZ[1] - offsetY;
  posXYZdup[2] = posXYZ[2] - offsetZ;

  /*
  Serial.printf("WalkerLeg::setXYZ: global x:%3d, y:%3d, z:%3d linear shift x:%3d, y:%3d, z:%3d\n",
                posXYZ[0], posXYZ[1], posXYZ[2],
                posXYZdup[0], posXYZdup[1], posXYZdup[2]);
  */

  //rotate to match leg orientation
  rotateCoords(posXYZdup); //{femur, coxa, tibia}

  //
  float pos_x = posXYZdup[0];
  float pos_y = posXYZdup[1];
  float pos_z = posXYZdup[2];

  
  Serial.printf("WalkerLeg::setXYZ: global x:%3d, y:%3d, z:%3d local x:%3f, y:%3f, z:%3f\n",
                posXYZ[0], posXYZ[1], posXYZ[2],
                pos_x, pos_y, pos_z);
  

  float desiredAngle[WALKER_LEG_NUMSERVOS];
  
  float leg_radius = sqrt((pos_x*pos_x)+(pos_y*pos_y));

  //coxa servo
  desiredAngle[0] = atan2f(pos_y,pos_x);

  //femur servo
  desiredAngle[1] = (atan2f(pos_z,leg_radius) + acos(((femurLength*femurLength)-((leg_radius*leg_radius)+(pos_z*pos_z))-(tibiaLength*tibiaLength))/(-2*sqrt((leg_radius*leg_radius)+(pos_z*pos_z))*tibiaLength)));

  //tibia servo
  desiredAngle[2] = -(acosf(((tibiaLength*tibiaLength)+(femurLength*femurLength)-((leg_radius*leg_radius)+(pos_z*pos_z)))/(-2*femurLength*tibiaLength)));
  Serial.print("Leg angles");
  for (int i = 0; i < WALKER_LEG_NUMSERVOS; i++) {
    //Serial.print(servoIDs[i]);
    Serial.print(", ");
    Serial.print(desiredAngle[i]);
    //setServo(servoIDs[i], desiredAngle[i]);
  }
  Serial.print("\n");
  return true;
}

void WalkerLeg::rotateCoords(int posXYZ[3]) {
  float posXYZdup[3];
  
  posXYZdup[0] = posXYZ[0];
  posXYZdup[2] = posXYZ[2];
  posXYZdup[1] = posXYZ[1];
  
  /*
  Serial.printf("WalkterLeg::rotateCoords: input x:%3d, y:%3d, Z:%3d dup x:%3f, y:%3f, Z:%3f\n",
                posXYZ[0], posXYZ[1], posXYZ[2],
                posXYZdup[0], posXYZdup[1], posXYZdup[2]);
  */
  
  float rotationMatrix[3][3] = {
    {cosf(offsetRZ), -sinf(offsetRZ), 0},
    {sinf(offsetRZ), cosf(offsetRZ), 0},
    {0, 0, 1}
  };

  /*
  Serial.printf("WalkterLeg::rotateCoords: rotationMatrix = {{%2f,%2f,%2f},{%2f,%2f,%2f},{%2f,%2f,%2f}}\n",
                rotationMatrix[0][0],rotationMatrix[0][1],rotationMatrix[0][2],
                rotationMatrix[1][0],rotationMatrix[1][1],rotationMatrix[1][2],
                rotationMatrix[2][0],rotationMatrix[2][1],rotationMatrix[2][2]);
  */

  posXYZ[0] = (rotationMatrix[0][0] * posXYZdup[0] + rotationMatrix[0][1] * posXYZdup[1] + rotationMatrix[0][2] * posXYZdup[2]);
  posXYZ[1] = (rotationMatrix[1][0] * posXYZdup[0] + rotationMatrix[1][1] * posXYZdup[1] + rotationMatrix[1][2] * posXYZdup[2]);
  posXYZ[2] = (rotationMatrix[2][0] * posXYZdup[0] + rotationMatrix[2][1] * posXYZdup[1] + rotationMatrix[2][2] * posXYZdup[2]);

  //Serial.printf("WalkerLeg::rotateCoords({%3f,%3f,%3f}) (RZ:%2f)-> {%3d,%3d,%3d}\n", posXYZdup[0], posXYZdup[1], posXYZdup[2],offsetRZ, posXYZ[0], posXYZ[1], posXYZ[2]);
}

//Write to Servo
bool WalkerLeg::setServo(int servoID, float rads) {
  Serial.print(servoID);
  Serial.print(" set to: ");
  Serial.println(rads);
  legServos[servoID]->setServoRad(rads);

  return true;
}
