#ifndef WALKER_LEG
#define WALKER_LEG

#include <math.h>
#include <Arduino.h>


#define WALKER_LEG_NUMSERVOS 3
class WalkerLeg {
	private:
		//static const int kNumServos;
		
		bool side; //use femur down (false) or femur up (true) solution for position.
		int offsetX;
		int offsetY;
		int offsetZ;
		float offsetRZ;
		int coxaLength;
		int femurLength;
		int tibiaLength;
		int tarsusLength;
		float servoLimits[WALKER_LEG_NUMSERVOS][2];
		int servoIDs[WALKER_LEG_NUMSERVOS];
	public:
		
		//constructor for a leg
		WalkerLeg(int offX, int offY, int offZ, float offRZ, int coxa, int femur, int tibia, int tarsus, const int limits[WALKER_LEG_NUMSERVOS][2], const int ids[WALKER_LEG_NUMSERVOS]);
		
		//set result to the angles that will place the foot at the specified locaton, returns true if possible, false if impossible.
		bool setXYZ(float result[WALKER_LEG_NUMSERVOS][3], int posXYZ[3]);
		
		//set the side boolean
		void setSide(bool newSide);
		
		//write the servos in this leg and returns true if no error
		bool writeServos(float toWrite[WALKER_LEG_NUMSERVOS][3]);

   //Rotates a leg
   void rotateCoords(int setXYZ[3]);
};

#endif
