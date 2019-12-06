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
  servoSerial = servoSerialIn;
}

void WalkerLeg::initializeServos() {
}

void WalkerLeg::setSide(bool newSide) {
	side = newSide;
}

bool WalkerLeg::writeServos(float toWrite[WALKER_LEG_NUMSERVOS][3]) {
	Serial.print("");
	
	return true;
}

bool WalkerLeg::setXYZ(float result[WALKER_LEG_NUMSERVOS][3], int posXYZ[3]) {
    posXYZ[0] -= offsetX;
    posXYZ[1] -= offsetY;
    posXYZ[2] -= offsetZ;
    
    rotateCoords(posXYZ);
    return true;
}

void WalkerLeg::rotateCoords(int posXYZ[3]){
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

  int Pos = constrain( (map((rads * 180 / PI),-90, 90, 1000, 2000)), 1000, 2000);
//void ServoWrite(byte ServoID, unsigned int Pos){
  byte Header = 170; //Header that opens the command and allows autobaudrate to be set
  byte Device = 12; //Identifier for the maestro in case of chaining Default 12
  byte TruncatedCommand = 04;//0x04 represents the command to set servo position
  byte Servoplace = constrain(servoID,0,999);//127);//the location of the servo on the controller
  byte Data1 = 0;//This holds the lower 7 bits of the position
  byte Data2 = 0;//This holds the upper 7 bits of the position
  unsigned long ScalePos = Pos*4;
  for (int i = 0; i < 7; i++){
    bitWrite(Data1,i,bitRead(ScalePos,i));
  }
  for (int i = 0; i < 7; i++){
    bitWrite(Data2,i,bitRead(ScalePos,(i+7)));
  }
  //Write the packet
  /*
  USER_SERIAL.println(Header);
  USER_SERIAL.println(Device);
  USER_SERIAL.println(TruncatedCommand);
  USER_SERIAL.println(Servoplace);
  USER_SERIAL.println(Data1);
  USER_SERIAL.println(Data2);
  */
  servoSerial->write(Header);
  servoSerial->write(Device);
  servoSerial->write(TruncatedCommand);
  servoSerial->write(Servoplace);
  servoSerial->write(Data1);
  servoSerial->write(Data2);

  return true;
}
