#ifndef WALKER_LEG
#define WALKER_LEG

#include <math.h>
#include <Arduino.h>
#include "MyServo.h"

#define WALKER_LEG_NUMSERVOS 3
//#define WALKER_LEG_MAESTRO_SERIAL Serial1
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
    MyServo *legServos[WALKER_LEG_NUMSERVOS];//pointer to array
  public:

    //constructor for a leg
    WalkerLeg(int offX, int offY, int offZ, float offRZ, int coxa, int femur, int tibia, int tarsus, MyServo* servos[]);
    
    //set the value of a servo
    bool setServo(int id, float rads);

    //set result to the angles that will place the foot at the specified locaton, returns true if possible, false if impossible.
    bool setXYZ(float result[WALKER_LEG_NUMSERVOS], int posXYZ[3]);

    //set the side boolean
    void setSide(bool newSide);

    //write the servos in this leg and returns true if no error
    bool writeServos(float toWrite[WALKER_LEG_NUMSERVOS]);

    //Rotates a leg
    void rotateCoords(int setXYZ[3]);
};

#endif
