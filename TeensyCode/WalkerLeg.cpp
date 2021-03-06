#include "WalkerLeg.h"

WalkerLeg::WalkerLeg(int offX, int offY, int offZ, float offRZ, int coxa, int femur, int tibia, int tarsus, const int limits[WALKER_LEG_NUMSERVOS][2], const int ids[WALKER_LEG_NUMSERVOS], Stream* servoSerialIn) {
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
    servoLimits[i][0] = limits[i][0];
    servoLimits[i][1] = limits[i][1];

    servoIDs[i] = ids[i];
  }
}

void WalkerLeg::initializeServos() {
}

void WalkerLeg::setSide(bool newSide) {
  side = newSide;
}

bool WalkerLeg::writeServos(float toWrite[WALKER_LEG_NUMSERVOS]) {
  Serial.print("");

  return true;
}

bool WalkerLeg::setXYZ(float result[WALKER_LEG_NUMSERVOS], int posXYZ[3]) {

  //shift origin to base of leg
  posXYZ[0] -= offsetX;
  posXYZ[1] -= offsetY;
  posXYZ[2] -= offsetZ;

  //rotate to match leg orientation
  rotateCoords(posXYZ); //{femur, coxa, tibia}

  //
<<<<<<< Updated upstream
  float pos_x = posXYZ[0];
  float pos_y = posXYZ[1];
  float pos_z = posXYZ[2];
=======
  float pos_x = posXYZdup[0];
  float pos_y = posXYZdup[1];
  float pos_z = posXYZdup[2];

  
  Serial1.printf("WalkerLeg::setXYZ: global x:%3d, y:%3d, z:%3d local x:%3f, y:%3f, z:%3f\n",
                posXYZ[0], posXYZ[1], posXYZ[2],
                pos_x, pos_y, pos_z);
  
>>>>>>> Stashed changes

  float desiredAngle[WALKER_LEG_NUMSERVOS];
  
  float leg_radius = sqrt((pos_x*pos_x)+(pos_y*pos_y));

  //coxa servo
  desiredAngle[0] = atan2f(pos_y,pos_x);

  //femur servo
  desiredAngle[1] = (atan2f(pos_z,leg_radius) + acos(((femurLength*femurLength)-((leg_radius*leg_radius)+(pos_z*pos_z))-(tibiaLength*tibiaLength))/(-2*sqrt((leg_radius*leg_radius)+(pos_z*pos_z))*tibiaLength)));

  //tibia servo
  desiredAngle[2] = -(acosf(((tibiaLength*tibiaLength)+(femurLength*femurLength)-((leg_radius*leg_radius)+(pos_z*pos_z)))/(-2*femurLength*tibiaLength)));
<<<<<<< Updated upstream

  for (int i = 0; i < WALKER_LEG_NUMSERVOS; i++) {
    Serial.print(servoIDs[i]);
    Serial.print(", ");
    Serial.println(desiredAngle[i]);
    setServo(servoIDs[i], desiredAngle[i]);
  }

  




=======
  Serial1.print("Leg angles");
  for (int i = 0; i < WALKER_LEG_NUMSERVOS; i++) {
    //Serial.print(servoIDs[i]);
    Serial1.print(", ");
    Serial1.print(desiredAngle[i]);
    //setServo(servoIDs[i], desiredAngle[i]);
  }
  Serial1.print("\n");
>>>>>>> Stashed changes
  return true;
}

void WalkerLeg::rotateCoords(int posXYZ[3]) {
  int posXYZdup[3];
  posXYZdup[0] = posXYZ[0];
  posXYZdup[1] = posXYZ[1];
  posXYZdup[2] = posXYZ[2];

  float rotationMatrix[3][3] = {
    {cosf(offsetRZ), -sinf(offsetRZ), 0},
    {sinf(offsetRZ), cosf(offsetRZ), 0},
    {0, 0, 1}
  };

  posXYZ[0] = rotationMatrix[0][0] * posXYZdup[0] + rotationMatrix[0][1] * posXYZdup[1] + rotationMatrix[0][2] * posXYZdup[2];
  posXYZ[1] = rotationMatrix[1][0] * posXYZdup[0] + rotationMatrix[1][1] * posXYZdup[1] + rotationMatrix[1][2] * posXYZdup[2];
  posXYZ[2] = rotationMatrix[2][0] * posXYZdup[0] + rotationMatrix[2][1] * posXYZdup[1] + rotationMatrix[2][2] * posXYZdup[2];
}

//Write to Servo
bool WalkerLeg::setServo(int servoID, float rads) {
<<<<<<< Updated upstream
  Serial.print(servoID);
  Serial.print(" set to: ");
  Serial.println(rads);
  int Pos = constrain( (map((int)(rads * 180.0 / PI), -90, 90, 1000, 2000)), 1200, 1800);

  Serial.println(Pos);
  //void ServoWrite(byte ServoID, unsigned int Pos){

  
  byte Header = 170; //Header that opens the command and allows autobaudrate to be set
  byte Device = 12; //Identifier for the maestro in case of chaining Default 12
  byte TruncatedCommand = 04;//0x04 represents the command to set servo position
  byte Servoplace = constrain(servoID, 0, 999); //127);//the location of the servo on the controller
  byte Data1 = 0;//This holds the lower 7 bits of the position
  byte Data2 = 0;//This holds the upper 7 bits of the position
  unsigned long ScalePos = Pos * 4;
  for (int i = 0; i < 7; i++) {
    bitWrite(Data1, i, bitRead(ScalePos, i));
  }
  for (int i = 0; i < 7; i++) {
    bitWrite(Data2, i, bitRead(ScalePos, (i + 7)));
  }
  //Write the packet
  /*
    Serial.println(Header);
    Serial.println(Device);
    Serial.println(TruncatedCommand);
    Serial.println(Servoplace);
    Serial.println(Data1);
    Serial.println(Data2);
    */
    
  WALKER_LEG_MAESTRO_SERIAL.write(Header);
  WALKER_LEG_MAESTRO_SERIAL.write(Device);
  WALKER_LEG_MAESTRO_SERIAL.write(TruncatedCommand);
  WALKER_LEG_MAESTRO_SERIAL.write(Servoplace);
  WALKER_LEG_MAESTRO_SERIAL.write(Data1);
  WALKER_LEG_MAESTRO_SERIAL.write(Data2);
=======
  Serial1.print(servoID);
  Serial1.print(" set to: ");
  Serial1.println(rads);
  legServos[servoID]->setServoRad(rads);
>>>>>>> Stashed changes

  return true;
}
