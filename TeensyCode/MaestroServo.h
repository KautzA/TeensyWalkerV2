#ifndef MAESTRO_SERVO
#define MAESTRO_SERVO

#include "MyServo.h"
#include <Arduino.h>

class MaestroServo : public MyServo {
  private:
    int servo_id = 0;
    int controller_id = 12;
    float lower_limit = -1.5;
    float upper_limit = 1.5;
    float counts_per_rad;
    Stream* maestro_stream;
  public:
    //Constructor for MaestroServo
    //Stream should be configured to communicate with Maestro servo controller
    //default value for device_id is 12
    MaestroServo(int device_id, int channel_id, float lower_lim_rad, float upper_lim_rad, float counts_per_rad_in, Stream* servoSerialIn);

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
    ~MaestroServo();
};

#endif
