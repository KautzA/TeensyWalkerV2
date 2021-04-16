#include "MaestroServo.h"

MaestroServo::MaestroServo(int device_id, int channel_id, float lower_lim_rad, float upper_lim_rad, float counts_per_rad_in, Stream* servoSerialIn){
  controller_id = device_id;
  servo_id = channel_id;
  lower_limit = lower_lim_rad * counts_per_rad;
  upper_limit = upper_lim_rad * counts_per_rad;
  counts_per_rad = counts_per_rad_in;
  maestro_stream = servoSerialIn;
}

void MaestroServo::setServoRad(float pos){
  int servotarget = 1500 + (pos * counts_per_rad);
  
  //Maestro Servo Control
  byte Header = 170; //Header that opens the command and allows autobaudrate to be set
  byte Device = controller_id; //Identifier for the maestro in case of chaining. Default 12
  byte TruncatedCommand = 04;//0x04 represents the command to set servo position
  byte Servoplace = constrain(servo_id, 0, 999); //127);//the location of the servo on the controller
  byte Data1 = 0;//This holds the lower 7 bits of the position
  byte Data2 = 0;//This holds the upper 7 bits of the position
  unsigned long ScalePos = servotarget * 4;
  for (int i = 0; i < 7; i++) {
    bitWrite(Data1, i, bitRead(ScalePos, i));
  }
  for (int i = 0; i < 7; i++) {
    bitWrite(Data2, i, bitRead(ScalePos, (i + 7)));
  }
  //Write the packet to serial
  maestro_stream->write(Header);
  maestro_stream->write(Device);
  maestro_stream->write(TruncatedCommand);
  maestro_stream->write(Servoplace);
  maestro_stream->write(Data1);
  maestro_stream->write(Data2);
  /*
  Serial.println(Header);
  Serial.println(Device);
  Serial.println(TruncatedCommand);
  Serial.println(Servoplace);
  Serial.println(Data1);
  Serial.println(Data2);
  */
}

float MaestroServo::getServoRad(){
  return 0;
}

float MaestroServo::getServoLowerLimitRad() {
  return (float)(lower_limit)/counts_per_rad;
}

float MaestroServo::getServoUpperLimitRad() {
  return (float)(upper_limit)/counts_per_rad;
}

MaestroServo::~MaestroServo() {

}
