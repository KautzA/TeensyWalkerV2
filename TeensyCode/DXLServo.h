#ifndef DXL_SERVO
#define DXL_SERVO

#include "MyServo.h"
#include <Arduino.h>

class DXLServo : MyServo {
  private:
  public:
    //Constructor for set of Dynamixel servos
    DXLServo(int busVersion, Stream* servoSerialIn);

    //Overriding set and get position in radians
    //Set the specified servo to the target position (radians)
    void setServoRad(int id, float pos);
    //Get the target of the specified servo (radians)
    float getServoRad(int id);

    //Deconstructor for set of Dynamixel servos
    ~DXLServo();
};

#endif
