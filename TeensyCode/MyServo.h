#ifndef MY_SERVO
#define MY_SERVO
class MyServo {
  private:
    float upperLimitRad();
    float lowerLimitRad();
    float radOffset();
  public:
    //Set the specified servo to the target position (radians)
    virtual void setServoRad(float pos) = 0;
    //Get the target of the specified servo (radians)
    virtual float getServoRad() = 0;
    //Set the specified servo to the target position (degrees)
    void setServoDeg(float pos);
    //Get the target of the specified servo (degrees)
    float getServoDeg();
    //Get lower limit of this servo
    virtual float getServoLowerLimitRad() = 0;
    float getServoLowerLimitDeg();
    //Get upper limit of this servo
    virtual float getServoUpperLimitRad() = 0;
    float getServoUpperLimitDeg();

    //virtual deconstructor
    virtual ~MyServo();
};
#endif
