#ifndef DXL_SERVO
#define DXL_SERVO

#include "MyServo.h"
#include <Arduino.h>

#include<ax12Serial.h>    //KurtE's bioloid library https://github.com/KurtE/BioloidSerial
#include<BioloidSerial.h> //KurtE's bioloid library https://github.com/KurtE/BioloidSerial

class DXLServo : public MyServo {
  private:
    int servo_id = 0;
  public:
    //Constructor for set of Dynamixel servos
    DXLServo(int id, Stream* servoSerialIn);

    //Overriding set and get position in radians
    //Set the specified servo to the target position (radians)
    void setServoRad(float pos);
    //Get the target of the specified servo (radians)
    float getServoRad();
    //get lower limit of servo
    float getServoLowerLimitRad();
    //get upper limit of servo
    float getServoUpperLimitRad();

    //Deconstructor for set of Dynamixel servos
    ~DXLServo();
};

#endif
