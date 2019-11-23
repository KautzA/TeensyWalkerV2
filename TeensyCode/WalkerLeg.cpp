#include "WalkerLeg.h"

WalkerLeg::WalkerLeg(int offX, int offY, int offZ, float offRZ, int coxa, int femur, int tibia, int tarsus, float limits[WALKER_LEG_NUMSERVOS][2], int ids[WALKER_LEG_NUMSERVOS]) {
	side = true;
	offsetX = offX;
	offsetY = offY;
	offsetZ = offZ;
	offesetRZ = offRZ;
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
	serial.print();
	
	return true;
}
