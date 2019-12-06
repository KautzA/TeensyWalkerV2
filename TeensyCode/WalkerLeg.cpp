#include "WalkerLeg.h"

WalkerLeg::WalkerLeg(int offX, int offY, int offZ, float offRZ, int coxa, int femur, int tibia, int tarsus, const int limits[WALKER_LEG_NUMSERVOS][2], const int ids[WALKER_LEG_NUMSERVOS]) {
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
